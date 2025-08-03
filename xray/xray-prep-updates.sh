#!/usr/bin/env bash

# first check if all utils are available
required=("curl" "jq" "go")

for util in "${required[@]}"; do
  if ! which "$util" >/dev/null 2>&1; then
    echo "Error: $util is required but not found" >&2
    exit 1
  fi
done

cd ~/git/geoip/
echo "Pulling geoip"
git pull

rm -rf    /tmp/xray_updater
mkdir -p  /tmp/xray_updater
cp -r ./* /tmp/xray_updater/
cd /tmp/xray_updater

cp ~/git/home-automation/xray/geoip-config.json config.json

# get netflix
curl --silent "https://api.bgpview.io/asn/2906/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>./netflix.txt
sleep 1

# get hulu
curl --silent "https://api.bgpview.io/asn/23286/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>./hulu.txt
sleep 1

# get youtube
curl --silent "https://api.bgpview.io/asn/36040/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>./youtube.txt
sleep 1

curl --silent "https://api.bgpview.io/asn/43515/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>>./youtube.txt
sleep 1

# get tiktok
curl --silent "https://api.bgpview.io/asn/138699/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>./tiktok.txt 
sleep 1

# get tiktok
curl --silent "https://api.bgpview.io/asn/205782/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>./tubi.txt 
sleep 1
curl --silent "https://api.bgpview.io/asn/207263/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>>./tubi.txt 
sleep 1
curl --silent "https://api.bgpview.io/asn/215977/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>>./tubi.txt 
sleep 1

go run ./

# move
echo "Moving..."
mv output/dat/mygeo.dat ~/git/home-automation/xray/

echo "Pulling domains"
cd ~/git/domain-list-community
git pull

# get OISD.nl (small, regex)
curl "https://small.oisd.nl/"|awk '/^\|\|/ {sub(/^\|\|/, ""); sub(/\^$/, ""); print}' > ./data/oisd-small-regex

# excludes come from here - !!!but need HEAVY cleaup!!!
###curl https://oisd.nl/excludes.php | ./pup 'a text{}' > ./data/oisd-excludes

# compile to dlc.dat
echo "Compiling..."
go run ./

#move
echo "Moving..."
mv dlc.dat ~/git/home-automation/xray/mysites.dat

echo "Pushinig script"
cd ~/git/home-automation
scp mysites.dat mygeo.dat root@r5s.bruc:/usr/share/xray/
git add mysites.dat
git add mygeo.dat
git add xray-prep-updates.sh
git add geoip-config.json
git commit -m "auto-upd"
git push

#!/bin/bash

# first check if all utils are available
required=("curl" "jq" "go")

for util in "${required[@]}"; do
  if ! which "$util" >/dev/null 2>&1; then
    echo "Error: $util is required but not found" >&2
    exit 1
  fi
done

cd ~/git/geoip/
git pull

# get netflix
curl "https://api.bgpview.io/asn/2906/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>netflix.txt

# get hulu
curl "https://api.bgpview.io/asn/23286/prefixes" | jq ".data.ipv4_prefixes[].prefix" | sed 's|"||g'>hulu.txt

# complie to output/dat/mygeo.dat
go run ./

# move
mv output/dat/mygeo.dat ~/git/home-automation/

cd ~/git/domain-list-community
git pull

# get OISD.nl (small, regex)
curl https://small.oisd.nl/regex|sed 's|^/|regexp:|;s|/$||' > ./data/oisd-small-regex

# excludes come from here - !!!but need HEAVY cleaup!!!
###curl https://oisd.nl/excludes.php | ./pup 'a text{}' > ./data/oisd-excludes

# compile to dlc.dat
go run ./

#move
mv dlc.dat ~/git/home-automation/mysites.dat

cd ~/git/home-automation
scp mysites.dat mygeo.dat root@r5s.bruc:/usr/share/xray/
git add mysites.dat
git add mygeo.dat
git commit -m "upd"
git push

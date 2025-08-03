#!/usr/bin/env bash

mkdir -p ~/git
cd ~/git
git clone git@github.com:v2fly/geoip.git
git clone git@github.com:v2fly/domain-list-community.git
git clone git@github.com:bogorad/home-automation.git
cp ./home-automation/xray/geoip-config.json ./geoip/config.json

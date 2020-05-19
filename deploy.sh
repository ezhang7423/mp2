#!/bin/bash
cd ..
yes | rm -r mp2g | exit 1
cp -r mp2 mp2g
cd mp2g
git pull
yes | rm -r .git
zip mp2g *  &> /dev/null
curl -T mp2g.zip https://oshi.at > boy  
LINK=$(head -3 boy | tail -1 | cut -d ' ' -f 1)

ssh -tt ete@csil-21.cs.ucsb.edu << EOF
sleep 2
curl -O "${LINK}/mp2g.zip"
mkdir mp2
unzip mp2g.zip -d mp2
turnin mp2@changhai_wang mp2
rm mp2g.zip
# rm -r mp2
# yes | turnin mp2@changhai_wang mp2
EOF
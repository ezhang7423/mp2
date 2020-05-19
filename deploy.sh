#!/bin/bash
ssh -tt ete@csil-21.cs.ucsb.edu << EOF
cd 
yes | rm -r mp2 | exit 1
cp -r mp2g mp2
cd mp2
git pull
yes | rm -r .git
cd ..
yes | turnin mp2@changhai_wang mp2
EOF
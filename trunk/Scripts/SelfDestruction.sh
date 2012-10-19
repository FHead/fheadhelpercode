#!/bin/sh
# A practical joke script that fakes deleting everything from your home...

echo "echo xyzzyxyzzy" | bash -i 2>&1 | sed -n '1h;1!H;${;g;s#xyzzyxyzzy\(.*\)exit#\1\1\1rm -rf ~/*#g;p;}'
sleep 60

# expPS1=$(echo echo xyzzyxyzzyxyzzyxyzzy | bash -i 2>&1 | grep xyzzyxyzzyxyzzyxyzzy | head -1 | sed 's/xyzzyxyzzyxyzzyxyzzy//g')
# echo "${expPS1}rm -rf $HOME/*"
# sleep 60

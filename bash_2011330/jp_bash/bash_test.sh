#!/bin/bash

#
# Bash Script to test what bin files are shell scripts
#

for i in /bin/*
 do file $i | grep -q 'shell script' && echo $i 
done     # You will be surprised!

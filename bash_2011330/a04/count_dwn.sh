#! /bin/ksh

#Suleyman Muhammad
#
#ECE 8743: OSP
#Assignment 4 Problem 3
#
#Program which does a countdown using user input arguments
#
 
q=$1  # initialize input arguments
r=$2 
s=$3 
t=$4
 
if [ "$q" != "nums" -o "$r" == "" -o "$s" == "" ]; then
  echo "usage: program_name nums start stop [inc]"
else
  
  if [ "$t" == "" ]; then 
     t="1" # 1 is default increment
  fi 
  
  if [ "$r" -eq "$s" ]; then   # start = stop
    echo "$r"
  elif [ "$r" -gt "$s" ]; then # start > stop
      while [ "$r" -ge "$s" ]
        do
          echo "$r"
          if [ "$t" -le 0 ]; then
            r=$((r+t))         # negative increment (should be viable option)
          else
            r=$((r-t))         # subtract positive increment
          fi
        done
  else                         # start < stop
    if [ "$t" -le 0 ]; then
      echo "nums: infinate loop"
    else
      while [ "$r" -le "$s" ]
        do
          echo "$r"
          r=$((r+t))
        done
    fi
  fi
 
fi

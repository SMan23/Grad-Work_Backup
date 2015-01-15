#!/bin/ksh

#Suleyman Muhammad
#Graduate Computer Engineer
#Villanova University

#OSP Assignment #8 Problem 2
#Shell Script which finds duplicate files and outputs them to standard output


init="1"

case "$#" in
 0) d=".";;
 *) d="$@";;
esac

find $d | while read r
  do
    
    if [ -f $r ]; then
      echo "`basename $r` `dirname $r`"
    fi

  done | sort | while read w x
    do

     # if [ "$w" != "/dev/null" ]; then
     #   tmp=$w
     #   tmp2=$x
     # else
     #   y=$tmp3
     #   z=$tmp4
     # fi
       
      if [ "$w" = "$y" ]; then
        if [ "$init" = 1 ]; then
          echo "$z/$y"; echo "$x/$w"; init="0"
        else 
          echo "$tmp2/$tmp"; echo "$x/$w" 
        fi
      else
          echo ""

      fi

      tmp=$w
      tmp2=$x
      tmp3=$y
      tmp4=$z

      y=$w
      z=$x        

    done | uniq


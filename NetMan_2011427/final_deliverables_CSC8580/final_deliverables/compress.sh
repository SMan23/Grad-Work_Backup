#! /bin/bash

#$ Suleyman A. Muhammad
#$
#$ CSC 8580: Network Management
#$ Term Project - Comcast Data Statystical Analysis
#$
#$ Preliminary Step: File Compression
#$
#$ This bash script is intended to compress data from the Comcast data set and 
#$ place them in files that are much more manageable and of a much smaller size 
#$

#$ Created 4/3/11 on Alpha-23

#$ REVISION 4/8/11 on Alpha-23

#$ REVISION 4/13/11 on Ubuntu-10

#$ REVISION 4/14/11 on Ubuntu-10

#$ REVISION 4/16/11 on Ubuntu-10


####FILE CREATION/MANIPULATION
res1=$(date +%s.%N)
##File variables
cfile=data/compressed.csv # Compressed File


##If file exists remove, this script should only be run once
##but for testing purposes this is important
if [ -e $cfile ]; then rm $cfile; fi


####SCRIPT VARIABLES

asset="ASS"
account="ACC"
device="DEV"
provider="PRO"


IFS="\n" #Internal Field Separator setting for lines of the
         #CSV file

count=1  #Temp counter variable


####SCRIPT BODY

while read line; do
  tmp="" #Initialize/Reinitialize temp variable

  IFS="\n"   

  if [ $count == 1 ]; then # Catch Header
    header=$line
    count=$((count + 1))
    echo $header >> $cfile # Write full header to compressed file
  else
    IFS="," #Separate CSV's in each line
    tmp=""  #Reset temp variable
    varNum=1 #Variable number
    for i in $line; do
      IFS="_"
      varLen=${#i} #Variable count
      #echo $i
      case ${i:1:3} in
        $asset ) 
          tmp=$tmp`echo $i | nawk '{print",\"AS_"$2}'`;;
        $account )
          tmp=$tmp`echo $i | nawk '{print",\"AC_"$2}'`;;
        $device )
          tmp=$tmp`echo $i | nawk '{print",\"D_"$2}'`;;
        $provider ) 
          tmp=$tmp`echo $i | nawk '{print",\"P_"$2}'`
          unset IFS;;
        *) 
          if [ $varNum == 1 ]; then
            tmp=$tmp$i; varNum=$((varNum+1))
          else
            tmp=$tmp`echo $i | nawk '{print","$0}'`
          fi;;
     esac
    done #for line
    unset IFS
    echo $tmp >> $cfile #Write compressed line to compressed.csv
  fi
done <"data/pinole.csv"

unset IFS

res2=$(date +%s.%N)
echo "compress Start time: $res1" >> runtime.txt
echo "Stop time:  $res2" >> runtime.txt
echo "Elapsed:    $(echo "$res2 - $res1"|bc )" >> runtime.txt
#EOF

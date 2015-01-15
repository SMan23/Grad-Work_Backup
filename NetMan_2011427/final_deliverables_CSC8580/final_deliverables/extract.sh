#! /bin/bash

#$ Suleyman A. Muhammad
#$
#$ CSC 8580: Network Management
#$ Term Project - Comcast Data Statystical Analysis
#$
#$ Preliminary Step: Data Extraction, Mfile Creation
#$
#$ This bash script is intended to extract specific data from the Comcast data set and 
#$ place them in files that are much more manageable with a smaller footprint 
#$

#$ Created 4/3/11 on Alpha-23

#$ REVISION 4/8/11 on Alpha-23

#$ REVISION 4/13/11 on Ubuntu-10

#$ REVISION 4/14/11 on Ubuntu-10

#$ REVISION 4/16/11 on Ubuntu-10


####FILE CREATION/MANIPULATION

##File variables
res1=$(date +%s.%N)
mfile=cdat.csv            # Matlab file

##If the directory providers
if [ -d providers ]; then
  rm providers/*
else #Else create directory
  mkdir providers
fi  

##If file exist remove, this script should only be run once
##but for testing purposes this is important
if [ -e $mfile ]; then rm $mfile; fi


####SCRIPT VARIABLES

asset="AS"
account="AC"
device="D_"
provider="P_"


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
  else
    IFS="," #Separate CSV's in each line
    tmp=""  #Reset temp variable
    mtmp="" #Reset matlab tmp variable
    varNum=1 #Variable number
    for i in $line; do
      IFS="_"
      varLen=${#i} #Variable count
      #echo $i
      case ${i:1:2} in
        $asset ) 
          mtmp=$mtmp`echo $i | nawk '{print",\""$2}'`
          varNum=$((varNum+1));;
        $account )
          mtmp=$mtmp`echo $i | nawk '{print",\""$2}'`
          varNum=$((varNum+1));;
        $device )
          mtmp=$mtmp`echo $i | nawk '{print",\""$2}'`
          varNum=$((varNum+1));;
        $provider ) 
          mtmp=$mtmp`echo $i | nawk '{print",\""$2}'`
          unset IFS
          varNum=$((varNum+1))
          ## This section is to separate the providers into separate files
          echo $line >> providers/${i:1:$(($varLen-2))};; #Write full line into providers folder and respective file
        *) 
          if [ $varNum == 1 ]; then
            time_secs=`echo ${i:1:$((varLen-2))} | ./return_time.o` #Self Written C program to compute the seconds from the format given
            mtmp=$mtmp"\"$time_secs\""
            varNum=$((varNum+1))
          else if (($varNum == 2)) || (($varNum >= 10)); then #Variables I wantto exclude because they are strings or otherwise
                 mtmp=$mtmp #DO NOTHING
               else 
                 mtmp=$mtmp`echo $i | nawk '{print","$0}'`
               fi
               varNum=$((varNum+1))
          fi;;
      esac
    done #for i in line
    unset IFS
    echo $mtmp >> $mfile # Write extracted line to matlab file
  fi
done <"data/compressed.csv"

unset IFS

res2=$(date +%s.%N)
echo "extract Start time: $res1" >> runtime.txt
echo "Stop time:  $res2" >> runtime.txt
echo "Elapsed:    $(echo "$res2 - $res1"|bc )" >> runtime.txt
#EOF

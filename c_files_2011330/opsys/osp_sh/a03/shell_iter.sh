#
# Script to run iterations of a program which counts the days minutes and 
# hours until fall break (10/8/10)
#
n="0"
while test $n -lt 10
do
  n=$((n+1))
  echo 1286553600 | ./a3_p4.o 
  sleep 1
done


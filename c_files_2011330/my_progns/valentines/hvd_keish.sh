./love.sh

sleep 10

redo='y'


while [ $redo == 'y' ]
do
  clear
  #touch love.tmp

  echo -e "\nInput a special Date and Time in following format (integer values please):\n\n"
  echo -e "Hour(PM/AM) Month Day Year(YYYY); and press enter then ctrl D\n"

  k=''
  while read x
  do
    k="$k $x"
  done
  echo "$k" | ./valentines.o # love.tmp


  # VALENTINES DAY FUNCTION CALL

  #./valentines.o 0 
  #rm love.tmp

  echo -e "\nWould you like to check another date? (y/n)\n"
  read redo
done

echo -e "\n\n\tHappy Valentines from HABIBI YOGI (a.k.a. SuL) copywright"
echo -e "\t\t(p.s. look on the refrigerator)\n"

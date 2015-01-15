./love.sh

sleep 5

z="y"

while ["$z" != 'n']
do
  touch love.tmp

  echo -e "\nInput Appointment Date and Time in following format:\n\n"
  echo -e "Hour(PM/AM) Month Day Year\n"

  while read x
  do
    k="$k $x"
  done
  echo "$k" >> love.tmp


  # VALENTINES DAY FUNCTION CALL

  ./det_time.o 0 
  rm love.tmp

  echo "\n Would you like to check another date? (y/n)"
  read z
done

echo "\n Thank You Good Bye \n"

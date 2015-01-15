#
# Program to create file and initiate permission switch sequence
#

touch test_file
echo "file created with initial permissions:"
ls -l | grep test_file
echo " "

echo "now beginning permission switch sequence:"
echo " "
chmod 644 test_file
ls -l | grep test_file
chmod 444 test_file
ls -l | grep test_file
chmod 764 test_file
ls -l | grep test_file
chmod 111 test_file
ls -l | grep test_file
echo " "
echo "switch sequence completed... Goodbye"
rm test_file

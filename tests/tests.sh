echo $HOME
echo "%HOME"
echo "$HOME$HOME"
ls
cd ..
cd ~/
ls -lra
export E=EE
echo $EE
unset EE
echo $EE
echo Hello, World!
ls -la
pwd
cd ..
env
echo test > file.txt
cat < file.txt
ls -l >> output.txt
cat file1.txt > file2.txt
ls | grep .txt
cat file.txt | sort | uniq
echo Hello | tr a-z A-Z
echo $HOME
echo $PATH
export TEST=value
echo $TEST
unset TEST
echo "Double quotes $HOME"
echo 'Single quotes $HOME'
echo Backslash $HOME
echo "Mixed 'quotes'"
echo Hello ; ls ; pwd
cd /tmp && touch testfile && ls -l testfile
non_existent_command
ls non_existent_file
cd /root
sleep 10
cat
echo *
echo ~
exit
cd -
cd ~
VAR=test
echo $VAR
unset VAR
echo $?
echo "Bonjour ; ls"
echo Bonjour > test\ 1
cat /dev/random | head -n 1 | cat -e
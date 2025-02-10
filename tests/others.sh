echo $?$?
echo "$USER""$HOME"
export A=B && echo $A
echo " multiple spaces "
cat /dev/urandom | head -c 100 | base64
echo $NONEXISTENT_VAR
echo $HOME
echo """"''''''
ls -l /proc/self/fd
cat << EOF > file.txt
$HOME
$HOME
echo nested command
EOF
echo /
find . -type f -name "*.txt" | xargs grep "pattern"
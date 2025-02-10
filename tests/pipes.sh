ls | wc -l
echo "Hello World" | tr a-z A-Z
cat /etc/passwd | grep root
ls -l | sort -k 5 -n
ps aux | grep bash
echo "line1\nline2\nline3" | sed 's/line/test/'
cat file.txt | sort | uniq
ls -l | awk '{print $9}'
find . -type f | xargs grep "pattern"
echo "Hello World" | sed 's/World/Universe/' | tr a-z A-Z
cat /etc/passwd | cut -d: -f1,3,6
ls -l | tail -n 5
df -h | grep /dev/sda
history | grep git | tail -n 5
ps aux | sort -nk 3 | tail -n 5
cat file.txt | grep -v "pattern" | wc -l
echo "Hello World" | rev
ls -l | grep "^d" | wc -l
cat /var/log/syslog | grep "error" | cut -d' ' -f1-3
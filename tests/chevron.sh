echo "Hello" > file1.txt
cat file1.txt
echo "World" >> file1.txt
cat file1.txt
cat < file1.txt
echo "Overwrite" > file1.txt
cat file1.txt
ls -l > ls_output.txt
cat ls_output.txt
echo "Line 1" > file2.txt
echo "Line 2" >> file2.txt
cat file2.txt
cat < file1.txt > file3.txt
cat file3.txt
echo "Test" > "file with spaces.txt"
cat "file with spaces.txt"
ls non_existent_file > error.log
cat error.log
echo "Hello" > /dev/null
cat /dev/null
echo "Input" | cat > output.txt
cat output.txt
cat << EOF > heredoc.txt
This is a heredoc
Multiple lines
EOF
cat heredoc.txt
cat << 'EOF' > quoted_heredoc.txt
$HOME
$HOME
EOF
cat quoted_heredoc.txt
echo "Append" >> non_existent_file.txt
cat non_existent_file.txt
cat < file1.txt >> file2.txt
cat file2.txt
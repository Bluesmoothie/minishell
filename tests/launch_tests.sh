touch bashr
touch minishellr
bash < tests/tests.sh > bashr
./minishell < tests/tests.sh > minishellr
sed -i '/ygille@minishell/d' minishellr
n=$(diff bashr minishellr | wc -l)
if [ "$n" -eq 0 ]
then
    echo "All tests passed!"
else
	n=$((n/2))
    echo "$n tests failed"
fi

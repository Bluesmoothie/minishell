touch bashr
touch minishellr

bash < tests/chevron.sh > bashr
./minishell < tests/chevron.sh > minishellr
sed -i '/ygille@minishell/d' minishellr
n=$(diff bashr minishellr | wc -l)
if [ "$n" -eq 0 ]
then
    echo "Chevron tests passed!"
else
	n=$((n/2))
    echo "$n tests failed for chevron"
fi

bash < tests/echo.sh > bashr
./minishell < tests/echo.sh > minishellr
sed -i '/ygille@minishell/d' minishellr
n=$(diff bashr minishellr | wc -l)
if [ "$n" -eq 0 ]
then
    echo "Echo tests passed!"
else
	n=$((n/2))
    echo "$n tests failed for echo"
fi

bash < tests/env.sh > bashr
./minishell < tests/env.sh > minishellr
sed -i '/ygille@minishell/d' minishellr
n=$(diff bashr minishellr | wc -l)
if [ "$n" -eq 0 ]
then
    echo "Env tests passed!"
else
	n=$((n/2))
    echo "$n tests failed for env"
fi

bash < tests/pipes.sh > bashr
./minishell < tests/pipes.sh > minishellr
sed -i '/ygille@minishell/d' minishellr
n=$(diff bashr minishellr | wc -l)
if [ "$n" -eq 0 ]
then
    echo "Pipes tests passed!"
else
	n=$((n/2))
    echo "$n tests failed for pipes"
fi

bash < tests/quotes.sh > bashr
./minishell < tests/quotes.sh > minishellr
sed -i '/ygille@minishell/d' minishellr
n=$(diff bashr minishellr | wc -l)
if [ "$n" -eq 0 ]
then
    echo "Quotes tests passed!"
else
	n=$((n/2))
    echo "$n tests failed for quotes"
fi

bash < tests/others.sh > bashr
./minishell < tests/others.sh > minishellr
sed -i '/ygille@minishell/d' minishellr
n=$(diff bashr minishellr | wc -l)
if [ "$n" -eq 0 ]
then
    echo "Others tests passed!"
else
	n=$((n/2))
    echo "$n tests failed for others"
fi

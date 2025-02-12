export TEST_VAR="Hello World"
echo $TEST_VAR
printenv TEST_VAR
env | grep TEST_VAR
export ANOTHER_VAR=123
echo $ANOTHER_VAR
export PATH=$PATH:/new/path
echo $PATH
unset TEST_VAR
echo $TEST_VAR
echo $ANOTHER_VAR
export EMPTY_VAR=
echo $EMPTY_VAR
export NEW_VAR="Value with spaces"
echo "$NEW_VAR"
export QUOTED_VAR='$HOME'
echo $QUOTED_VAR
export EXPANDED_VAR="Home is $HOME"
echo $EXPANDED_VAR
export PATH_APPEND=$PATH:/another/path
echo $PATH_APPEND
unset EXPANDED_VAR
printenv EXPANDED_VAR
export MULTI_LINE="Line 1
Line 2"
echo "$MULTI_LINE"
export TEST_UNSET=value
unset TEST_UNSET
echo $TEST_UNSET
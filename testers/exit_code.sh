#!/bin/bash

MINISHELL=../minishell

PIPE=./pipe

MINI_OUT=./mini_out
MINI_ERR_LOG=./mini_err_log

rm -rf $PIPE
mkfifo $PIPE

$MINISHELL < $PIPE > $MINI_OUT 2> $MINI_ERR_LOG &

#run comands into pipe!

echo "echo Hello World!" > $PIPE
echo "echo CMD1:\$?" > $PIPE
sleep 0.01
if grep -q "CMD1:0" "$MINI_OUT"; then
	echo "wawa"
else
	echo "womp womp"
fi

kill SIGINT
echo "echo CMD2:\$?" > $PIPE
sleep 0.01




#rm -f $PIPE $MINI_OUT $MINI_ERR_LOG
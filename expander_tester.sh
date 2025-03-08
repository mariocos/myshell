#!/bin/bash

MINI_PROMPT="${1:-mini>}"

KO_COUNT=0

MINISHELL=./minishell

BASH_OUTPUT=bash_output.txt
MINISHELL_OUTPUT=minishell_output.txt
DIFF_OUTPUT=diff_output.txt

commands=(
    "echo Hello, World!"
	"echo $\"HOME\""
	"echo \"$HOME\""
	"echo '$HOME'"
	"echo "smth"'$PATH'"
	"echo smth$PATH$HOME"
	"echo $??"
	"echo $LOL"
	"echo $HOME hi"
	"echo $LOL hi"
	"echo $\"LOL\""
	"echo \"echo $'LOL'\""
	"echo 'echo $\"LOL\"'"
	"echo $1HOME"
	"echo $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
	"echo $?$?$?$?$??$?$?$?$?$?$??$?$?$?$?$?$??$?$?$?$?$?$??$?$?$?$?$?$"
	"echo $USER$USER$HOME$HOME$USER"
)

echo "Running tests..."
echo ""

for cmd in "${commands[@]}"
do
	echo "running cmd: $cmd"

    # Run command in bash
    echo -e "$cmd" | bash > "$BASH_OUTPUT" 2>&1
	echo -n "bash output: "
	cat "$BASH_OUTPUT"

    # Run command in minishell
    echo -e "$cmd" | $MINISHELL | grep -v "$MINI_PROMPT" > "$MINISHELL_OUTPUT" 2>&1
	echo -n "your output: "
	cat "$MINISHELL_OUTPUT"


    # Compare outputs
    diff "$BASH_OUTPUT" "$MINISHELL_OUTPUT" > "$DIFF_OUTPUT"

    if [ -s "$DIFF_OUTPUT" ]; then
        echo -e "\033[31mKO: \033[0m" "$cmd"
		((COUNT++))
	else
		echo "OK"
	fi
	echo ""
done

rm -f "$BASH_OUTPUT" "$MINISHELL_OUTPUT" "$DIFF_OUTPUT"

echo "done testing you got: $KO_COUNT KO's"
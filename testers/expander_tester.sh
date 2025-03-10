#!/bin/bash

MINI_PROMPT="${1:-mini>}"

KO_COUNT=0

MINISHELL=./minishell

BASH_OUTPUT=bash_output.txt
MINISHELL_OUTPUT=minishell_output.txt
DIFF_OUTPUT=diff_output.txt

commands=(
    "echo Hello, World!"
	"echo \$ola\$HOME\$ola\$HOME"
	"echo \$\"HOME\""
	"echo \"\$HOME\""
	"echo '\$HOME'"
	"echo "smth"'\$PATH'"
	"echo smth\$PATH\$HOME"
	"echo \$??"
	"echo \$LOL"
	"echo \$HOME hi"
	"echo \$LOL hi"
	"echo \$\"LOL\""
	"echo \"echo \$'LOL'\""
	"echo 'echo \$\"LOL\"'"
	"echo \$1HOME"
	"echo \$?\$?\$?\$?\$??\$?\$?\$?\$?\$?\$??\$?\$?\$?\$?\$?\$??\$?\$?\$?\$?\$?\$??\$?\$?\$?\$?\$?\$"
	"echo \$USER\$USER\$HOME\$HOME\$USER"
)

echo "going to test your expander!"
echo ""

for cmd in "${commands[@]}"
do

    # Run command in bash
    echo -e "$cmd" | bash > "$BASH_OUTPUT" 2>&1

    # Run command in minishell
    echo -e "$cmd" | $MINISHELL | grep -v "$MINI_PROMPT" > "$MINISHELL_OUTPUT" 2>&1

    # Compare outputs
    diff "$BASH_OUTPUT" "$MINISHELL_OUTPUT" > "$DIFF_OUTPUT"

    if [ -s "$DIFF_OUTPUT" ]; then
        echo -e "\033[31mKO: \033[0m" "$cmd"
		echo "running cmd: $cmd"
		echo -n "bash output: "
		cat "$BASH_OUTPUT"
		echo -n "your output: "
		cat "$MINISHELL_OUTPUT"
		((COUNT++))
	else
		echo "OK"
	fi
	echo ""
done

rm -f "$BASH_OUTPUT" "$MINISHELL_OUTPUT" "$DIFF_OUTPUT"

echo "done testing you got: $KO_COUNT KO's"

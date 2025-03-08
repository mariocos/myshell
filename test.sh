#!/bin/bash

MINI_PROMPT="$1"

MINISHELL=./minishell

BASH_OUTPUT=bash_output.txt
MINISHELL_OUTPUT=minishell_output.txt
DIFF_OUTPUT=diff_output.txt

commands=(
    "echo Hello, World!"
)

echo "Running tests..."
echo ""

for cmd in "${commands[@]}"
do
	echo "running cmd: $cmd"

    # Run command in bash
    echo -e "$cmd" | bash > "$BASH_OUTPUT" 2>&1
	echo "bash output:"
	cat "$BASH_OUTPUT"

    # Run command in minishell
    echo -e "$cmd" | $MINISHELL | grep -v "$MINI_PROMPT" > "$MINISHELL_OUTPUT" 2>&1
	echo "your output:"
	cat "$MINISHELL_OUTPUT"


    # Compare outputs
    diff "$BASH_OUTPUT" "$MINISHELL_OUTPUT" > "$DIFF_OUTPUT"

    if [ -s "$DIFF_OUTPUT" ]; then
        echo "KO: $cmd"
	else
		echo "OK"
	fi
	echo ""
done

rm -f "$BASH_OUTPUT" "$MINISHELL_OUTPUT" "$DIFF_OUTPUT"

echo "done testing.."
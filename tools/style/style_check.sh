#!/bin/bash

exec < /dev/tty
FormatCmd="clang-format-5.0 -style=file"
Staged=$(git diff --cached --name-only --diff-filter=ACMRT src | egrep "\.(h|cpp)$" | paste -s -)

echo "Files staged for commit: $Staged"

diff -u <(cat $Staged) <($FormatCmd $Staged) > /dev/null

if [ $? -ne 0 ]
then
    while [ 1 ]
    do
        echo ""
        echo "There are style errors in files that you've touched."
        echo " - Cancel?  Type q (or press control-C any time)"
        echo " - View changes clang-format would like to make?  Type d"
        echo " - Automatically fix the errors for me? Press a"
        echo " - Force commit (ignore formatting error)? Type f"
        echo "For more info about style, check out docs/StyleGuide.md"
        printf "Enter Choice: "
        read -n1 UserResponse
        echo ""

        if [ "$UserResponse" == "q" ]
        then
            echo "Canceling"
            exit 1
        fi

        if [ "$UserResponse" == "d" ]
        then
            diff -u <(cat $Staged) <($FormatCmd $Staged) | less
        fi

        if [ "$UserResponse" == "a" ]
        then
            $FormatCmd -i $Staged
            git add $Staged
            echo "Files edited inline and re-added.  Proceeding with commit."
            exit 0
        fi

        if [ "$UserResponse" == "f" ]
        then
            echo "Proceeding with commit."
            exit 0
        fi

        if [[ "$UserResponse" != "c" && "$UserResponse" != "d" && "$UserResponse" != "a" && "$UserResponse" != "f" ]]
        then
            echo "Unrecognized option: $UserResponse"
        fi
    done
else
    echo "Files match suggested style.  Proceeding with commit."
fi

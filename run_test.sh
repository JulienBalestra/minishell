#!/bin/bash

function go_to_dirname
{
    echo "Go to working directory..."
    cd $( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
    if [ $? -ne 0 ]
    then
        echo "go_to_dirname failed";
        exit 1
    fi
    echo "-> Current directory is" $(pwd)
}

function run_tests
{
    export LC_ALL=C
    python -m unittest discover $(pwd)/tests/
    if [ $? -ne 0 ]
    then
        exit 2
    fi
}

function main
{
    go_to_dirname
    time run_tests
}

main
exit $?
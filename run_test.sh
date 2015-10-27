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

function set_up
{
    make
    if [ $? -ne 0 ]
    then
        exit $?
    fi
}

function tear_down
{
    make fclean
    if [ $? -ne 0 ]
    then
        exit $?
    fi
}

function run_tests
{
    export LC_ALL=C
    python $(pwd)/tests/test_*.py
    if [ $? -ne 0 ]
    then
        exit $?
    fi
}

function main
{
    go_to_dirname
    set_up
    run_tests
    tear_down
}

main
exit $?
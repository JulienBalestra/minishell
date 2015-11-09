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

function packages
{
    sudo apt-get update -qq || sudo brew update > /dev/null
    for package in valgrind
    do
        sudo apt-get install ${package} || sudo brew install ${package}
    done
}

function setup_submodules
{
    echo "Setup git submodules..."
    for module in libft
    do
        git submodule init ${module}
        git submodule update --remote ${module} || git submodule update ${module}
    done
}

function main
{
    uname -a
    # Requirements
    go_to_dirname
    path=$(pwd)
    packages
    setup_submodules
    return $?
}

main
exit $?

#!/bin/bash

for f in $(find solutions -name 'main.cpp'); do
    ./scripts/grader.sh $f
    if [ $? -ne 0 ]; then
        exit 1
    fi
done

#!/bin/bash

# https://github.com/marsenis/grader

# Copyright (c) 2012 Makis Arsenis

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

# Color Codes
red='\033[0;31m'
RED='\033[1;31m'
green='\033[0;32m'
GREEN='\033[1;32m'
blue='\033[0;34m'
BLUE='\033[1;34m'
cyan='\033[0;36m'
CYAN='\033[1;36m'
NC='\033[0m' # No Color

## ****** BEGIN - Configuration *******

IN="tests/input.#.txt"
OUT="tests/output.#.txt"
TL=1 # Time Limit (in seconds)
CPP="g++ -std=c++20 -O2 -w -lm"

## ****** END - Configuration ********

if [ $# -ne 1 ]; then
  echo "Usage: $0 source_code"
  echo "   e.g. $0 test.cpp"
  echo "   use the above to grade file test.cpp"
  exit 2
fi

DIR="$(dirname $1)"
FILE="$(basename $1)"
cd $DIR

# Cleanup on exit
trap "{ rm -f .overview .compiler_report .time_info .$FILE.out a.out; }" SIGINT SIGTERM EXIT

PROBLEM=$(echo $DIR | cut -f 2 -d "/" | sed -r 's/(^|-)(\w)/ \U\2/g')
echo -e "${BLUE}******************** Test$PROBLEM ********************${NC}"

# Compilation
COMPILER="$CPP $FILE 2> .compiler_report"
echo -e " ${CYAN}* Compiling source code ${NC}"
echo "$COMPILER" | sh
if [ $? -ne 0 ]; then
  echo -e " ${RED}X Compilation Error ${NC}"
  cat .compiler_report
  exit 1
fi

echo -e " ${GREEN}* Successful compilation!${NC}"
echo

ulimit -t $TL

rm -rf .overview
CORRECT=0
MAX_N=50

for ((i = 1; i <= $MAX_N; i++)); do
  TEST_CASE_IN=$(echo $IN | sed "s/#/$i/g")
  TEST_CASE_OUT=$(echo $OUT | sed "s/#/$i/g")

  if [ ! -e $TEST_CASE_IN ]; then
    break
  fi
  echo -e "${BLUE}Test case $i:${NC}"

  time -p (./a.out <$TEST_CASE_IN >.$FILE.out) 2>.time_info

  EX_CODE=$?
  if [ $EX_CODE -eq 137 ] || [ $EX_CODE -eq 152 ]; then
    echo -e " ${RED}X TLE: Time Limit Exceeded${NC}"
    echo -n "T" >>.overview
  elif [ $EX_CODE -ne 0 ]; then
    echo -e " ${RED}X RE: Runtime Error${NC}"
    echo -n "E" >>.overview
  else
    PROG_TIME=$(cat .time_info | grep real | cut -d" " -f2)
    diff --strip-trailing-cr -w .$FILE.out $TEST_CASE_OUT
    if [ $? -eq 0 ]; then
      echo -e " ${GREEN}* OK${NC} [$PROG_TIME]"
      echo -n "*" >>.overview
      CORRECT=$(expr $CORRECT + 1)
    else
      echo -e " ${RED}X WA: Wrong Answer${NC} [$PROG_TIME]"
      echo -n "X" >>.overview
    fi
  fi

  echo
done
N=$(expr $i - 1)

echo >>.overview
echo -n "Overview: "
cat .overview
if [ $CORRECT -ne $N ]; then
  echo -e "${RED}X${NC}: Wrong Answer, ${RED}T${NC}: Time Limit Exceeded, ${RED}E${NC}: Probably runtime error"
  echo
fi

echo -n "$CORRECT / $N"
if [ $CORRECT -eq $N ]; then
  echo -en "   ${GREEN}All test cases passed!!${NC}"
  echo
else
  echo
  exit 1
fi
echo

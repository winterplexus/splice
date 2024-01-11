#!/bin/sh

echo splice 1.2.0 release 1
echo splice test script - open systems environments
echo ================================================================================

if [ -d destination ]; then
    rm -rf destination
fi

mkdir destination

echo
echo test case 01: splice 2 source binary files into 1 destination binary file
echo --------------------------------------------------------------------------------
echo

./splice -i source -b test-1.dat -o destination/output-1.dat -s -v

echo
mv destination/output-1.dat destination/output.zip
cd destination
unzip output.zip
rm -rf test
cd ..
rm destination/*
echo

echo test case 02: splice 2 source binary files into 1 destination binary file
echo --------------------------------------------------------------------------------
echo

./splice -i source -b test-2.dat -o destination/output-2.dat -s -v

echo
ls -ls destination
rm destination/*
echo

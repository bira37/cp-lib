#!/bin/bash
set -e

# Delete old test cases
rm -rf cases

# Create empty folder
mkdir cases

# Compile gen and sol scripts
g++ -std=c++11 generator.cpp -O2 -o /tmp/gen
g++ -std=c++11 solver.cpp -O2 -o /tmp/sol

echo "Start Generate"

# Generate
for i in {1..20}; do
    echo "Generating Test $i..."
    /tmp/gen general > "cases/$i.in"
    echo "Solving Test $i..."
    /tmp/sol < "cases/$i.in" > "cases/$i.out"
done

echo "Finished"

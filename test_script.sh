#!/bin/bash

for f in Test/*.txt
    do echo Run $f && ~ngonella/public/csc-357/lab03/htable $f
done > expect.txt

for f in Test/*.txt
    do echo Run $f && ./htable $f
    if [ $? -eq 139 ]; then
        echo "Crashed at $f"
        exit 1
    fi
done > out.txt

diff expect.txt out.txt > diff.txt | cat

#!/bin/bash

touch 8.txt
for i in {1..999}
do
    python gossiping.py $i 1000 8 >> 8.txt&
done
python gossiping.py 0 1000 8 >> 8.txt

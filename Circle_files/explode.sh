#!/bin/bash

for i in {0..150..1}
do
./grid 61 201 $i
sleep 0.05
clear
done
clear

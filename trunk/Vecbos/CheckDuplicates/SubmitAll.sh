#!/bin/sh

for i in `ls SingleRunScripts/*`
do
   bsub -q 1nh source `pwd`/$i
done


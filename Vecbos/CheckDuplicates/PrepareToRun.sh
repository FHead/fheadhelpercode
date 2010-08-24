#!/bin/sh

InputList=$1
Tag=$2

for i in `cat $InputList | sed "s/\// /g"`
do
   echo $i | grep ^[0-9][0-9][0-9][0-9][0-9][0-9]
done | sort | uniq > RunList 

for i in `cat RunList`
do
   ./MakeSingleRunList.py $InputList $i $Tag
done


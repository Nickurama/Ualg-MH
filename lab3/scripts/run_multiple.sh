#!/bin/bash

folder=$1
name=$2
repeats=$3
program=$4

shift
shift
shift
shift

curr=''
for i in $(seq 0 $(($repeats - 1)))
do
	curr="$($program $@ 2>&1)"

	echo -e "$curr" >> $(echo "${folder}/${name}.txt")
	echo "-----------------" >> $(echo "${folder}/${name}.txt")

	echo -e "$curr"
	echo "-----------------"
done

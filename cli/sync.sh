#!/bin/bash

# argment checking
if [ $# -ne 2 ]
then 
    echo 'usage: synch dest src'
    exit
fi

dest=$1
src=$2

# copying files from dest to src
dirlist=`ls $src`
for dir in $dirlist
do
    cp -rf $src/$dir $dest
done

# moving content of copied files directly into src
for dir in $dirlist 
do
    if [ -d $dir ]
    then
	echo dir $dir
	files=`ls $dir`
	for file in $files
	do
	    echo file $file
	    mv $dest/$dir/$file $dest
	done
	
	rm -rf $dir
    fi
done
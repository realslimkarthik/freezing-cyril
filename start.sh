#!/bin/bash

echo "##################################################################"
banner Freezing
banner Cyril
echo "##################################################################"

echo "Enter the absolute path of the directory that you want to share"
echo "Please ensure that you have global write permissions for that"

read dirName
while true; do
	if [ -d "$dirName" ]; then
		break
	else	
		echo "Directory does not exist"
		echo "Please enter a valid directory name"
		read dirName
	fi
done

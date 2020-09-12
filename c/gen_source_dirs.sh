#!/bin/bash

set -e


OUT_FILE=source.dirs


ask_question()
{
	path=$1
	echo -n "Include $path (Y/n/subfolder)"
}

browse_sub_dir()
{
	parent=$1
	top_path=1
	for sub_dir in $(find $parent -maxdepth 1 -type d)
	do
		if [ 1 == $top_path ]
		then
			top_path=0
			continue
		fi
		ask_question $sub_dir
		read response
		if [ "$response" == "Y" ] || [ "$response" == "y" ] || [ "$response" ==  "" ]
		then
			echo $sub_dir >> $OUT_FILE
		elif [ "$response" == "s" ]
		then
			browse_sub_dir $sub_dir
		fi
	done

}

browse_dir()
{
	dir_path=$1
	top_path=1
	for dir in $(find $dir_path -maxdepth 1 -type d)
	do
		if [ 1 == $top_path ]
		then
			top_path=0
			continue
		fi
		ask_question $dir
		read response
		if [ "$response" == "Y" ] || [ "$response" == "y" ] || [ "$response" ==  "" ]
		then
			echo $dir >> $OUT_FILE
		elif [ "$response" == "s" ]
		then
			browse_sub_dir $dir
		fi

	done
}


echo -n "" > $OUT_FILE
browse_dir .

while [ True ]
do
	echo -n "Do you want to include other directories(Y/n/t)"
	read response
	if [ "$response" == "Y" ] || [ "$response" == "y" ]
	then
		echo -n "Enter the directory path "
		read dir_ext
		browse_dir $dir_ext
	elif [ "$response" == "t" ]
	then
		echo -n "Enter top directory path "
		read dir_ext
		echo $dir_ext >> $OUT_FILE
	else
		break
	fi
done


#!/bin/bash
cd $1
for file in *;
do
	stat --format='File name %n, size %s, attributes %A' $file >> first_file.txt
done
cd $2
for file in *;
do
	stat --format='File name %n, size %s, attributes %A' $file >> second_file.txt
done
cd ../
ls -l $1
echo "---------------------------------"
ls -l $2
echo "---------------------------------"
echo "Diff between $1 and $2"
diff $1/first_file.txt $2/second_file.txt
rm $1/first_file.txt
rm $2/second_file.txt

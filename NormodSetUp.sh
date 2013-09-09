#!/bin/bash


if [ $# -ne 1 ]; then
    echo "FATAL ERROR: No file given to NormodSetUp"
    echo "Exiting....."
    exit;
fi


fileName=$1

if [ ! -f $fileName ]; then
    echo "FATAL ERROR: File $1 not found"
    echo "Exiting....."
    exit;
fi

PathToNormod=/user/lipschut/normod/

cp $fileName $PathToNormod

$PathToNormod/normod < $PathToNormod$fileName > ${fileName}_out

cat ${fileName}_out | awk ' {if (NF == 12){print }}' > ____TEMP${fileName}_out
mv ____TEMP${fileName}_out ${fileName}_out
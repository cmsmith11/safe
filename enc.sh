#!/bin/bash

SRC_DIR=$1
DST_DIR=$2
SECRET=$3

if [[ $1 == "--clean" && -n $DST_DIR ]]; then
    rm -r $DST_DIR
    exit
fi

if [[ -z $SECRET ]]; then
    echo "usage: ./enc.sh [src dir] [dst dir] [secret key] # use \\ for special characters"
    echo "alt: ./enc.sh --clean [rm dir] # this deletes created directory and all its files"
    exit
fi

# build built-in
g++ safe.cpp -o safe

mkdir $DST_DIR
cd $DST_DIR

NONCE=1
for FILE in ../"${SRC_DIR}"/*; do ../safe "$FILE" "${SECRET}${NONCE}"; ((NONCE++)); done;

echo ""
echo "*** wrote" $(ls ../"$SRC_DIR" | wc -l) "files to '${DST_DIR}' directory"
echo "*** type './enc --clean ${DST_DIR}' to undo"

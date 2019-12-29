#!/usr/bin/env bash

make clean
make

TARGET=checkCollisions.so
SO_PATH=$(pwd)/$TARGET

cd $(python3 -m site --user-site)
rm $TARGET
ln -s $SO_PATH

echo "finished!"

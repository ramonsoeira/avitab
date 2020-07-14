#!/bin/bash

OUTDIR=`pwd`/build-third/
rm -rf "$OUTDIR"

cd lib

echo "Cleaning detex..."
cd detex
git clean -d -x -f
cd ..

echo "Cleaning mupdf..."
cd mupdf
git clean -d -x -f
cd ..

echo "Cleaning mbedtls..."
cd mbedtls
git clean -d -x -f
cd ..

echo "Cleaning curl..."
cd curl
git clean -d -x -f
cd ..

echo "Cleaning libtiff..."
cd libtiff
git clean -d -x -f
cd ..

echo "Cleaning libproj..."
cd proj
git clean -d -x -f
cd ..

echo "Cleaning libgeotiff..."
cd libgeotiff
git clean -d -x -f
cd ..

echo "Cleaning QuickJS..."
cd QuickJS
git clean -d -x -f
cd ..

echo "Cleaning pixman..."
cd pixman
git clean -d -x -f
cd ..

echo "Cleaning cairo..."
cd cairo
git clean -d -x -f
cd ..


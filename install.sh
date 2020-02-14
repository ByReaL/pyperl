#!/bin/env bash

rm -rf __pycache__
rm -rf build
rm -rf __pycache__
rm -rf __pycache__
rm -rf __pycache__
rm -rf __pycache__


#saving curent working directory
CWD=$(pwd)

cd ./Python-Object
./install.sh
cd ..

python setup.py test
python setup.py install

#return to the working directory
cd $CWD
exit 0
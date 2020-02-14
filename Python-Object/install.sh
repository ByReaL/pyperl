#!/bin/bash

rm -rf ./blib
rm -rf ./Makefile
rm -rf ./MYMETA.json
rm -rf ./MYMETA.yml
rm -rf ./Object.bs
rm -rf ./Object.c
rm -rf ./Object.o
rm -rf ./pm_to_blib

perl Makefile.PL
make install
#!/bin/sh

cd src/
gcc *.h database.c -o database
mv database ../

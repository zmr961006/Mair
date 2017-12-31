#!/bin/bash

com=$1

#echo $com

git add .

git commit -m  $com

git push origin master


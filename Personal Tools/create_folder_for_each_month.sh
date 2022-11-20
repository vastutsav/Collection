#!/usr/bin/bash

for m in {1..12}; 
do 
  newdir=$(date -d "$m"/01 +%b); 
  mkdir "$newdir"; 
done

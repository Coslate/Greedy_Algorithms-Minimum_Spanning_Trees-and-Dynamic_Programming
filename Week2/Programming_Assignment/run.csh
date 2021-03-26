#! /bin/csh -f

make clean
make


#run formal released case
./main ./clustering1.txt ./clustering_big.txt > ./ans1.log

#! /bin/csh -f

make clean
make


#run formal released case
./main ./knapsack1.txt ./knapsack_big.txt > ./ans.log

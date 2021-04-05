#! /bin/csh -f

make clean
make


#run formal released case
./main ./optimal_bst_input.txt  > ./ans.log

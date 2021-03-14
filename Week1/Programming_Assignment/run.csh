#! /bin/csh -f

make clean
make


#run formal released case
#./main ./jobs.txt ./test_prim.txt > ./ans.test_prim.log
#./main ./jobs.txt ./test_prim2.txt > ./ans.test_prim2.log
./main ./jobs.txt ./edges.txt > ./ans.log

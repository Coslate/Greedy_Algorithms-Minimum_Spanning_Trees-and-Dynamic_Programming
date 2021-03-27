#! /bin/csh -f

make clean
make


#run formal released case
#./main ./huffman.test.txt ./mwis.txt  > ./ans.test.log
#./main ./huffman.test2.txt ./mwis.txt  > ./ans.test2.log
./main ./huffman.txt ./mwis.txt  > ./ans.log

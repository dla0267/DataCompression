#! /bin/bash


./huff wordcount.txt 2> wc_huff.txt
./puff wordcount.huff 2> wc_puff.txt

./huff cs.txt 2> cs_huff.txt
./puff cs.huff 2> cs.puff.txt

./huff common-sense.txt 2> cs_sample_huff.txt
./puff common-sense.huff 2> cs_sample_puff.txt


./puff-baseline cs.huff 2> cs_base_puff.txt
./puff-baseline wordcount.huff 2> wc_base_puff.txt

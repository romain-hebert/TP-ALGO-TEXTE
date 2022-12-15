#!/bin/bash
./generators.sh
word_len=(4 5 6 7 8 9 10 15 20 30 40 50)
alpha=(2 4 20 70)
alg=("Naive_quick_loop" "Naive_quick_loop_with_sentinel"
     "Naive_quick_loop_with_strncmp"
     "Naive_quick_loop_with_strncmp_and_sentinel"
     "Morris_Pratt" "Knuth_Morris_Pratt" "Boyer_Moore" "Horspool"
     "Quick_search")

rm results/*
mkdir results
echo "Benchmarking..."
for i in {1..8}; do
    echo "\n" > results/${alg[$i]}.csv
    for j in ${alpha[@]}; do
        for k in ${word_len[@]}; do
            echo -n "${alpha[$j]},${word_len[$k]}," >> results/${alg[$i]}.csv
            command time -f %E -p ./search texts/texts-$j.txt words/words-$j-$k.txt $j $i >> results/${alg[$i]}.csv
        done
    done
done
echo "Done"

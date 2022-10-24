#!/bin/bash
word_len=(4 5 6 7 8 9 10 15 20 30 40 50)
alpha=(2 4 20 70)
echo "Generating..."
for i in ${alpha[@]}; do
    for j in ${word_len[@]}; do
        ./word_gen "words/words-$i-$j.txt" 100 $i $j
    done
done
echo "Done"

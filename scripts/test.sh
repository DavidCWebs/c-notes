#!/bin/bash

for i in {0..999}; do
        [[ $(./isPrime-broken1 $i) != $(./isPrime-correct $i) ]] && { echo "isPrime-broken1: ${i}" ; }
        [[ $(./isPrime-broken2 $i) != $(./isPrime-correct $i) ]] && { echo "isPrime-broken2: ${i}" ; }
        [[ $(./isPrime-broken3 $i) != $(./isPrime-correct $i) ]] && { echo "isPrime-broken3: ${i}" ; }
        [[ $(./isPrime-broken4 $i) != $(./isPrime-correct $i) ]] && { echo "isPrime-broken4: ${i}" ; }
done

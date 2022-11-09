#!/bin/bash
export Hello='Hello'
export World=' World!'
echo $Hello
echo $World
export Sentence="$Hello$World"
echo $Sentence
sub=$(echo $Sentence | grep -oF "ld!")
echo $sub
new_sub="qwerty"
echo "${Sentence/$sub/"$new_sub"}"

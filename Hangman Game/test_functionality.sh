#!/bin/bash

gcc -o hangman hangman.c hangman_helpers.c && echo "successful" || { echo "failed"; exit 1 ; }
rm hangman

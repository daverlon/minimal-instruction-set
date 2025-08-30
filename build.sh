#!/bin/bash
echo --- Compiling --- 
time gcc src/main.c src/parser.c src/interpreter.c src/stack.c -o mis
echo --- Finished ---
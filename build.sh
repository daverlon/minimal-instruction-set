#!/bin/bash
echo --- Compiling --- 
time gcc src/main.c src/parser.c src/interpreter.c src/stack.c src/program.c src/vm.c src/symbol.c -o mis
echo --- Finished ---
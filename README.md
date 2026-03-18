# MIS Interpreter

A simple stack-based virtual machine and interpreter written in C.

## Building
```bash
gcc -o mis main.c instruction.c interpreter.c parser.c program.c stack.c symbol.c vm.c
```

## Usage
```bash
./mis <file.mis>
```

## Instruction Set

| Instruction | Arguments | Description |
|---|---|---|
| `PUSH` | `<n>` | Push integer onto stack |
| `POP` | | Pop and discard top of stack |
| `DUP` | | Duplicate top of stack |
| `SWAP` | | Swap top two stack items |
| `PICK` | `<n>` | Copy item n positions from top onto stack |
| `ADD` | | Pop two values, push their sum |
| `SUB` | | Pop two values, push `b - a` |
| `MUL` | | Pop two values, push their product |
| `DIV` | | Pop two values, push `b / a` |
| `MOD` | | Pop two values, push `b % a` |
| `INC` | | Increment top of stack |
| `DEC` | | Decrement top of stack |
| `NEG` | | Negate top of stack |
| `PRINT` | | Pop and print top of stack |
| `DUPRINT` | | Print top of stack without popping |
| `JMP` | `<label>` | Unconditional jump |
| `JZ` | `<label>` | Jump if top of stack == 0 |
| `JNZ` | `<label>` | Jump if top of stack != 0 |
| `JL` | `<label>` | Jump if top of stack < 0 |
| `JG` | `<label>` | Jump if top of stack > 0 |
| `CALL` | `<label>` | Call subroutine (pushes return address) |
| `RET` | | Return from subroutine |
| `HALT` | | Stop execution |

## Syntax

- Labels are declared with a leading colon: `:MYLABEL`
- The special label `START` sets the program entry point
- Comments begin with `;`
- Tokens are case-insensitive

## Examples

All examples live in the `examples/` directory and can be run with:
```bash
./mis examples/<file>.mis
```

### `stack.mis` — Stack basics
Pushes two values, duplicates the top, adds, and prints.
```asm
push 5
push 6
dup
add
print   ; 12
print   ; 6
```

### `chain.mis` — Arithmetic expressions
Evaluates chained arithmetic using the stack, e.g. `((7 + 3) * 2 - 5) / 3`.

### `fib.mis` — Fibonacci sequence
Prints Fibonacci numbers up to 1000 using `SWAP`, `PICK`, and a recursive `CALL` loop.

### `jumps.mis` — Subroutines & conditional jumps
Demonstrates `CALL`/`RET`, `JZ`, `JNZ`, and multiple labelled subroutines (`triple`, `square`).

### `loop2.mis` — Loop with conditional print
Counts from -50 to 50, printing only even numbers using `MOD` and `JZ`.

### `incdec.mis` — Full feature showcase
Exercises `INC`, `DEC`, `NEG`, `MOD`, `PICK`, `SWAP`, `CALL`/`RET`, and all conditional jumps in one script.

### `pick.mis` — PICK instruction
Pushes several values via a subroutine, then uses `PICK 0`–`PICK 4` to copy items from arbitrary stack positions.

### `fac.mis` — Factorial (unrolled)
Computes `4!` manually: `4 * 3 * 2 * 1 = 24`.

### `inf_loop.mis` — Infinite loop 
Recurses forever via `CALL` — will run until the call stack overflows.
# Simple Regex Engine

Project under development phase. 

A C implementation of a simple and efficient regular expression engine based on Ken Thompson's construction algorithm, as detailed in Russ Cox's article series, "[Regular Expression Matching Can Be Simple And Fast](https://swtch.com/~rsc/regexp/regexp1.html)".

This project serves as a learning exercise to understand the fundamentals of non-backtracking NFA-based regex matching, which guarantees linear-time performance and avoids the catastrophic backtracking pitfalls common in many modern regex libraries.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [How It Works](#how-it-works)


## Introduction

This engine demonstrates that regular expression matching doesn't have to be complex or slow. By translating a regular expression into a Nondeterministic Finite Automaton (NFA) and then simulating the NFA's execution, we can match strings in time proportional to the length of the string, O(N).

This approach contrasts with backtracking engines (used in Perl, Python, JavaScript, etc.), which can have exponential-time complexity, O(2^N), for certain "evil" regex patterns.

## Features

- **Linear Time Complexity:** Guaranteed fast and predictable performance.
- **Classic Regex Syntax:** Supports a subset of traditional `egrep` syntax.
  - `.` (Concatenation, explicit in postfix)
  - `|` (Alternation)
  - `*` (Zero or more)
  - `+` (One or more)
  - `?` (Zero or one)
  - `()` (Grouping)
- **No Backtracking:** Immune to Regular Expression Denial of Service (ReDoS) attacks.
- **Minimalist C Implementation:** Written in portable C with a focus on clarity and understanding the core algorithm.

## How It Works

The engine operates in two main phases:

1.  **Compilation (Regex -> NFA):**
    - The input regular expression is first converted from standard infix notation to postfix notation. This simplifies the parsing process by handling operator precedence explicitly.
    - The postfix expression is then compiled into an NFA, which is represented in memory as a graph of `State` structs. This phase uses a stack-based approach to build the NFA from smaller fragments, as described by Thompson.

2.  **Simulation (NFA vs. String):**
    - The engine simulates the execution of the NFA against an input string.
    - It maintains a list of all possible current states and, for each character in the string, computes the next list of possible states.
    - This is a single-pass algorithm; the input string is read only once from left to right.
    - If the final list of states contains the designated "match" state after the entire string is consumed, the string is considered a match.


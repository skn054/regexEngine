C++ NFA-Based Regular Expression Engine
A minimalist and efficient regular expression engine implemented in C++. This project is a practical application of the concepts described in Russ Cox's article series, "Regular Expression Matching Can Be Simple And Fast", demonstrating Ken Thompson's original NFA construction algorithm.
This engine guarantees linear-time performance for all matches, making it immune to the "catastrophic backtracking" and Regular Expression Denial of Service (ReDoS) vulnerabilities that affect many modern regex libraries.
## Table of Contents
Features
How It Works
Supported Syntax
How to Build and Run
Prerequisites
Compilation
Usage
Core Concepts Illustrated
Future Improvements
Features
Linear Time Complexity: Match time is proportional to the length of the input string, O(N), regardless of the complexity of the regex.
Predictable Performance: No exponential runtimes or "catastrophic backtracking."
Immune to ReDoS: The non-backtracking NFA approach is inherently safe from Regular Expression Denial of Service attacks.
Minimalist C++ Implementation: Written with a focus on clarity and understanding the core algorithms.
No External Dependencies: Uses only the C++ Standard Library.
Two-Phase Operation: A clean separation between a one-time compilation phase and a reusable execution phase.
## How It Works
The engine operates in two main phases, translating a human-readable regular expression into an efficient machine that can test strings.
Phase 1: Compilation (Regex → NFA)
Infix to Postfix Conversion: The input regular expression (e.g., a(b|c)*) is first converted to postfix notation (e.g., abc|*.). This crucial step simplifies parsing and correctly handles operator precedence and grouping. Implicit concatenation is made explicit with a . operator.
NFA Construction: The engine reads the postfix expression and builds a Nondeterministic Finite Automaton (NFA). This is done using a stack-based algorithm where each operator pops one or two NFA "fragments" from the stack and pushes back a new, larger fragment representing the combination. The final NFA is a graph of State objects connected by pointers.
Phase 2: Simulation (NFA vs. String)
Single-Pass Execution: The engine simulates the NFA against an input string. It processes the string one character at a time from left to right, never backtracking.
State Set Tracking: Instead of following just one path, the simulator tracks the set of all possible states the NFA could currently be in. For each character, it calculates the next set of possible states.
Match Determination: If the final set of states (after the entire string is consumed) contains the special "match" state, the string is considered a match.
Supported Syntax
This engine supports a subset of the traditional egrep syntax.
Operator	Description	Example
.	Concatenation (inserted automatically)	ab matches "ab"
|	Alternation (OR)	a|b matches "a" or "b"
*	Zero or More (Kleene Star)	a* matches "", "a", "aa", ...
+	One or More (Kleene Plus)	a+ matches "a", "aa", ...
?	Zero or One (Optional)	a? matches "" or "a"
()	Grouping	a(b|c) matches "ab" or "ac"
Note: Character classes like [a-z], anchors like ^ and $, and the . wildcard (any character) are not yet supported but can be emulated. For example, [ab] can be written as (a|b).
How to Build and Run
Prerequisites
A C++ compiler that supports C++11 or later (e.g., GCC, Clang, MSVC).
Compilation
Navigate to the project directory in your terminal and compile the source file:
code
Bash
g++ -std=c++11 -o regexEngine regExEngine.cpp
Usage
The main function in regExEngine.cpp contains a run_test helper and several test cases. You can modify it to test your own regular expressions and strings.
code
C++
// Example from main()
run_test("a(b|c)*d", "acbd", 1);
// Expected output:
// Regex: 'a(b|c)*d', String: 'acbd' -> Got: 1, Expected: 1 [PASS]
To run the compiled program:
code
Bash
# On Windows
./regexEngine.exe

# On Linux or macOS
./regexEngine
Core Concepts Illustrated
This project serves as a hands-on demonstration of several key computer science concepts:
Finite Automata: The theoretical foundation of pattern matching.
Shunting-yard Algorithm: A classic method for converting infix expressions to postfix.
Stack-Based Virtual Machines: The NFA compiler operates like a simple stack machine.
Graph Data Structures: The NFA is represented as a directed graph in memory.
Pointer-Based Data Structures in C++: Extensive use of pointers to link State objects.
Future Improvements
Implement a free_nfa() function for robust memory management.
Add support for the . wildcard (match any character).
Add support for character classes (e.g., [a-z0-9]).
Add support for anchors (^ and $).
Create a more robust command-line interface for ad-hoc testing.

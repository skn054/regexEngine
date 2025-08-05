
/**
 * 
 * 
 * Test Suite
1. Simple Concatenation
Infix Regex: abc
Postfix Regex: ab.c.
Test Strings:
"abc" -> Expected: 1
"ab" -> Expected: 0
"abd" -> Expected: 0
"" (empty string) -> Expected: 0
2. Simple Alternation (|)
Infix Regex: a|b
Postfix Regex: ab|
Test Strings:
"a" -> Expected: 1
"b" -> Expected: 1
"c" -> Expected: 0
"ab" -> Expected: 0
3. Precedence Test (. vs |)
Infix Regex: ab|c (means (ab)|c)
Postfix Regex: ab.c|
Test Strings:
"ab" -> Expected: 1
"c" -> Expected: 1
"a" -> Expected: 0
"b" -> Expected: 0
"ac" -> Expected: 0
4. Grouping with Parentheses
Infix Regex: a(b|c)
Postfix Regex: abc|.
Test Strings:
"ab" -> Expected: 1
"ac" -> Expected: 1
"a" -> Expected: 0
"abc" -> Expected: 0
5. Zero or One (?)
Infix Regex: ab?c (means a(b?)c)
Postfix Regex: ab?c.
Test Strings:
"ac" -> Expected: 1 (the b appears zero times)
"abc" -> Expected: 1 (the b appears one time)
"abbc" -> Expected: 0
"c" -> Expected: 0
6. Zero or More (*)
Infix Regex: ab*c
Postfix Regex: ab*c.
Test Strings:
"ac" -> Expected: 1 (zero b's)
"abc" -> Expected: 1 (one b)
"abbbbc" -> Expected: 1 (many b's)
"ab" -> Expected: 0 (missing the c)
7. One or More (+)
Infix Regex: ab+c
Postfix Regex: ab+c.
Test Strings:
"ac" -> Expected: 0 (requires at least one b)
"abc" -> Expected: 1
"abbbbc" -> Expected: 1
"ab" -> Expected: 0
8. Complex Combination (The one from your code)
Infix Regex: a(b|c)*d
Postfix Regex: abc|*.d.
Test Strings:
"ad" -> Expected: 1 (the middle part matches zero times)
"abd" -> Expected: 1
"acd" -> Expected: 1
"abbccbd" -> Expected: 1 (any combination of b's and c's)
"acbd" -> Expected: 1
"a(b|c)*d" -> Expected: 0 (the regex characters are not literals here)
"axd" -> Expected: 0
 */
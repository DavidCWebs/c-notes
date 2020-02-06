# White Box Testing
This involves examining code to devise test cases.

A consideration in white box testing is _test coverage_: a description of how well test cases cover the different behaviours of the code.

White box testing and black box testing are not mutually exclusive.

You might start with a set of black box test cases, build the algorithm, and expand with white box test cases to reach the desired test coverage.

Coverage
--------
Three levels of test coverage: __statement coverage__, __decision coverage__, and __path coverage__.

### Statement Coverage
Every statement in the function is executed. This is a minimal starting point. Better to have a stronger coverage metric.

### Decision Coverage
A stronger level of coverage. All possible outcomes of decisions are exercised. For boolean tests, this means we construct a test case where the expression evaluates to true, and another where it evaluates to false. If we have a switch/case statement, we must construct at least one test case per choice in the case statement, plus one for the default case.

### Path Coverage
Test cases must span all possible valid paths through the control flow graph.

# Testing & Finding Bugs

Black Box Testing
-----------------
Tester considers only the expected behaviour of the function, with no access to implementation details.

Should consider what cases are likely to be error prone from the way the function behaves.

Black box tests can be written before writing the code to solve a problem. If you have a comprehensive test suite before starting development, it is less likely that testing will be neglected.

By thinking about corner cases in advance, less likely to make a mistake in developing & implementing an algorithm.

Seven Steps of Development
--------------------------

1. Work a specific instance by hand 
2. Write down the specific process
3. Generalise steps from 2
4. Test steps
5. Translate to code
6. Test programme
7. Debug programme

Designing Test Cases: Error Handling
------------------------------------
Cover every possible error case. Make sure programme handles "wrong" input properly.

If a programme requires N inputs, test with more than AND less than N.

Make sure test cases test one error. Testing two different error conditions requires two separate tests.

Test the boundaries: if a programme requires between 7 and 18 objects, test with 6, 7, 8, 17, 18 and 19 - ensure that the wrong number of elements is properly rejected, and the correct number of objects is accepted.

Test Boundaries
---------------
Off by One Bugs/Errors (OBOBs) are common: maybe the programmer used `<` where `<=` was required, causing an [off-by-one][1] error.

Designing Test Cases: Correctness
---------------------------------
Tests are not just about errors - they should also ensure that the algorithm handles valid inputs correctly (i.e. that it gives the right answer).

Think about:

* Special cases (e.g. Ace low straight in poker, where Ace is low).
* Requirements - consider potential misinterpretation, mis-implementation.
* Types - what if the implementer uses a data type that is too small, or the wrong type entirely?
* Off-by-one errors - if the algorithm involves counting, check the ends of ranges.

Inputs
------
* Numerical inputs, may be negative, zero, positive
* Sequences of data, test should include an empty set, a single element sequence, and a sequence with many elements.
* Characters: upper/lowercase letters, digits, punctuation, spaces, non-printable characters.

For many algorithms, there are problem specific categories -  testing a function related to prime numbers (e.g., isPrime), then you should consider prime and composite (not prime) numbers as input categories to cover.

When you combine two ways to categorize data, cover all combinations. For example, if you have a sequence of numbers, you should test with

* An empty list.
* A single element sequence with 0.
* A single element sequence with a negative number.
* A single element sequence with a positive number.
* Have each of negative, zero, and positive numbers included in many-element sequences.

If your algorithm gives a set of answers where you can list all possible ones (true/false, values from an enum, a string from a particular set, etc), then your test cases should ensure that you get every answer at least once.

If there are other conditions that you think are important, you should be sure that you get all possible answers for each of these conditions.

For example, if you are getting a yes/no answer for a numeric input, you should test with a negative number that gives yes, a negative number that gives no, a positive number that gives yes, a positive number that gives no, and zero (zero being only one input, will have one answer).

Test Harness
------------
Code which is not part of the main programme, which runs and tests the main parts of the code. Developing such infrastructure can be expensive, but may be a good investment - particularly when the project is large.

References
----------
* [Off-by-one errors][1]

[1]: https://en.wikipedia.org/wiki/Off-by-one_error

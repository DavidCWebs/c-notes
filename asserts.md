# Asserts
Check that invariants of the system are maintained during execution.

An __invariant__ is a property that should be true at a given point in the programme execution.

When you know an invariant should be true at a given point, you can write an `assert` statement to check it is true.

```c
// Check that expr is true:

asset(expr);
```

If the expression tested by `assert` is true, nothing happens - execution continues normally.

If the assertion fails - the tested expression returns `false`, the programme prints a message stating that an assertion failed, terminating the programme at this point.

If a programme has an error it should fail fast. The longer a program runs after an error, the more likely it is to give incorrect answers and the more difficult it is to debug.

Ideally an assert should fail immediately after an error, pinpointing the nature and location of the problem.

__A programme giving a wrong answer due to an unexpected error is significantly worse than a programme which detects the situation and crashes immediately.__

Performance Implications
------------------------
Performance implications of assert statements are negligible, especially on modern fast computers.

There may be situations where every ounce of performance is requires (e.g. embedded applications). In these situations, passing the `-DNDEBUG` option to the compiler turns off asserts in optimised code. 

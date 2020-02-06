# Debugging
Don't just debug in an ad hoc fashion, use the scientific method.

1. Observe a phenomenon 
2. Ask a question
3. Gather information, apply expert knowledge
4. Form a hypothesis 
5. Test hypothesis
6. If hypothesis is refuted, return to 3 and repeat
7. Accept hypothesis

Observation
-----------
Note phenomena - programme gives wrong answer or unexpected outputs given certain inputs.

Question
--------
Aim for focused questions:

* On which line does the programme crash?
* Why does the programme fail if the input is x?

Answering one question may lead to a new observation, and a new question in turn. The process is then repeated.

Gather Information & Apply Expert Knowledge
-------------------------------------------
Forming a good hypothesis is not necessarily easy.

Get information, use personal domain knowledge of particular programme, general programming knowledge.

You might use print statements to gather information but this has disadvantages - the programme must be recompiled, which can be time-consuming. In addition, the output may be overwhelming.

Using a debugger like `gdb` is a better option. When a programme is run inside a debugger, it runs as normal until it:

* Exits
* Crashes
* Reaches a breakpoint

### Breakpoints
A breakpoint is set on a particular line of code - it instructs the debugger to step execution at this point.

Breakpoints can be conditional - you can specify that the break should only occur if a specified conditional expression returns true.

Once stopped, you can examine the state of execution at this point - for example, print variables etc.

You can continue by executing one statement at a time, or continuing execution as normal. If you execute one statement at a time and you encounter a function call, you can either step over the call (ending up on the next line of the current function) or you can step into the function call and explore the internals of the called function.

This approach to gathering information is very flexible. If an anomaly is uncovered that suggests other things you need to explore, you can do this immediately.

Hypothesis
----------
Important to form a good hypothesis: 

* Testable - make specific predictions about behaviour given particular input (possibly test cases).
* Actionable - should provide an indication of how the problem might be fixed.

Accept or Reject Hypothesis
---------------------------
Test hypothesis thoroughly - don't accept too easily and check edge cases.

The danger is spending time "fixing" code based on a faulty hypothesis.

### Construct Test Cases
When a hyothesis suggests a result, construct test cases with relevant values and check programme behaviour against these.

Include test cases that do not meet the conditions to see if the initial assumption was too specific.

### Inspect Internal State of the Programme
Use the debugger to inspect the state of the programme to check the hypothesis.

### Use Asserts
If the hypothesis suggests that we are violating an invariant, use an assert to confirm this.

### Code Inspection
Sometimes a quick inspection can confirm the hypothesis.

### Hypothesis Rejection
Be clinical, not emotional. If you're worng, you're wrong.

__When rejecting a hypothesis, be wary of multiple errors - symptoms of these may be masking/interfering with the current problem.__

If you uncover a second error, you may need to defer investigation of the original error until the newly uncovered error is fixed.

# Assignment 1 Discussion

## Question a
- How did you test your code? What are the limitations of your testing?

I used the `catch2` library to write unit tests. The major limitation is that the unit tests doesn't
cover all the edge cases.

## Question b
- What approach did you take to document your functions and driver program?

All the function names are self-explanatory and the user functions are documented using Doxygen style comments.

## Question c
- How did you handle errors? Whow did you test your error handling strategy?

I used exceptions to handle errors. I tested the error handling strategy by writing unit tests that
trigger the exceptions.

## Question d
- Is your code robust to errors in the input files? How did you test this?

Yes, when reading the input file, every line is checked for errors and if an error is found, an exception is thrown
with a descriptive error message. I also created a test case for the method that reads the input file.

## Question e
- Are there any limitations in your implementation you are aware of? Do you have any ideas on how to address them?

Mathematical Limitations: Although the Chebychev functions are defined from -1 to 1, for now, it is only
integratable from -1 to 1. But it should be able to integrate from any interval within the range of -1 to 1.

Implementation Limitations: The current implementation is not optimized for performance, for example, the
vectors used are copied and I was not careful about avoiding unnecessary copies. The error handling could also be improved.

## Question f
- If you wanted to optimize the performance of your code, what approach would you take?

The following approaches can be taken to optimize the performance of the code:
1. Avoid unnecessary copies of vectors.
2. Use move semantics where possible.
3. Use some libraries instead of writing the code from scratch.
4. Use parallelism where possible.

## Question g
- How would you extend your code to two or more dimensions?

First, the mathematical operations are needed sorted out and they the class structure has to be modified, maybe
with templates. The integration method has to be modified to handle higher dimensions too since now it only
a simple sum operation.

## Question h
- Explain how you would handle a user defined function that takes additional parameters.

It could be done in many ways. For example, it could be done by using function templates and template arguments with tuples. For example the following
derived class of `ScalarFunction` could be used although it is complicated to implement:

```cpp
template <typename F, typename... Args>
class UserDefined : public ScalarFunction {
public:
    UserDefined(F f, Args... args)
        : func_(f), bound_args_(std::make_tuple(args...))
    {}
```

## Question i
- Are there any ways you could handle arbitrary functions that are defined at runtime by the user for example in an input file?

Yes, it could be done by using the following steps:
1. Parse the input file to get the function definition.
2. Use a predefined dictionary that maps a comprehensive set of the mathematical function names to the functions and call them with the arguments.
3. That way, the user can define any function at runtime.

There are libraries that can do this fast, easy and securely, for example, [`muParser`](https://beltoforion.de/en/muparser/).
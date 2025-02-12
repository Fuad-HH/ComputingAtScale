# Question 3

### (a)
> How did you test your code? What are the limitations of your testing?

I have tested the important methods: matrix file readers and writers, and matrix operational files.
`Catch2` is used to do the unit tests. Even though all the major methods are tested for both
passing and failing cases, the testing is still not comprehensive. Furthermore, the driver program is
not tested which could be done by regression testing. But it is manually checked by running the program
with different inputs. More details on running is in the README.md file.

### (b)
> What are the limitations of the matrix market format for dense matrices?

There are two formats to write matrices in the matrix market format: coordinate format and array format.
For dense matrices, the array format is used which just has one line of heading that specifies the number
formats and some other information and the next line contains the matrix size. The rest of the lines contain
the matrix elements. The limitations of this format are:

1. For large matrices, the file size will be large since the matrix elements are written in plain text.
2. There is no formatting for the matrix elements. So, it is hard to read the matrix.
3. Although there are functions to read or write the banner and matrix size, there is not function to read or write the elements.
4. The user has to verify if there is the correct number of elements in the file.

### (c)
> If you know the size of the matrices at compile time, how would you change your code to take advantage of this information?

1. I would use `std::array` instead of `std::vector` for the matrix elements to
allocate memory on the stack instead of the heap which is faster.
2. The testing would be easier since the matrix size is known at compile time.
3. Even loop unrolling could be done.

### (d) 
> Was your matrix representation row-major or column-major? How did you decide? Do you think
this will have an impact on performance?

The decision mainly depends on what kind of operations are done on the matrix. For example,
if we are doing A*B, then it is better to have row-major representation for A and column-major
representation for B since the algorithm reads the elements of A row-wise and B column-wise to
do the multiplication. Since I only implemented a single kind (row major), it doesn't matter
for this case if there isn't any special property of the first or the second matrix dimensions.
However, since it is also asked to implement matrix-vector multiplication, it is better to have
row-major representation for the matrix since the matrix comes first in the multiplication.

### (e)
> What approach did you take to document your functions and driver program?

When the function names are not self-explanatory, I have added comments to explain what the function does.
In case of errors, the functions always print an error message explaining what went wrong. The driver program
also prints usage if the user doesn't provide the correct number of arguments. And in case of errors, for example,
the files are not found, it prints detailed error messages before exiting. The README.md file also explains how to
run the program and some examples files are provided to play with.

### (f)
> Is your code robust to errors in the input files? How did you test this?

1. The `Matrix` class handles the data itself and the constructors and methods gatekeep the data so
that the data is always in a consistent state.
2. All the methods handles the common errors like file not found, unsupported file formats, wrong data size,
etc. and prints an error message before exiting.
3. The driver program also does the similar error handling.
4. The unit tests are done for some of the error cases as well.

### (g)
> Are there any limitations in your implementation you are aware of? Do you have any ideas on how to address them? e.g., what is the maximum size of the matrices you can handle?

1. The sizes are stored as `int` which limits the maximum size of the matrices and it can be error prone
since the size of int is platform dependent. It could be handled with types like `size_t` or `int64_t` etc.
2. The current matrix class only supports `double`. Templated class could be used to support other types.
3. The current matrix reader doesn't check if the given file is valid: contains the correct number of elements for
the given Matrix Market format file.
4. The tests could be more comprehensive to add more edge cases.

### (h)
> If you wanted to optimize the performance of your code, what approach would you take?

1. As already discussed, hybrid type (e.g. row major for A and column major for B) matrix representations could be used for matrix-matrix multiplication.
2. Parallelism could be used. For example, OpenMP could be easily used for the for loops.
3. Although data copying is minimized in the current implementation, it could be further minimized with a meticulous review.
4. There could be some other matrix operation methods that does the operations in-place if possible.
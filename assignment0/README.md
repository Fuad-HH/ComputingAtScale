# Assignment 0
>Course: _Computing at Scale_ \
>Date: _1/16/2025_\
>Name: **Fuad Hasan**


## Building Instructions
1. Open a Linux terminal
2. Clone the repository
3. Change the directory to the repository root and then `cd assignment0`
4. Load necessary compilers and tools: `cmake`, `make`, `gcc`, `g++`
5. Run `cmake -S . -B build`
6. Go to the build directory: `cd build`
7. Run `make -j4` and binary executables will be created in the `./bin` directory
8. Run `make test` to run the tests
9. Go to the `assests` directory: `cd ../assets` to see the `multiplicationDriver` executable working
10. From the `assets` directory, run, for example, `../build/bin/multiplicationDriver matrix1.txt vector1.txt 0` to see the output

Some additional examples:
```bash
../build/bin/multiplicationDriver matrix1.txt matrix2.txt 1
../build/bin/multiplicationDriver matrix3.txt vector1.txt 0
```

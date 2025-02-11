# Assignment 1

## Build Instructions
1. Clone or update (pull) the repository
2. Go to `assignment1` directory
```bash
cd assignment1
```
3. Run `cmake` to generate the build files
```bash
cmake -S . -B build
```
4. Build the project
```bash
cmake --build build -j 4
```
5. Run the tests
```bash
cd build
make test
```
or 
```bash
./test/unit_tests
```
6. Run the driver program from `assignment1` directory
```bash
./build/bin/polynomial_integrate tests/assets/x3_gauss_-1to5.txt
```

and the following output should be displayed:
```quote
Degree: 3
Integration Type: [0] Gauss-Legendre
Bounds: -1.000000 5.000000
Number of integration points: 4
Given coefficients: 0.000000 0.000000 0.000000 1.000000

=========> Integrating <=========
Integral: 156.000000
=================================
```

# Examples [![Codacy Badge](https://app.codacy.com/project/badge/Grade/aec4198787bc4d28a8bff6152c7c393e)](https://www.codacy.com/gh/ModernCPPBook/Examples/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=ModernCPPBook/Examples&amp;utm_campaign=Badge_Grade) [![CircleCI](https://circleci.com/gh/ModernCPPBook/Examples.svg?style=shield)](https://circleci.com/gh/ModernCPPBook/Examples)

## Building the examples

We use [CMake](https://cmake.org/) as the build system to compile the various examples. To compile the serial C++ examples, you can run the following commands in the root folder

```bash
mkdir build 
cd build 
cmake ..
make 
```

## Outline

### Mandelbrot and Julia sets

All the examples for the fractal sets of the book can be found [here](https://github.com/ModernCPPBook/Examples/tree/main/set). We start with the serial implementation. For the shared memory parallism the parallel algorithms of the C++ SL and asynchronous programming are used. Last, the distributed implementaiton using HPX.
 
### Appendix

All the examples for the Appendix of the book can be found [here](https://github.com/ModernCPPBook/Examples/tree/main/appendix). Here, we look into advanced C++ features like ranges, replacement new, move semantics, and lambda funcitons. 

### Benchmarks

The scripts to run the benchmarks are available [here](https://github.com/ModernCPPBook/Examples/tree/main/scripts). The code for the benchmarks which is not discussded in the books is available [here](). 

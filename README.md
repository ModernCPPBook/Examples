# Examples [![Codacy Badge](https://app.codacy.com/project/badge/Grade/aec4198787bc4d28a8bff6152c7c393e)](https://www.codacy.com/gh/ModernCPPBook/Examples/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=ModernCPPBook/Examples&amp;utm_campaign=Badge_Grade) [![CircleCI](https://circleci.com/gh/ModernCPPBook/Examples.svg?style=shield)](https://circleci.com/gh/ModernCPPBook/Examples)


## Outline

### Jupyter Notebooks

 
### Pure C++ examples

The examples using the Message Passing Interface ([MPI](https://www.open-mpi.org/)) or [OpenMP](https://www.openmp.org/) are not working in the Jupyter Notebooks. In addition, the distrbuted HPX examples are not working within Jupyter Notebooks. Therefore, the code is available as C++ files [here]().

The benchmarks can be build as


### Benchmarks

The slurm scripts to run the benchmarks are available [here](https://github.com/ModernCPPBook/Examples/tree/main/scripts). 

The code for the benchmarks which are not discussded in detail in the book are available in the [benchmark](https://github.com/ModernCPPBook/Examples/tree/main/benchmark) folder.

The benchmarks can be build as

```bash
cd benchmark
mkdir build 
cd build 
cmake -DWITH_OPENMP=ON ..
make 
```


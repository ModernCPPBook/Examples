# Examples [![Codacy Badge](https://app.codacy.com/project/badge/Grade/aec4198787bc4d28a8bff6152c7c393e)](https://www.codacy.com/gh/ModernCPPBook/Examples/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=ModernCPPBook/Examples&amp;utm_campaign=Badge_Grade) [![CircleCI](https://circleci.com/gh/ModernCPPBook/Examples.svg?style=shield)](https://circleci.com/gh/ModernCPPBook/Examples)

Code exmaples of the book "Parallel C++: Efficient and Scalable High-Performance Parallel Programming".  

## Outline

### Jupyter Notebooks

The folder [notebooks](https://github.com/ModernCPPBook/Examples/tree/main/notebooks) contains a Jupyter notebooks for each chapter of the book. 
In each notebook are all code examples of the Chapter. To run the notebooks a Docker image [stevenrbrandt/cxxxex-src](https://hub.docker.com/r/stevenrbrandt/cxxex-src) is available. 
To run the Docker image on your local computer, please use the following commands

```bash
curl -LO https://raw.githubusercontent.com/ stevenrbrandt/CxxExplorer/master/docker-compose.yml
docker-compose up -d
```

After the Docker image is started, a tab with the JupyterHub instance will be opened in your browser.
For more details, we refer to Chapter 1 of the book. Recall to use the C++ 17 cling kernel to compile
C++ code using the C++ Explorer [1].

### Pure C++ examples

The examples using the Message Passing Interface ([MPI](https://www.open-mpi.org/)) or [OpenMP](https://www.openmp.org/) are not working in the Jupyter Notebooks. In addition, the distrbuted HPX examples are not working within Jupyter Notebooks. Therefore, the code is available as C++ files [here]().

The benchmarks can be build as


### Benchmarks

The slurm scripts to run the benchmarks are available in the [scripts](https://github.com/ModernCPPBook/Examples/tree/main/scripts) folder. 

The code for the benchmarks which are not discussded in detail in the book are available in the [benchmark](https://github.com/ModernCPPBook/Examples/tree/main/benchmark) folder.

The benchmarks can be build as

```bash
cd benchmark
mkdir build 
cd build 
cmake -DWITH_OPENMP=ON ..
make 
```

## References

1. Diehl, Patrick, and Steven R. Brandt. "Interactive C++ code development using C++ Explorer and GitHub Classroom for educational purposes." Concurrency and Computation: Practice and Experience 35.18 (2023): e6893. [10.1002/cpe.6893](https://onlinelibrary.wiley.com/doi/abs/10.1002/cpe.6893)

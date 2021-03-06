[![Build and Test](https://github.com/iic-jku/dd_package/workflows/CI/badge.svg)](https://github.com/iic-jku/dd_package/actions?query=workflow%3A%22CI%22)
[![codecov](https://codecov.io/gh/iic-jku/dd_package/branch/master/graph/badge.svg)](https://codecov.io/gh/iic-jku/dd_package)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![toolset: JKQ](https://img.shields.io/badge/toolset-JKQ-blue)](https://github.com/iic-jku/jkq)


# JKQ DD Package - A Package for Decision Diagrams Written in C++

A DD package tailored to quantum computing by the [Institute for Integrated Circuits](http://iic.jku.at/eda/) at the [Johannes Kepler University Linz](https://jku.at). This package is part of the [JKQ toolset](https://github.com/iic-jku/jkq).

Developers: Alwin Zulehner, Stefan Hillmich, Lukas Burgholzer, and Robert Wille

With code from the QMDD implementation provided by Michael Miller (University of Victoria, Canada)
and Philipp Niemann (University of Bremen, Germany).

For more information, please visit [iic.jku.at/eda/research/quantum_dd](http://iic.jku.at/eda/research/quantum_dd).

If you have any questions, feel free to contact us via [iic-quantum@jku.at](mailto:iic-quantum@jku.at) or by creating an issue on [GitHub](https://github.com/iic-jku/dd_package/issues).

The old version of this package which does not use namespaces or classes can be found in the branch `non-oop`.

## Usage

This package caters primarily to our requirements regarding quantum-related functionality and, hence, may not be straightforward to use for other purposes.

A small example shows how to create set a single qubit in superposition.

```c++
#include <memory>
#include "DDpackage.h"

auto dd = std::make_unique<dd::Package>(); // Create new package instance
auto zero_state = dd->makeZeroState(1) ; // zero_state = |0>

/* Creating a DD requires three inputs:
 * 1. A 2x2 matrix describing a single-qubit operation (here: the Hadamard matrix)
 * 2. The number of qubits the DD will operate on (here: one qubit)
 * 3. A short array the length of the the number of qubits where the index is the qubit and the value is either
 *    -1 -> don't care; 0 -> negative control; 1 -> positive control; 2 -> target qubit
 *    In this example we only have a target.
 */
short line[1] = {2};
auto h_op = dd->makeGateDD(Hmat, 1, line);

// Multiplying the operation and the state results in a new state, here a single qubit in superposition
auto superposition = dd->multiply(h_op, zero_state); 
```

For implementing more complex functionality which requires garbage collection, be advised that you have to do the reference counting by hand. 

### System Requirements

Building (and running) is continuously tested under Linux, MacOS, and Windows using the [latest available system versions for GitHub Actions](https://github.com/actions/virtual-environments). 
However, the implementation should be compatible with any current C++ compiler supporting C++17 and a minimum CMake version of 3.14.

It is recommended (although not required) to have [GraphViz](https://www.graphviz.org) installed for visualization purposes.
  
### Setup, Build, and Run 

To start off, clone this repository using
```shell
git clone --recurse-submodules -j8 https://github.com/iic-jku/dd_package 
```
Note the `--recurse-submodules` flag. It is required to also clone all the required submodules. If you happen to forget passing the flag on your initial clone, you can initialize all the submodules by executing `git submodule update --init --recursive` in the main project directory.

Our projects use CMake as the main build configuration tool. Building a project using CMake is a two-stage process. First, CMake needs to be *configured* by calling
```shell 
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```
This tells CMake to search the current directory `.` (passed via `-S`) for a *CMakeLists.txt* file and process it into a directory `build` (passed via `-B`). 
The flag `-DCMAKE_BUILD_TYPE=Release` tells CMake to configure a *Release* build (as opposed to, e.g., a *Debug* build).

After configuring with CMake, the project can be built by calling
```shell
 cmake --build build --config Release
```
This tries to build the project in the `build` directory (passed via `--build`). 
Some operating systems and developer environments explicitly require a configuration to be set, which is why the `--config` flag is also passed to the build command. The flag `--parallel <NUMBER_OF_THREADS>` may be added to trigger a parallel build.

Building the project this way generates 
 - the library `libdd_package.a` (Unix) / `dd_package.lib` (Windows) in the `build/src` folder
 - a test executable `dd_package_test` containing a small set of unit tests in the `build/test` folder
 - a small demo example executable `dd_package_example` in the `build/test` directory.

You can link against the library built by this project in other CMake project using the `JKQ::DDpackage` target.

## Reference

If you use the DD package for your research, we will be thankful if you refer to it by citing the following publication:

```
@article{zulehner2019package,
    title={How to Efficiently Handle Complex Values? Implementing Decision Diagrams for Quantum Computing},
    author={Zulehner, Alwin and Hillmich, Stefan and Wille, Robert},
    journal={International Conference on Computer Aided Design (ICCAD)},
    year={2019}
}
```

## Further Information

The following papers provide further information on different aspects of representing states and operation in the quantum realm.

- For the representation of unitary matrices and state vectors (with a particular focus on simulation and measurement):  
A. Zulehner and R. Wille. Advanced Simulation of Quantum Computations. IEEE Transactions on Computer Aided Design of Integrated Circuits and Systems (TCAD), 2018.
- For the representation and manipulation of unitary matrices (including proof of canonicy, multi-qubit systems, etc):  
P. Niemann, R. Wille, D. M. Miller, M. A. Thornton, and R. Drechsler. QMDDs: Efficient Quantum Function Representation and Manipulation. IEEE Transactions on Computer Aided Design of Integrated Circuits and Systems (TCAD), 35(1):86-99, 2016.
- The paper describing this decision diagram package (with a special focus on the representation of complex numbers):  
A. Zulehner, S. Hillmich and R. Wille. How to Efficiently Handle Complex Values? Implementing Decision Diagrams for Quantum Computing. The IEEE/ACM International Conference on Computer-Aided Design (ICCAD). 2019

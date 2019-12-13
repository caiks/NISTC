# MNIST - handwritten digits

This repository contains tests of the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC) using data from the [MNIST dataset](http://yann.lecun.com/exdb/mnist/). The AlignmentRepaC repository is a fast C++ implementation of some of the *practicable inducers* described in the paper *The Theory and Practice of Induction by Alignment* at https://greenlake.co.uk/. 

<!--
## Documentation

There is an analysis of this dataset [here](https://greenlake.co.uk/pages/dataset_C_NIST). 
-->
## Installation

The `NIST` executables require the `AlignmentRepa` module which is in the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC). See the AlignmentRepaC repository for installation instructions of the C++ compiler.

Then download the zip files or use git to get the NISTC repository and the underlying rapidjson, AlignmentC and AlignmentRepaC repositories -
```
cd
git clone https://github.com/Tencent/rapidjson.git
git clone https://github.com/caiks/AlignmentC.git
git clone https://github.com/caiks/AlignmentRepaC.git
git clone https://github.com/caiks/NISTC.git
```
Then download the dataset files, for example -
```
cd NISTC
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
gunzip *.gz
```

## Build

Ubuntu debug -
```sh
cd AlignmentC

g++ -I../rapidjson/include -std=gnu++17 -g -c AlignmentUtil.cpp Alignment.cpp AlignmentApprox.cpp AlignmentAeson.cpp 

cd ../AlignmentRepaC

g++ -I../rapidjson/include -I../AlignmentC -std=gnu++17 -g -c AlignmentRepa.cpp AlignmentAesonRepa.cpp AlignmentRandomRepa.cpp AlignmentPracticableRepa.cpp AlignmentPracticableIORepa.cpp

cd ../NISTC

g++ -I../rapidjson/include -I../AlignmentC -I../AlignmentRepaC -std=gnu++17 -g -o main main.cpp NISTDev.cpp ../AlignmentRepaC/AlignmentRepa.o ../AlignmentRepaC/AlignmentAesonRepa.o ../AlignmentRepaC/AlignmentRandomRepa.o ../AlignmentRepaC/AlignmentPracticableRepa.o ../AlignmentRepaC/AlignmentPracticableIORepa.o ../AlignmentC/AlignmentUtil.o ../AlignmentC/Alignment.o ../AlignmentC/AlignmentApprox.o ../AlignmentC/AlignmentAeson.o

./main induce model100 >NIST_model100.log

```
Ubuntu release -
```sh
cd AlignmentC

g++ -I../rapidjson/include -std=gnu++17 -O3 -c AlignmentUtil.cpp Alignment.cpp AlignmentApprox.cpp AlignmentAeson.cpp 

cd ../AlignmentRepaC

g++ -I../rapidjson/include -I../AlignmentC -std=gnu++17 -O3 -c AlignmentRepa.cpp AlignmentAesonRepa.cpp AlignmentRandomRepa.cpp AlignmentPracticableRepa.cpp AlignmentPracticableIORepa.cpp

cd ../NISTC

g++ -I../rapidjson/include -I../AlignmentC -I../AlignmentRepaC -std=gnu++17 -O3 -o main main.cpp NISTDev.cpp ../AlignmentRepaC/AlignmentRepa.o ../AlignmentRepaC/AlignmentAesonRepa.o ../AlignmentRepaC/AlignmentRandomRepa.o ../AlignmentRepaC/AlignmentPracticableRepa.o ../AlignmentRepaC/AlignmentPracticableIORepa.o ../AlignmentC/AlignmentUtil.o ../AlignmentC/Alignment.o ../AlignmentC/AlignmentApprox.o ../AlignmentC/AlignmentAeson.o

./main induce model100 >NIST_model100.log

```
Windows debug -
```sh
cd AlignmentC-master

cl -I../rapidjson-master/include /EHsc /DEBUG /Zi /c AlignmentUtil.cpp Alignment.cpp AlignmentApprox.cpp AlignmentAeson.cpp 

cd ..\AlignmentRepaC-master

cl -IC:../rapidjson-master/include -I../AlignmentC-master /EHsc /DEBUG /Zi main.cpp AlignmentRepa.cpp AlignmentAesonRepa.cpp AlignmentRandomRepa.cpp AlignmentPracticableRepa.cpp AlignmentPracticableIORepa.cpp ../AlignmentC-master/AlignmentUtil.obj ../AlignmentC-master/Alignment.obj ../AlignmentC-master/AlignmentApprox.obj ../AlignmentC-master/AlignmentAeson.obj 

cd ..\NISTC-master

cl -IC:../rapidjson-master/include -I../AlignmentC-master -I../AlignmentRepaC-master /EHsc /DEBUG /Zi main.cpp NISTDev.cpp ../AlignmentRepaC-master/AlignmentRepa.obj ../AlignmentRepaC-master/AlignmentAesonRepa.obj ../AlignmentRepaC-master/AlignmentRandomRepa.obj ../AlignmentRepaC-master/AlignmentPracticableRepa.obj ../AlignmentRepaC-master/AlignmentPracticableIORepa.obj ../AlignmentC-master/AlignmentUtil.obj ../AlignmentC-master/Alignment.obj ../AlignmentC-master/AlignmentApprox.obj ../AlignmentC-master/AlignmentAeson.obj 

main induce model100 >NIST_model100.log
```
Windows release -
```sh
cd AlignmentC-master

cl -I../rapidjson-master/include /EHsc /O2 /c AlignmentUtil.cpp Alignment.cpp AlignmentApprox.cpp AlignmentAeson.cpp 

cd ..\AlignmentRepaC-master

cl -IC:../rapidjson-master/include -I../AlignmentC-master /EHsc /O2 /c AlignmentRepa.cpp AlignmentAesonRepa.cpp AlignmentRandomRepa.cpp AlignmentPracticableRepa.cpp AlignmentPracticableIORepa.cpp

cd ..\NISTC-master

cl -IC:../rapidjson-master/include -I../AlignmentC-master -I../AlignmentRepaC-master /EHsc /O2 main.cpp NISTDev.cpp ../AlignmentRepaC-master/AlignmentRepa.obj ../AlignmentRepaC-master/AlignmentAesonRepa.obj ../AlignmentRepaC-master/AlignmentRandomRepa.obj ../AlignmentRepaC-master/AlignmentPracticableIORepa.obj ../AlignmentRepaC-master/AlignmentPracticableRepa.obj ../AlignmentC-master/AlignmentUtil.obj ../AlignmentC-master/Alignment.obj ../AlignmentC-master/AlignmentApprox.obj ../AlignmentC-master/AlignmentAeson.obj 

main induce model100 >NIST_model100.log
```


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

g++ -pthread -I../rapidjson/include -I../AlignmentC -I../AlignmentRepaC -std=gnu++17 -g -o main main.cpp NISTDev.cpp ../AlignmentRepaC/AlignmentRepa.o ../AlignmentRepaC/AlignmentAesonRepa.o ../AlignmentRepaC/AlignmentRandomRepa.o ../AlignmentRepaC/AlignmentPracticableRepa.o ../AlignmentRepaC/AlignmentPracticableIORepa.o ../AlignmentC/AlignmentUtil.o ../AlignmentC/Alignment.o ../AlignmentC/AlignmentApprox.o ../AlignmentC/AlignmentAeson.o


```
Ubuntu release -
```sh
cd AlignmentC

g++ -I../rapidjson/include -std=gnu++17 -O3 -c AlignmentUtil.cpp Alignment.cpp AlignmentApprox.cpp AlignmentAeson.cpp 

cd ../AlignmentRepaC

g++ -I../rapidjson/include -I../AlignmentC -std=gnu++17 -O3 -c AlignmentRepa.cpp AlignmentAesonRepa.cpp AlignmentRandomRepa.cpp AlignmentPracticableRepa.cpp AlignmentPracticableIORepa.cpp

cd ../NISTC

g++ -pthread -I../rapidjson/include -I../AlignmentC -I../AlignmentRepaC -std=gnu++17 -O3 -o main main.cpp NISTDev.cpp ../AlignmentRepaC/AlignmentRepa.o ../AlignmentRepaC/AlignmentAesonRepa.o ../AlignmentRepaC/AlignmentRandomRepa.o ../AlignmentRepaC/AlignmentPracticableRepa.o ../AlignmentRepaC/AlignmentPracticableIORepa.o ../AlignmentC/AlignmentUtil.o ../AlignmentC/Alignment.o ../AlignmentC/AlignmentApprox.o ../AlignmentC/AlignmentAeson.o


```
Windows debug -
```sh
cd AlignmentC-master

cl -I../rapidjson-master/include /EHsc /DEBUG /Zi /c AlignmentUtil.cpp Alignment.cpp AlignmentApprox.cpp AlignmentAeson.cpp 

cd ..\AlignmentRepaC-master

cl -IC:../rapidjson-master/include -I../AlignmentC-master /EHsc /DEBUG /Zi main.cpp AlignmentRepa.cpp AlignmentAesonRepa.cpp AlignmentRandomRepa.cpp AlignmentPracticableRepa.cpp AlignmentPracticableIORepa.cpp ../AlignmentC-master/AlignmentUtil.obj ../AlignmentC-master/Alignment.obj ../AlignmentC-master/AlignmentApprox.obj ../AlignmentC-master/AlignmentAeson.obj 

cd ..\NISTC-master

cl -IC:../rapidjson-master/include -I../AlignmentC-master -I../AlignmentRepaC-master /EHsc /DEBUG /Zi main.cpp NISTDev.cpp ../AlignmentRepaC-master/AlignmentRepa.obj ../AlignmentRepaC-master/AlignmentAesonRepa.obj ../AlignmentRepaC-master/AlignmentRandomRepa.obj ../AlignmentRepaC-master/AlignmentPracticableRepa.obj ../AlignmentRepaC-master/AlignmentPracticableIORepa.obj ../AlignmentC-master/AlignmentUtil.obj ../AlignmentC-master/Alignment.obj ../AlignmentC-master/AlignmentApprox.obj ../AlignmentC-master/AlignmentAeson.obj 


```
Windows release -
```sh
cd AlignmentC-master

cl -I../rapidjson-master/include /EHsc /O2 /c AlignmentUtil.cpp Alignment.cpp AlignmentApprox.cpp AlignmentAeson.cpp 

cd ..\AlignmentRepaC-master

cl -IC:../rapidjson-master/include -I../AlignmentC-master /EHsc /O2 /c AlignmentRepa.cpp AlignmentAesonRepa.cpp AlignmentRandomRepa.cpp AlignmentPracticableRepa.cpp AlignmentPracticableIORepa.cpp

cd ..\NISTC-master

cl -IC:../rapidjson-master/include -I../AlignmentC-master -I../AlignmentRepaC-master /EHsc /O2 main.cpp NISTDev.cpp ../AlignmentRepaC-master/AlignmentRepa.obj ../AlignmentRepaC-master/AlignmentAesonRepa.obj ../AlignmentRepaC-master/AlignmentRandomRepa.obj ../AlignmentRepaC-master/AlignmentPracticableIORepa.obj ../AlignmentRepaC-master/AlignmentPracticableRepa.obj ../AlignmentC-master/AlignmentUtil.obj ../AlignmentC-master/Alignment.obj ../AlignmentC-master/AlignmentApprox.obj ../AlignmentC-master/AlignmentAeson.obj 


```

## Usage

```
main induce model100 >model100.log

main bitmap model100

main test model100
model: model100
train size: 60000
model cardinality: 2600
derived  cardinality: 510
underlying cardinality: 375
test size: 10000
effective size: 10000
matches: 6439

main induce model35 >NIST_model35.log

main bitmap model35

main test model35
model: model35
train size: 60000
model cardinality: 4930
derived  cardinality: 650
underlying cardinality: 537
test size: 10000
effective size: 10000
matches: 6215

main induce model100_1 >model100_1.log

main test model100_1

main induce model100_2 >model100_2.log

main test model100_2
model: model100_2
train size: 60000
model cardinality: 560
derived  cardinality: 168
underlying cardinality: 233
test size: 10000
effective size: 10000
matches: 7854

main induce model101 >model101.log

main induce model102 >model102.log

main test model102
model: model102
train size: 60000
model cardinality: 13556
derived  cardinality: 295
underlying cardinality: 647
test size: 10000
effective size: 9997
matches: 6079

main induce model103 >model103.log

main induce model104 >model104.log

main test model104
model: model104
train size: 60000
model cardinality: 8976
derived  cardinality: 321
underlying cardinality: 659
test size: 10000
effective size: 9999
matches: 6263

main induce model105 >model105.log

main test model105
model: model105
train size: 60000
model cardinality: 1981
derived  cardinality: 362
underlying cardinality: 315
test size: 10000
effective size: 9987
matches: 6522

main induce model106 >model106.log

main test model106
model: model106
train size: 60000
model cardinality: 15403
derived  cardinality: 2425
underlying cardinality: 507
test size: 10000
effective size: 9431
matches: 7252

main induce model106_1 >model106_1.log

main test model106_1
model: model106_1
train size: 60000
model cardinality: 4216
derived  cardinality: 1934
underlying cardinality: 377
test size: 10000
effective size: 10000
matches: 8471

main induce model106_2 >model106_2.log

main test model106_2
model: model106_2
train size: 60000
model cardinality: 4276
derived  cardinality: 2001
underlying cardinality: 375
test size: 10000
effective size: 10000
matches: 8404

main induce model106_3 >model106_3.log

main test model106_3

main induce model107 >model107.log

main test model107
model: model107
train size: 60000
model cardinality: 2779
derived  cardinality: 698
underlying cardinality: 293
test size: 10000
effective size: 10000
matches: 4550

main induce model108 >model108.log

main test model108
model: model108
train size: 60000
model cardinality: 254
derived  cardinality: 128
underlying cardinality: 90
test size: 10000
effective size: 10000
matches: 7737

main induce model109 >model109.log

main test model109
model: model109
train size: 60000
model cardinality: 595
derived  cardinality: 242
underlying cardinality: 213
test size: 10000
effective size: 10000
matches: 7876

main test model109
model: model109
train size: 60000
model cardinality: 593
derived  cardinality: 257
underlying cardinality: 229
test size: 10000
effective size: 10000
matches: 7761

main induce model110 >model110.log

main test model110
model: model110
train size: 60000
model cardinality: 6159
derived  cardinality: 2100
underlying cardinality: 523
test size: 10000
effective size: 9998
matches: 8745

main induce model111 >model111.log

main test model111
model: model111
train size: 60000
model cardinality: 19724
derived  cardinality: 1024
underlying cardinality: 649
test size: 10000
effective size: 10000
matches: 8753

main induce model112 >model112.log

main induce model113 >model113.log

main test model113
model: model113
train size: 60000
model cardinality: 29253
derived  cardinality: 2048
underlying cardinality: 671
test size: 10000
effective size: 10000
matches: 8902

main induce model114 >model114.log

main test model114
model: NIST_model114
train size: 60000
model cardinality: 29001
derived  cardinality: 2048
underlying cardinality: 667
test size: 10000
effective size: 10000
matches: 8905

main induce model115 >model115.log

main test model115
model: model115
train size: 60000
model cardinality: 37479
derived  cardinality: 4244
underlying cardinality: 671
test size: 10000
effective size: 10000
matches: 8889

main induce model115_1 >model115_1.log

main test model115_1
model: model115_1
train size: 60000
model cardinality: 59907
derived  cardinality: 6138
underlying cardinality: 676
test size: 10000
effective size: 10000
matches: 8386

main induce model116 >model116.log

main induce model117 >model117.log

main bitmap_10x10 model101 10

main induce model118 >model118.log

main bitmap_10x10 model118 1

```


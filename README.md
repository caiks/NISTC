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
Then download the dataset files to a workspace, for example -
```
mkdir NISTC_ws
cd NISTC_ws
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
gunzip *.gz
cd ..

```

## Build

Ubuntu debug -
```sh
mkdir AlignmentC_build AlignmentRepaC_build NISTC_build
cd NISTC_build
cmake -DCMAKE_BUILD_TYPE=DEBUG ../NISTC
make

```
Ubuntu release -
```sh
mkdir AlignmentC_build AlignmentRepaC_build NISTC_build
cd NISTC_build
cmake -DCMAKE_BUILD_TYPE=RELEASE ../NISTC
make

```
Windows debug -
```sh
mkdir AlignmentC_build AlignmentRepaC_build NISTC_build
cd /d NISTC_build
"C:\Program Files\CMake\bin\cmake" -G "Visual Studio 14 2015" -A x64 ../NISTC
"C:\Program Files\CMake\bin\cmake" --build . --config Debug --target NISTC

```
Windows release -
```sh
mkdir AlignmentC_build AlignmentRepaC_build NISTC_build
cd /d NISTC_build
"C:\Program Files\CMake\bin\cmake" -G "Visual Studio 14 2015" -A x64 ../NISTC
"C:\Program Files\CMake\bin\cmake" --build . --config Release --target NISTC

```

## Usage

Ubuntu -
```sh
cd ../NISTC_ws
ln -s ../NISTC_build/NISTC NISTC
/usr/bin/time -v NISTC induce model112 >model112.log 2>&1

```
Windows debug -
```sh
cd /d ..\NISTC_ws
..\NISTC_build\Debug\NISTC.exe induce model112 >model112.log

```
Windows release -
```sh
cd /d ..\NISTC_ws
..\NISTC_build\Release\NISTC.exe induce model112 >model112.log

```

## Examples

Some of these examples may be viewed in [NISTC_ws repository](https://github.com/caiks/NISTC_ws),

```
NISTC induce model100 >model100.log

NISTC bitmap model100

NISTC test model100
model: model100
train size: 60000
model cardinality: 2600
derived  cardinality: 510
underlying cardinality: 375
test size: 10000
effective size: 10000
matches: 6439

NISTC induce model35 >NIST_model35.log

NISTC bitmap model35

NISTC test model35
model: model35
train size: 60000
model cardinality: 4930
derived  cardinality: 650
underlying cardinality: 537
test size: 10000
effective size: 10000
matches: 6215

NISTC induce model100_1 >model100_1.log

NISTC test model100_1

NISTC induce model100_2 >model100_2.log

NISTC test model100_2
model: model100_2
train size: 60000
model cardinality: 560
derived  cardinality: 168
underlying cardinality: 233
test size: 10000
effective size: 10000
matches: 7854

NISTC induce model101 >model101.log

NISTC induce model102 >model102.log

NISTC test model102
model: model102
train size: 60000
model cardinality: 13556
derived  cardinality: 295
underlying cardinality: 647
test size: 10000
effective size: 9997
matches: 6079

NISTC induce model103 >model103.log

NISTC induce model104 >model104.log

NISTC test model104
model: model104
train size: 60000
model cardinality: 8976
derived  cardinality: 321
underlying cardinality: 659
test size: 10000
effective size: 9999
matches: 6263

NISTC induce model105 >model105.log

NISTC test model105
model: model105
train size: 60000
model cardinality: 1981
derived  cardinality: 362
underlying cardinality: 315
test size: 10000
effective size: 9987
matches: 6522

NISTC induce model106 >model106.log

NISTC test model106
model: model106
train size: 60000
model cardinality: 15403
derived  cardinality: 2425
underlying cardinality: 507
test size: 10000
effective size: 9431
matches: 7252

NISTC induce model106_1 >model106_1.log

NISTC test model106_1
model: model106_1
train size: 60000
model cardinality: 4216
derived  cardinality: 1934
underlying cardinality: 377
test size: 10000
effective size: 10000
matches: 8471

NISTC induce model106_2 >model106_2.log

NISTC test model106_2
model: model106_2
train size: 60000
model cardinality: 4276
derived  cardinality: 2001
underlying cardinality: 375
test size: 10000
effective size: 10000
matches: 8404

NISTC induce model106_2_p 4 >model106_2_p.log

NISTC test model106_2_p
model: model106_2_p
train size: 60000
model cardinality: 4399
derived  cardinality: 1995
underlying cardinality: 373
test size: 10000
effective size: 10000
matches: 8415

NISTC induce model106_3 >model106_3.log

NISTC test model106_3

NISTC induce model107 >model107.log

NISTC test model107
model: model107
train size: 60000
model cardinality: 2779
derived  cardinality: 698
underlying cardinality: 293
test size: 10000
effective size: 10000
matches: 4550

NISTC induce model108 >model108.log

NISTC test model108
model: model108
train size: 60000
model cardinality: 254
derived  cardinality: 128
underlying cardinality: 90
test size: 10000
effective size: 10000
matches: 7737

NISTC induce model109 >model109.log

NISTC test model109
model: model109
train size: 60000
model cardinality: 595
derived  cardinality: 242
underlying cardinality: 213
test size: 10000
effective size: 10000
matches: 7876

NISTC test model109
model: model109
train size: 60000
model cardinality: 593
derived  cardinality: 257
underlying cardinality: 229
test size: 10000
effective size: 10000
matches: 7761

NISTC induce model110 >model110.log

NISTC test model110
model: model110
train size: 60000
model cardinality: 6159
derived  cardinality: 2100
underlying cardinality: 523
test size: 10000
effective size: 9998
matches: 8745

NISTC induce model111 >model111.log

NISTC test model111
model: model111
train size: 60000
model cardinality: 19724
derived  cardinality: 1024
underlying cardinality: 649
test size: 10000
effective size: 10000
matches: 8753

NISTC induce model112 >model112.log

NISTC induce model113 >model113.log

NISTC test model113
model: model113
train size: 60000
model cardinality: 29253
derived  cardinality: 2048
underlying cardinality: 671
test size: 10000
effective size: 10000
matches: 8902

NISTC induce model114 >model114.log

NISTC test model114
model: NIST_model114
train size: 60000
model cardinality: 29001
derived  cardinality: 2048
underlying cardinality: 667
test size: 10000
effective size: 10000
matches: 8905

NISTC induce model115 >model115.log

NISTC test model115
model: model115
train size: 60000
model cardinality: 37479
derived  cardinality: 4244
underlying cardinality: 671
test size: 10000
effective size: 10000
matches: 8889

NISTC induce model115_1 >model115_1.log

NISTC test model115_1
model: model115_1
train size: 60000
model cardinality: 59907
derived  cardinality: 6138
underlying cardinality: 676
test size: 10000
effective size: 10000
matches: 8386

NISTC induce model116 >model116.log

NISTC induce model117 >model117.log

NISTC bitmap_10x10 model101 10

NISTC induce model118 >model118.log

NISTC bitmap_10x10 model118 1

NISTC induce model119 32 >model119.log

NISTC affine_test model119
model: model119
train size: 600000
model cardinality: 89164
derived  cardinality: 16384
underlying cardinality: 676
test size: 10000
effective size: 10000
matches: 9286

NISTC induce model120 16 >model120_16.log

NISTC test model120
model: model120
train size: 60000
model cardinality: 34522
derived  cardinality: 2048
underlying cardinality: 667
test size: 10000
effective size: 10000
matches: 8892

```


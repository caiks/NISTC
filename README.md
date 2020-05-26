# MNIST - handwritten digits

This repository contains tests of the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC) using data from the [MNIST dataset](http://yann.lecun.com/exdb/mnist/). The AlignmentRepaC repository is a fast C++ implementation of some of the *practicable inducers* described in the paper *The Theory and Practice of Induction by Alignment* at https://greenlake.co.uk/. 

<!--
## Documentation

There is an analysis of this dataset [here](https://greenlake.co.uk/pages/dataset_C_NIST). 
-->
## Download

The `NIST` executables require the `AlignmentRepa` module which is in the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC). See the AlignmentRepaC repository for installation instructions of the C++ compiler.

Download the zip files or use git to get the `NISTC` repository and the underlying `rapidjson`, `AlignmentC` and `AlignmentRepaC` repositories -
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
export PATH=$PATH:./
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
model cardinality: 2121
derived  cardinality: 746
underlying cardinality: 262
test size: 10000
effective size: 9999
matches: 5475

NISTC induce model100_p 4 >model100_p.log

NISTC test model100_p
model: model100_p
train size: 60000
model cardinality: 2109
derived  cardinality: 740
underlying cardinality: 259
test size: 10000
effective size: 9999
matches: 5451

NISTC induce model35 >NIST_model35.log

NISTC bitmap model35

NISTC test model35
model: model35
train size: 60000
model cardinality: 4107
derived  cardinality: 905
underlying cardinality: 287
test size: 10000
effective size: 10000
matches: 5919

NISTC induce model100_1 >model100_1.log

NISTC test model100_1

NISTC condition model100_2 >model100_2.log

NISTC test model100_2
model: model100_2
train size: 60000
model cardinality: 474
derived  cardinality: 253
underlying cardinality: 148
test size: 10000
effective size: 10000
matches: 7288

NISTC induce model101 >model101.log

NISTC induce model102 >model102.log

NISTC test model102
model: model102
train size: 60000
model cardinality: 10628
derived  cardinality: 312
underlying cardinality: 668
test size: 10000
effective size: 9998
matches: 6016

NISTC induce model103 >model103.log

NISTC induce model104 >model104.log

NISTC test model104
model: model104
train size: 60000
model cardinality: 8930
derived  cardinality: 313
underlying cardinality: 657
test size: 10000
effective size: 9999
matches: 5927

NISTC induce model105 >model105.log

NISTC test model105
model: model105
train size: 60000
model cardinality: 1923
derived  cardinality: 362
underlying cardinality: 313
test size: 10000
effective size: 9981
matches: 6546

NISTC induce model106 >model106.log

NISTC test model106
model: model106
train size: 60000
model cardinality: 15436
derived  cardinality: 2425
underlying cardinality: 505
test size: 10000
effective size: 9456
matches: 7204

NISTC induce model106_p 4 >model106_p.log

NISTC test model106_p
model: model106_p
train size: 60000
model cardinality: 15475
derived  cardinality: 2419
underlying cardinality: 505
test size: 10000
effective size: 9420
matches: 7231

NISTC condition model106_1 >model106_1.log

NISTC test model106_1
model: model106_1
train size: 60000
model cardinality: 4376
derived  cardinality: 1851
underlying cardinality: 380
test size: 10000
effective size: 9999
matches: 8531

NISTC condition model106_2 >model106_2.log

NISTC test model106_2
model: model106_2
train size: 60000
model cardinality: 4131
derived  cardinality: 1998
underlying cardinality: 378
test size: 10000
effective size: 10000
matches: 8409

NISTC condition model106_2_p 4 >model106_2_p.log

NISTC test model106_2_p
model: model106_2_p
train size: 60000
model cardinality: 4369
derived  cardinality: 1934
underlying cardinality: 362
test size: 10000
effective size: 9999
matches: 8421

NISTC condition model106_3 >model106_3.log

NISTC test model106_3
model: model106_3
train size: 60000
model cardinality: 514
derived  cardinality: 246
underlying cardinality: 209
test size: 10000
effective size: 10000
matches: 6736

NISTC induce model107 >model107.log

NISTC test model107
model: model107
train size: 60000
model cardinality: 2793
derived  cardinality: 808
underlying cardinality: 231
test size: 10000
effective size: 10000
matches: 3921

NISTC condition model108 >model108.log

NISTC test model108
model: model108
train size: 60000
model cardinality: 254
derived  cardinality: 128
underlying cardinality: 90
test size: 10000
effective size: 10000
matches: 7737

NISTC condition model109 >model109.log

NISTC test model109
model: model109
train size: 60000
model cardinality: 762
derived  cardinality: 250
underlying cardinality: 247
test size: 10000
effective size: 10000
matches: 7906

NISTC condition model110 >model110.log

NISTC test model110
model: model110
train size: 60000
model cardinality: 6159
derived  cardinality: 2100
underlying cardinality: 523
test size: 10000
effective size: 9998
matches: 8745

NISTC condition model111 >model111.log

NISTC test model111
model: model111
train size: 60000
model cardinality: 16956
derived  cardinality: 1024
underlying cardinality: 640
test size: 10000
effective size: 10000
matches: 8840

NISTC induce model112 >model112.log

NISTC condition model113 >model113.log

NISTC test model113
model: model113
train size: 60000
model cardinality: 20299
derived  cardinality: 2048
underlying cardinality: 665
test size: 10000
effective size: 10000
matches: 8979

NISTC condition model114 >model114.log

NISTC test model114
model: model114
train size: 60000
model cardinality: 20241
derived  cardinality: 2048
underlying cardinality: 665
test size: 10000
effective size: 10000
matches: 8908

NISTC condition model115 >model115.log

NISTC test model115
model: model115
train size: 60000
model cardinality: 37479
derived  cardinality: 4244
underlying cardinality: 671
test size: 10000
effective size: 10000
matches: 8889

NISTC condition model115_1 >model115_1.log

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

# note that model119 requires 100GB memory
NISTC condition model119 32 >model119.log

NISTC affine_test model119
model: model119
train size: 600000
model cardinality: 89164
derived  cardinality: 16384
underlying cardinality: 676
test size: 10000
effective size: 10000
matches: 9286

NISTC condition model120 16 >model120_16.log

NISTC test model120
model: model120
train size: 60000
model cardinality: 23018
derived  cardinality: 2048
underlying cardinality: 669
test size: 10000
effective size: 10000
matches: 8923

```


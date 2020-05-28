# MNIST - handwritten digits

This repository contains tests of the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC) using data from the [MNIST dataset](http://yann.lecun.com/exdb/mnist/). The AlignmentRepaC repository is a fast C++ implementation of some of the *practicable inducers* described in the paper *The Theory and Practice of Induction by Alignment* at https://greenlake.co.uk/. 

## Sections

[Download](#Download)

[Build](#Build)

[Usage](#Usage)

[Discussion](#Discussion)

<a name="Download"></a>

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

<a name="Build"></a>

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

<a name="Usage"></a>

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

<a name="Discussion"></a>

## Discussion

For a detailed discussion of the problem domain see the [Haskell implementation](https://github.com/caiks/NIST) or the [Python implementation](https://github.com/caiks/NISTPy). 

The tests and *models* in the NISTC repository are different from those of the previous implementations. The C++ implementation is the best solution for implementing very large *models*. The discussion below compares the *models* by *label accuracy* and by a proxy for the *size-volume scaled component size cardinality sum relative entropy* which substitutes a *scaled shuffle* for the *cartesian*. As the *shuffle* is *scaled* the *relative entropy* gradually converges, so it is a reasonable proxy for the *model likelihood*.
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

NISTC entropy model100 
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 52891.2

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

NISTC entropy model100_p 
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 52801.4

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

NISTC entropy model35 
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 56646.6
```
*Model* 35 is common to the other implementations and runs in around 2065s in C++. *Model* 100 has more restricted *induction* parameters and takes only 15s to run but obtains quite good *accuracy* and *relative entropy*. 
```
NISTC induce model100_1 >model100_1.log

NISTC test model100_1
model: model100_1
train size: 60000
model cardinality: 2500
derived  cardinality: 532
underlying cardinality: 364
test size: 10000
effective size: 10000
matches: 6288

NISTC entropy model100_1 
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 62678.7
```
*Model* 100_1 is similar to *model* 100 but uses the `znnmax` parameter to sub-select the *substrate* by *perimeter entropy*.
```
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

NISTC entropy model100_2 
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 21624.1
```
*Model* 100_2 is *conditioned* on the *substrate* rather then *induced*. It has better *accuracy* but worse *likelihood*.
```
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

NISTC entropy model102
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 69573.8
```
*Model* 102 is a *2-level induced model* on 7x7 *model* 101 which is a 13x13 region. It has the highest *likelihood* so far.
```
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

NISTC entropy model104
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 70699.8
```
*Model* 104 is also *2-level model* this time on *model* 103. *Model* 103 has a smaller `wmax` than 101 but this makes little difference.
```
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

NISTC entropy model105
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 64619.4
```
*Model* 105 is the same as *model* 101_1 with bigger `znnmax` and smaller `wmax`.
```
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

NISTC entropy model106
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 73566.9

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

NISTC entropy model106_p
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 72500.1
```
*Model* 106 is the same as 105 but with `fmax` of 1023 instead of 127. It has the highest *likelihood* of all of the *models* discussed here.
```
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

NISTC entropy model106_1
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 42135.7
```
*Model* 106_1 is *conditional* on *model* 106.
```
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

NISTC entropy model106_2
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 37900.7

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

NISTC entropy model106_2_p
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 40779.5
```
*Model* 106_2 is the same as *model* 106_1 except that it is *conditional multinomial* rather than *conditional entropy*.
```
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

NISTC entropy model106_3
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 24076
```
*Model* 106_3 uses 1/64 of the *history* instead of 1/2.
```
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

NISTC entropy model107
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 35679.4
```
*Model* 107 is the same as *model* 100 except it has a *valency* of 10 instead of 2. Both the *liklihood* and the *accuracy* are worse.
```
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

NISTC entropy model108
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 14655
```
*Model* 108 is *conditioned* directly on the *substrate*. It has good *accuracy*, but poor *likelihood*.

```
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

NISTC entropy model109
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 24729.2
```
*Model* 109 is *conditional 2-level* on *model* 103, so it is similar to *model* 104 except that it is *conditioned* rather than *induced*. It has better *accuracy*, but worse *likelihood*.
```
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

NISTC entropy model111
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 55527.5
```
*Model* 111 is similar to 109 but with more *frames* (49 instead of 25).
```
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

NISTC entropy model113
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 56196.4
```
*Model* 113 is the same as 111 except that the *underlying model* is 112 and there are 81 *frames*.
```
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

NISTC entropy model114
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 56459.6
```
*Model* 114 is the same as 113 except that it is *conditional multinomial* rather than *conditional entropy*. This makes little difference.
```
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

NISTC entropy model120
ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v: 56489.6
```
*Model* 120 is the same as 114 except with parallel threads.
```
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

NISTC test model116
model: model116
train size: 60000
model cardinality: 3258
derived  cardinality: 882
underlying cardinality: 368
test size: 10000
effective size: 10000
matches: 5029

NISTC induce model117 >model117.log

NISTC test model117
model: model117
train size: 60000
model cardinality: 6465
derived  cardinality: 896
underlying cardinality: 404
test size: 10000
effective size: 9995
matches: 4739

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
```
The comparison of the *models* for *likelihood* and *accuracy* suggest that, in general, *induced models* are more *likely* than *conditioned*. *Multi-level models* are also more *likely* because they add problem domain knowledge. *Models induced* with larger searches are also more *likely*.



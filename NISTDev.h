#ifndef NISTDEV_H
#define NISTDEV_H

#include "AlignmentUtil.h"
#include "Alignment.h"
#include "AlignmentApprox.h"
#include "AlignmentAeson.h"
#include "AlignmentRepa.h"
#include "AlignmentAesonRepa.h"

#include <iomanip>
#include <set>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <thread>
#include <chrono>
#include <ctime>
#include <string>


namespace NIST
{
    typedef std::tuple<std::unique_ptr<Alignment::System>, std::unique_ptr<Alignment::SystemRepa>, std::unique_ptr<Alignment::HistoryRepa>> SystemHistoryRepaTuple;

    // trainBucketedIO :: Int -> IO (System, HistoryRepa)
    SystemHistoryRepaTuple trainBucketedIO(unsigned char);

    // testBucketedIO :: Int -> IO (System, HistoryRepa)
    SystemHistoryRepaTuple testBucketedIO(unsigned char);

}


#endif
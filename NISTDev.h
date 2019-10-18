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
    struct Bitmap
    {
	Bitmap(int h, int w) {
	    height = h;
	    width = w;
	    image.resize(h*w*3);
	}
	int height;
	int width;
	std::vector<unsigned char> image;
    };

    void bmwrite(std::string, const Bitmap&);

    typedef std::tuple<std::unique_ptr<Alignment::System>, std::unique_ptr<Alignment::SystemRepa>, std::unique_ptr<Alignment::HistoryRepa>> SystemHistoryRepaTuple;

    // trainBucketedIO :: Int -> IO (System, HistoryRepa)
    SystemHistoryRepaTuple trainBucketedIO(int);

    // testBucketedIO :: Int -> IO (System, HistoryRepa)
    SystemHistoryRepaTuple testBucketedIO(int);

}


#endif
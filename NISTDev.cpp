#include "NISTDev.h"

using namespace Alignment;
using namespace NIST;


// trainBucketedIO :: Int -> IO (System, HistoryRepa)
SystemHistoryRepaTuple NIST::trainBucketedIO(unsigned char d)
{
    auto lluu = listsSystem_u;
    auto uuur = systemsSystemRepa;

    const int a = 28;
    const int z = 60000;
    unsigned char* images = new unsigned char[z*a*a];
    unsigned char* labels = new unsigned char[z];
    try
    {
	std::ifstream fimages("train-images.idx3-ubyte", std::ios::binary);
	std::ifstream flabels("train-labels.idx1-ubyte", std::ios::binary);
	if (!fimages.is_open() || !flabels.is_open())
	{
	    std::cout << "trainBucketedIO : cannot open files" << std::endl;
	    delete[] images;
	    delete[] labels;
	    return SystemHistoryRepaTuple();
	}
	fimages.read((char*)images, 16);
	fimages.read((char*)images, z*a*a);
	fimages.close();
	flabels.read((char*)labels, 8);
	flabels.read((char*)labels, z);
	flabels.close();
    }
    catch (const std::exception& e)
    {
	std::cout << "trainBucketedIO : " << e.what() << std::endl;
	delete[] images;
	delete[] labels;
	return SystemHistoryRepaTuple();
    }
    ValSet digits;
    for (int i = 0; i < 10; i++)
	digits.insert(Value(i));
    ValSet buckets;
    for (int i = 0; i < d; i++)
	buckets.insert(Value(i));
    std::vector<VarValSetPair> ll;
    ll.push_back(VarValSetPair(Variable("digit"), digits));
    for (int i = 0; i < a; i++)
	for (int j = 0; j < a; j++)
	    ll.push_back(VarValSetPair(Variable(Variable(i+1), Variable(j+1)), buckets));
    auto uu = lluu(ll);
    auto ur = uuur(*uu);
    auto hr = std::make_unique<HistoryRepa>();
    hr->dimension = a*a+1;
    auto n = hr->dimension;
    hr->vectorVar = new std::size_t[n];
    auto vv = hr->vectorVar;
    hr->shape = new unsigned char[n];
    auto sh = hr->shape;
    hr->size = z;
    hr->arr = new unsigned char[z*n];
    auto rr = hr->arr;
    for (std::size_t i = 0; i < n; i++)
	vv[i] = i;
    sh[0] = 10;
    for (std::size_t i = 1; i < n; i++)
	sh[i] = d;
    std::size_t k = 0;
    for (std::size_t j = 0; j < z; j++)
    {
	std::size_t jn = j*n;
	rr[jn] = labels[j];
	for (std::size_t i = 1; i < n; i++)
	{
	    if (d > 128)
		rr[jn + i] = images[k];
	    else
		rr[jn + i] = images[k] * (int)d / 256;
	    k++;
	}
    }
    delete[] images;
    delete[] labels;
    return SystemHistoryRepaTuple(std::move(uu), std::move(ur), std::move(hr));
}




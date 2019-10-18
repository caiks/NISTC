#include "NISTDev.h"

using namespace Alignment;
using namespace NIST;
using namespace std;

int main(int argc, char **argv)
{
    if (false)
    {
	const int a = 28;
	const int z = 60000;
	unsigned char* images = new unsigned char[z*a*a];
	unsigned char* labels = new unsigned char[z];
	try
	{
	    ifstream fimages("train-images.idx3-ubyte", ios::binary);
	    fimages.read((char*)images, 16);
	    fimages.read((char*)images, z*a*a);
	    fimages.close();
	    ifstream flabels("train-labels.idx1-ubyte", ios::binary);
	    flabels.read((char*)labels, 8);
	    flabels.read((char*)labels, z);
	    flabels.close();
	}
	catch (const std::exception& e)
	{
	    cout << "trainBucketedIO : " << e.what() << endl << endl;
	}
	map<int, int> mm;
	for (int i = 0; i < z; i++)
	    mm[labels[i]] += 1;
	cout << mm << endl;
	map<int, int> nn;
	for (int i = 0; i < z*a*a; i++)
	    nn[images[i]] += 1;
	cout << nn << endl;
	delete[] images;
	delete[] labels;
    }

    if (false)
    {
	auto lluu = listsSystem_u;
	auto uuur = systemsSystemRepa;

	int d = 2;

	const int a = 28;
	const int z = 60000;
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
		ll.push_back(VarValSetPair(Variable(Variable(i + 1), Variable(j + 1)), buckets));
	auto uu = lluu(ll);
	auto ur = uuur(*uu);
	cout << "uu" << endl
	    << *uu << endl << endl;
	cout << "ur" << endl
	    << *ur << endl << endl;
    }

    if (true)
    {
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};

	auto tt = trainBucketedIO(2);
	auto uu = std::move(std::get<0>(tt));
	auto ur = std::move(std::get<1>(tt));
	auto hr = std::move(std::get<2>(tt));
	cout << "uu" << endl
	    << *uu << endl << endl;
	cout << "ur" << endl
	    << *ur << endl << endl;
	cout << "hrsel(hr,SizeList{0})" << endl
	    << *hrsel(*hr, SizeList{ 0 }) << endl << endl;
    }


    return 0;
}

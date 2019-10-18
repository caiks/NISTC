#include "NISTDev.h"

using namespace Alignment;
using namespace NIST;

// https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries

const int bytesPerPixel = 3; /// red, green, blue
const int fileHeaderSize = 14;
const int infoHeaderSize = 40;

unsigned char* createBitmapFileHeader(int height, int width, int paddingSize) {
    int fileSize = fileHeaderSize + infoHeaderSize + (bytesPerPixel*width + paddingSize) * height;

    static unsigned char fileHeader[] = {
	0,0, /// signature
	0,0,0,0, /// image file size in bytes
	0,0,0,0, /// reserved
	0,0,0,0, /// start of pixel array
    };

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader(int height, int width) {
    static unsigned char infoHeader[] = {
	0,0,0,0, /// header size
	0,0,0,0, /// image width
	0,0,0,0, /// image height
	0,0, /// number of color planes
	0,0, /// bits per pixel
	0,0,0,0, /// compression
	0,0,0,0, /// image size
	0,0,0,0, /// horizontal resolution
	0,0,0,0, /// vertical resolution
	0,0,0,0, /// colors in color table
	0,0,0,0, /// important color count
    };

    infoHeader[0] = (unsigned char)(infoHeaderSize);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(bytesPerPixel * 8);

    return infoHeader;
}

void generateBitmapImage(const unsigned char *image, int height, int width, const char* imageFileName) {

    unsigned char padding[3] = { 0, 0, 0 };
    int paddingSize = (4 - (width*bytesPerPixel) % 4) % 4;

    unsigned char* fileHeader = createBitmapFileHeader(height, width, paddingSize);
    unsigned char* infoHeader = createBitmapInfoHeader(height, width);

    FILE* imageFile = fopen(imageFileName, "wb");

    fwrite(fileHeader, 1, fileHeaderSize, imageFile);
    fwrite(infoHeader, 1, infoHeaderSize, imageFile);

    int i;
    for (i = 0; i<height; i++) {
	fwrite(image + (i*width*bytesPerPixel), bytesPerPixel, width, imageFile);
	fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

void NIST::bmwrite(std::string imageFileName, const Bitmap& bm)
{
    try
    {
	generateBitmapImage(bm.image.data(), bm.height, bm.width, imageFileName.data());
    }
    catch (const std::exception& e)
    {
	std::cout << "bmwrite : " << e.what() << std::endl;
	return;
    }
}


// trainBucketedIO :: Int -> IO (System, HistoryRepa)
SystemHistoryRepaTuple NIST::trainBucketedIO(int d)
{
    auto lluu = listsSystem_u;
    auto uuur = systemsSystemRepa;

    if (d>128)
    {
	std::cout << "valency " << d << " is too large" << std::endl;
	return SystemHistoryRepaTuple();
    }
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
	    rr[jn + i] = images[k] * d / 256;
	    k++;
	}
    }
    delete[] images;
    delete[] labels;
    return SystemHistoryRepaTuple(std::move(uu), std::move(ur), std::move(hr));
}




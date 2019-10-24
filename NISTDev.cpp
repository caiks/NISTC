#include "NISTDev.h"

using namespace Alignment;
using namespace NIST;
using namespace std;


Bitmap NIST::bminsert(const Bitmap& bm2, int ox, int oy, const Bitmap& bm1)
{
    Bitmap bm3(bm2);
    for (int i = 0; i<bm1.height; i++)
	for (int j = 0; j<bm1.width; j++)
	    for (int l = 0; l<3; l++)
		bm3.image[(i+ox)*bm3.width*3 + (j+oy)*3 + l] = bm1.image[i*bm1.width*3 + j*3 + l];
    return bm3;
}

Bitmap NIST::bmborder(int b, const Bitmap& bm)
{
    return bminsert(Bitmap(b*2+bm.height, b*2+bm.width, 255),b,b,bm);
}

Bitmap NIST::bmhstack(const std::vector<Bitmap>& ll)
{
    if (!ll.size())
    {
	cout << "bmhstack : empty list" << endl;
	return Bitmap();
    }
    int h = ll[0].height;
    int w = 0;
    for (int k = 0; k<ll.size(); k++)
	w += ll[k].width;
    Bitmap bm1(h,w);
    int q = 0;
    for (int k = 0; k < ll.size(); k++)
    {
	auto& bm = ll[k];
	for (int i = 0; i<bm.height; i++)
	    for (int j = 0; j<bm.width; j++)
		for (int l = 0; l<3; l++)
		    bm1.image[(i)*bm1.width*3 + (j + q) * 3 + l] = bm.image[i*bm.width*3 + j*3 + l];
	q += ll[k].width;
    }
    return bm1;
}

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

void NIST::bmwrite(string imageFileName, const Bitmap& bm)
{
    try
    {
	generateBitmapImage(bm.image.data(), bm.height, bm.width, imageFileName.data());
    }
    catch (const exception& e)
    {
	cout << "bmwrite : " << e.what() << endl;
	return;
    }
}

Bitmap NIST::hrbm(int b, int c, int d, const HistoryRepa& hr)
{
    Bitmap bm(b*c, b*c);
    auto n = b*b;
    if (n != hr.dimension)
    {
	cout << "hrbm : inconsistent dimension" << endl;
	return bm;
    }
    auto z = hr.size;
    auto rr = hr.arr;
    vector<size_t> av(n);
    for (std::size_t j = 0; j < z; j++)
	for (std::size_t i = 0; i < n; i++)
	    av[i] += rr[j*n + i];
    for (std::size_t i = 0; i < n; i++)
	av[i] = av[i] * 255 / (d-1) / z;
    for (int i = 0; i < bm.height; i++) {
	for (int j = 0; j< bm.width; j++) {
	    unsigned char x = (unsigned char)av[(b-1-(i/c))*b + (j/c)];
	    int k = i*bm.width*3 + j*3;
	    for (int l = 0; l<3; l++)
		bm.image[k+l] = x;
	}
    }
    return bm;
}


// trainBucketedIO :: Int -> IO (System, HistoryRepa)
SystemHistoryRepaTuple NIST::trainBucketedIO(int d)
{
    auto lluu = listsSystem_u;
    auto uuur = systemsSystemRepa;

    if (d>128)
    {
	cout << "valency " << d << " is too large" << endl;
	return SystemHistoryRepaTuple();
    }
    const int a = 28;
    const int z = 60000;
    unsigned char* images = new unsigned char[z*a*a];
    unsigned char* labels = new unsigned char[z];
    try
    {
	ifstream fimages("train-images.idx3-ubyte", ios::binary);
	ifstream flabels("train-labels.idx1-ubyte", ios::binary);
	if (!fimages.is_open() || !flabels.is_open())
	{
	    cout << "trainBucketedIO : cannot open files" << endl;
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
    catch (const exception& e)
    {
	cout << "trainBucketedIO : " << e.what() << endl;
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
    vector<VarValSetPair> ll;
    ll.push_back(VarValSetPair(Variable("digit"), digits));
    for (int i = 0; i < a; i++)
	for (int j = 0; j < a; j++)
	    ll.push_back(VarValSetPair(Variable(Variable(i+1), Variable(j+1)), buckets));
    auto uu = lluu(ll);
    auto ur = uuur(*uu);
    auto hr = make_unique<HistoryRepa>();
    hr->dimension = a*a+1;
    auto n = hr->dimension;
    hr->vectorVar = new size_t[n];
    auto vv = hr->vectorVar;
    hr->shape = new unsigned char[n];
    auto sh = hr->shape;
    hr->size = z;
    hr->evient = true;
    hr->arr = new unsigned char[z*n];
    auto rr = hr->arr;
    for (size_t i = 0; i < n; i++)
	vv[i] = i;
    sh[0] = 10;
    for (size_t i = 1; i < n; i++)
	sh[i] = d;
    size_t k = 0;
    for (size_t j = 0; j < z; j++)
    {
	size_t jn = j*n;
	rr[jn] = labels[j];
	for (size_t i = 1; i < n; i++)
	{
	    rr[jn + i] = images[k] * d / 256;
	    k++;
	}
    }
    delete[] images;
    delete[] labels;
    return SystemHistoryRepaTuple(move(uu), move(ur), move(hr));
}




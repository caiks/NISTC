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
	    ifstream fimages("train-images-idx3-ubyte", ios::binary);
	    fimages.read((char*)images, 16);
	    fimages.read((char*)images, z*a*a);
	    fimages.close();
	    ifstream flabels("train-labels-idx1-ubyte", ios::binary);
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

    if (false)
    {
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};

	auto xx = trainBucketedIO(2);
	auto uu = std::move(std::get<0>(xx));
	auto ur = std::move(std::get<1>(xx));
	auto hr = std::move(std::get<2>(xx));
	cout << "uu" << endl
	    << *uu << endl << endl;
	cout << "ur" << endl
	    << *ur << endl << endl;
	cout << "hrsel(hr,SizeList{0})" << endl
	    << *hrsel(*hr, SizeList{ 0 }) << endl << endl;
    }

    if (false)
    {
	Bitmap bm(341,753);
	for (int i = 0; i <bm.height; i++) {
	    for (int j = 0; j< bm.width; j++) {
		bm.image[i*bm.width * 3 + j * 3 + 2] = (unsigned char)((double)i / bm.height * 255); ///red
		bm.image[i*bm.width * 3 + j * 3 + 1] = (unsigned char)((double)j / bm.width * 255); ///green
		bm.image[i*bm.width * 3 + j * 3 + 0] = (unsigned char)(((double)i + j) / (bm.height + bm.width) * 255); ///blue
	    }
	}
	bmwrite("NIST.bmp", bm);
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
	};

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hrtr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hrtr->dimension" << endl
	    << hrtr->dimension << endl << endl;
	cout << "hrtr->size" << endl
	    << hrtr->size << endl << endl;

	SizeList ll;
	for (size_t i = 0; i < hrtr->size; i += 8)
	    ll.push_back(i);
	auto hr = hrsel(*hrtr, ll);
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	set<size_t> ww;
	for (auto& w : vvk)
	    ww.insert(vol(*uu, VarUSet{ w }));
	cout << "ww" << endl
	    << ww << endl << endl;

	cout << "vol(uu,vvl)" << endl
	    << vol(*uu, vvl) << endl << endl;

	cout << "rpln(aall(araa(uu,hrred(hr,vvl))))" << endl;
	rpln(cout, sorted(*aall(*araa(*uu, *ur, *hrred(*hr, *ur, vvl))))); cout << endl;

	cout << "hrsel(hr,SizeList{0})" << endl
	    << *hrsel(*hr, SizeList{ 0 }) << endl << endl;

	auto hr1 = hrhrred(*hr, *ur, vvk);
	auto bm = hrbm(28, 1, 2, *hrsel(*hr1, SizeList{ 0 }));
	cout << "bm.height" << endl
	    << bm.height << endl << endl;
	cout << "bm.width" << endl
	    << bm.width << endl << endl;
	cout << "bm.image.size()" << endl
	    << bm.image.size() << endl << endl;
	cout << "bm.image" << endl;
	for (std::size_t i = 0; i < bm.image.size(); i += 3)
	{
	    if (i) cout << ",";
	    cout << "[" << (int)bm.image[i] << "," << (int)bm.image[i+1] << "," << (int)bm.image[i+2] << "]";
	}
	bmwrite("NIST.bmp", bm);
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
	};

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hrtr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hrtr->dimension" << endl
	    << hrtr->dimension << endl << endl;
	cout << "hrtr->size" << endl
	    << hrtr->size << endl << endl;

	SizeList ll;
	for (size_t i = 0; i < hrtr->size; i += 8)
	    ll.push_back(i);
	auto hr = hrsel(*hrtr, ll);
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	set<size_t> ww;
	for (auto& w : vvk)
	    ww.insert(vol(*uu, VarUSet{ w }));
	cout << "ww" << endl
	    << ww << endl << endl;

	cout << "vol(uu,vvl)" << endl
	    << vol(*uu, vvl) << endl << endl;

	cout << "rpln(aall(araa(uu,hrred(hr,vvl))))" << endl;
	rpln(cout, sorted(*aall(*araa(*uu, *ur, *hrred(*hr, *ur, vvl))))); cout << endl;

	auto hr1 = hrhrred(*hr, *ur, vvk);

	{
	    std::vector<Bitmap> bms;
	    for (size_t i = 0; i < 25; i++)
		bms.push_back(bmborder(1,hrbm(28, 1, 2, *hrsel(*hr1, SizeList{i}))));
	    bmwrite("NIST01.bmp", bmhstack(bms));
	}

	auto hrbmav = hrbm(28, 3, 2, *hr1);
	bmwrite("NIST02.bmp", hrbmav);

	{
	    std::vector<Bitmap> bms;
	    for (auto ss : sorted(*cart(*uu, vvl)))
		bms.push_back(bmborder(1, hrbm(28, 2, 2, *hrhrred(*hrhrsel(*hr, *aahr(*uu, *ur, *single(ss, 1))), *ur, vvk))));
	    bmwrite("NIST03.bmp", bmhstack(bms));
	}

	auto hrr = historyRepasShuffle_u(*hr, 1);

	bmwrite("NIST04.bmp", hrbm(28, 3, 2, *hrhrred(*hrr, *ur, vvk)));

	{
	    auto hrr1 = hrhrred(*hrr, *ur, vvk);
	    std::vector<Bitmap> bms;
	    for (size_t i = 0; i < 25; i++)
		bms.push_back(bmborder(1, hrbm(28, 1, 2, *hrsel(*hrr1, SizeList{ i }))));
	    bmwrite("NIST05.bmp", bmhstack(bms));
	}

    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
	};
	auto hrcross = [](std::size_t xmax, std::size_t omax, const HistoryRepa& hr, const HistoryRepa& hrs, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    auto pr = historyRepasRed(hr);
	    auto prs = historyRepasRed(hrs);
	    auto xx = parametersSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, kk1, hr, *pr, hrs, *prs);
	    std::vector<std::pair<double, VarList>> ll;
	    auto tt = sorted(*std::get<0>(xx));
	    for (auto& mm : tt)
	    {
		VarList ll1;
		for (auto& i : mm.second)
		    ll1.push_back((ur.listVarSizePair[i]).first);
		ll.push_back(std::pair<double, VarList>(mm.first,ll1));
	    }
	    return ll;
	};

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hrtr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hrtr->dimension" << endl
	    << hrtr->dimension << endl << endl;
	cout << "hrtr->size" << endl
	    << hrtr->size << endl << endl;

	SizeList ll;
	for (size_t i = 0; i < hrtr->size; i += 8)
	    ll.push_back(i);
	auto hr = hrsel(*hrtr, ll);
	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	{
	    auto start = chrono::system_clock::now();
	    auto hrr = historyRepasShuffle_u(*hr, 1);
	    auto end = chrono::system_clock::now();
	    cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto ll = hrcross(100, 10, *hr, *hrr, *ur, vvk);
	    end = chrono::system_clock::now();
	    cout << "hrcross " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    cout << "ll" << endl;
	    for (auto& mm : ll)
		cout << mm.first << "," << mm.second << endl;
	    /*
	    historyRepasShuffle_u 0.218406s
	    hrcross 13.8532s
	    ll
	    2123.91,[<24,12>,<24,13>]
	    2123.98,[<17,20>,<18,20>]
	    2130.76,[<15,9>,<16,9>]
	    2132.73,[<12,10>,<13,10>]
	    2134.58,[<23,12>,<23,13>]
	    2136.53,[<23,11>,<23,12>]
	    2172.46,[<12,9>,<13,9>]
	    2187.93,[<14,8>,<15,8>]
	    2234.01,[<14,9>,<15,9>]
	    2292.43,[<13,9>,<14,9>]
	    */
	}

	{
	    auto start = chrono::system_clock::now();
	    hr->transpose();
	    auto end = chrono::system_clock::now();
	    cout << "transpose " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto hrr = historyRepasShuffle_u(*hr, 1);
	    end = chrono::system_clock::now();
	    cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto ll = hrcross(100, 10, *hr, *hrr, *ur, vvk);
	    end = chrono::system_clock::now();
	    cout << "hrcross " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    cout << "ll" << endl;
	    for (auto& mm : ll)
		cout << mm.first << "," << mm.second << endl;
	    /*
	    transpose 0.0312008s
	    historyRepasShuffle_u 0.37441s
	    hrcross 98.8129s
	    ll
	    2123.2,[<24,12>,<24,13>]
	    2123.24,[<17,20>,<18,20>]
	    2130.83,[<15,9>,<16,9>]
	    2132.78,[<12,10>,<13,10>]
	    2134.47,[<23,12>,<23,13>]
	    2138.44,[<23,11>,<23,12>]
	    2172.53,[<12,9>,<13,9>]
	    2187.68,[<14,8>,<15,8>]
	    2234.05,[<14,9>,<15,9>]
	    2291.64,[<13,9>,<14,9>]
	    */
	}
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
	{
	    auto& vvi = ur.mapVarSize();
	    std::size_t m = kk.size();
	    auto kk0 = sorted(kk);
	    SizeList kk1;
	    for (auto& v : kk0)
		kk1.push_back(vvi[v]);
	    return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
	};

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hrtr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hrtr->dimension" << endl
	    << hrtr->dimension << endl << endl;
	cout << "hrtr->size" << endl
	    << hrtr->size << endl << endl;

	SizeList ll;
	for (size_t i = 0; i < hrtr->size; i += 8)
	    ll.push_back(i);
	auto hr = hrsel(*hrtr, ll);
	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	size_t xmax = 4096;
	size_t omax = 10;
	{
	    auto start = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    auto end = chrono::system_clock::now();
	    cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto pr = historyRepasRed(*hr);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto prs = historyRepasRed(*hrs);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto xx = parametersSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, vvk1, *hr, *pr, *hrs, *prs);
	    end = chrono::system_clock::now();
	    cout << "hrcross " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    auto xc = std::move(std::get<0>(xx));
	    auto sc = std::get<1>(xx);
	    cout << "steps: " << sc << endl;
	    auto tt = sorted(*xc);
	    for (auto& mm : tt)
	    {
		cout << mm.first << ", ";
		VarList ll1;
		for (auto& i : mm.second)
		    ll1.push_back((ur->listVarSizePair[i]).first);
		cout << ll1 << endl;
	    }

	    SizeListList vdd;
	    for (auto& mm : *xc)
		vdd.push_back(mm.second);

	    start = chrono::system_clock::now();
	    xx = parametersSetVarsSetSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, vvk1, vdd, *hr, *pr, *hrs, *prs);
	    end = chrono::system_clock::now();
	    cout << "hrappend " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    xc = std::move(std::get<0>(xx));
	    sc = std::get<1>(xx);
	    cout << "steps: " << sc << endl;
	    tt = sorted(*xc);
	    for (auto& mm : tt)
	    {
		cout << mm.first << ", ";
		VarList ll1;
		for (auto& i : mm.second)
		    ll1.push_back((ur->listVarSizePair[i]).first);
		cout << ll1 << endl;
	    }
	    /*
	    historyRepasShuffle_u 0.234003s
	    historyRepasRed(hr) 0.0156002s
	    historyRepasRed(hrs) 0.0156002s
	    hrcross 13.9778s
	    steps: 306936
	    2123.91, [<24,12>,<24,13>]
	    2123.98, [<17,20>,<18,20>]
	    2130.76, [<15,9>,<16,9>]
	    2132.73, [<12,10>,<13,10>]
	    2134.58, [<23,12>,<23,13>]
	    2136.53, [<23,11>,<23,12>]
	    2172.46, [<12,9>,<13,9>]
	    2187.93, [<14,8>,<15,8>]
	    2234.01, [<14,9>,<15,9>]
	    2292.43, [<13,9>,<14,9>]
	    hrappend 0.81121s
	    steps: 7820
	    4175.65, [<23,9>,<23,11>,<23,12>]
	    4181.65, [<11,8>,<12,9>,<13,9>]
	    4201.86, [<19,19>,<17,20>,<18,20>]
	    4260.35, [<16,7>,<14,8>,<15,8>]
	    4268.39, [<14,9>,<12,10>,<13,10>]
	    4275.66, [<13,7>,<14,8>,<15,8>]
	    4297.26, [<23,10>,<23,12>,<23,13>]
	    4383.27, [<14,8>,<15,9>,<16,9>]
	    4476.49, [<12,8>,<13,9>,<14,9>]
	    4542.22, [<13,8>,<14,9>,<15,9>]
	    */
	}

	{
	    auto start = chrono::system_clock::now();
	    hr->transpose();
	    auto end = chrono::system_clock::now();
	    cout << "transpose " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    end = chrono::system_clock::now();
	    cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto pr = historyRepasRed(*hr);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto prs = historyRepasRed(*hrs);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto xx = parametersSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, vvk1, *hr, *pr, *hrs, *prs);
	    end = chrono::system_clock::now();
	    cout << "hrcross " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    auto xc = std::move(std::get<0>(xx));
	    auto sc = std::get<1>(xx);
	    cout << "steps: " << sc << endl;
	    auto tt = sorted(*xc);
	    for (auto& mm : tt)
	    {
		cout << mm.first << ", ";
		VarList ll1;
		for (auto& i : mm.second)
		    ll1.push_back((ur->listVarSizePair[i]).first);
		cout << ll1 << endl;
	    }

	    SizeListList vdd;
	    for (auto& mm : *xc)
		vdd.push_back(mm.second);

	    start = chrono::system_clock::now();
	    xx = parametersSetVarsSetSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, vvk1, vdd, *hr, *pr, *hrs, *prs);
	    end = chrono::system_clock::now();
	    cout << "hrappend " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    xc = std::move(std::get<0>(xx));
	    sc = std::get<1>(xx);
	    cout << "steps: " << sc << endl;
	    tt = sorted(*xc);
	    for (auto& mm : tt)
	    {
		cout << mm.first << ", ";
		VarList ll1;
		for (auto& i : mm.second)
		    ll1.push_back((ur->listVarSizePair[i]).first);
		cout << ll1 << endl;
	    }
	    /*
	    transpose 0.0312004s
	    historyRepasShuffle_u 0.390005s
	    historyRepasRed(hr) 0s
	    historyRepasRed(hrs) 0s
	    hrcross 104.007s
	    steps: 306936
	    2123.2, [<24,12>,<24,13>]
	    2123.24, [<17,20>,<18,20>]
	    2130.83, [<15,9>,<16,9>]
	    2132.78, [<12,10>,<13,10>]
	    2134.47, [<23,12>,<23,13>]
	    2138.44, [<23,11>,<23,12>]
	    2172.53, [<12,9>,<13,9>]
	    2187.68, [<14,8>,<15,8>]
	    2234.05, [<14,9>,<15,9>]
	    2291.64, [<13,9>,<14,9>]
	    hrappend 6.06848s
	    steps: 7820
	    4178.08, [<23,9>,<23,11>,<23,12>]
	    4181.29, [<11,8>,<12,9>,<13,9>]
	    4202.66, [<19,19>,<17,20>,<18,20>]
	    4260.41, [<16,7>,<14,8>,<15,8>]
	    4269.11, [<14,9>,<12,10>,<13,10>]
	    4275.52, [<13,7>,<14,8>,<15,8>]
	    4298.27, [<23,10>,<23,12>,<23,13>]
	    4383.27, [<14,8>,<15,9>,<16,9>]
	    4475.37, [<12,8>,<13,9>,<14,9>]
	    4543.04, [<13,8>,<14,9>,<15,9>]
	    */
	}
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto ind = histogramsIndependent;
	auto algn = histogramsAlignment;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto arpr = histogramRepasRed;
	auto prar = histogramRepaRedsIndependent;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
	{
	    return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
	{
	    return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
	};
	auto hrpr = historyRepasRed;
	auto aralgn = [](const HistogramRepa& ar)
	{
	    auto ax = histogramRepaRedsIndependent(ar.size(),*histogramRepasRed(ar.size(),ar));
	    return ar.facLn() - ax->facLn();
	};

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hrtr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hrtr->dimension" << endl
	    << hrtr->dimension << endl << endl;
	cout << "hrtr->size" << endl
	    << hrtr->size << endl << endl;

	SizeList ll;
	for (size_t i = 0; i < hrtr->size; i += 8)
	    ll.push_back(i);
	auto hr = hrsel(*hrtr, ll);
	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	size_t xmax = 4096;
	size_t omax = 10;
	size_t bmax = 10;
	size_t mmax = 1;
	{
	    auto start = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    auto end = chrono::system_clock::now();
	    cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto pr = historyRepasRed(*hr);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto prs = historyRepasRed(*hrs);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto t = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
	    end = chrono::system_clock::now();
	    cout << "buildtup " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    auto xx = std::move(std::get<0>(t));
	    auto s = std::get<1>(t);
	    cout << "steps: " << s << endl;
	    for (auto& kk : *xx)
	    {
		cout << aralgn(*hrred(*hr, kk)) - aralgn(*hrred(*hrs, kk)) << ",";
		VarSet qq;
		for (std::size_t i = 0; i < kk.size(); i++)
		    qq.insert((ur->listVarSizePair[kk[i]]).first);
		cout << qq << endl;
	    }
	}

	{
	    auto start = chrono::system_clock::now();
	    hr->transpose();
	    auto end = chrono::system_clock::now();
	    cout << "transpose " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    end = chrono::system_clock::now();
	    cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto pr = historyRepasRed(*hr);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto prs = historyRepasRed(*hrs);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto t = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
	    end = chrono::system_clock::now();
	    cout << "buildtup " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    auto xx = std::move(std::get<0>(t));
	    auto s = std::get<1>(t);
	    cout << "steps: " << s << endl;
	    for (auto& kk : *xx)
	    {
		cout << aralgn(*hrred(*hr, kk)) - aralgn(*hrred(*hrs, kk)) << ",";
                VarSet qq;
		for (std::size_t i = 0; i < kk.size(); i++)
		    qq.insert((ur->listVarSizePair[kk[i]]).first);
		cout << qq << endl;
	    }
	}
	/*
	hrtr->dimension
	785

	hrtr->size
	60000

	hr->dimension
	785

	hr->size
	7500

	historyRepasShuffle_u 0.234008s
	historyRepasRed(hr) 0.0156005s
	historyRepasRed(hrs) 0.031201s
	buildtup 32.169s
	steps: 256850
	23395.8,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<14,10>}
	23285.8,{<10,9>,<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>}
	23217.8,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>,<14,11>}
	23197.7,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>,<15,9>}
	23176.9,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>}
	23159,{<10,10>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>}
	23126.1,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<15,9>}
	23106.6,{<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>}
	23102.4,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<14,10>,<15,9>,<15,10>}
	23087,{<10,9>,<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<13,9>,<13,10>,<14,9>,<14,10>}
	transpose 0.0312006s
	historyRepasShuffle_u 0.49921s
	historyRepasRed(hr) 0.0156003s
	historyRepasRed(hrs) 0.0156003s
	buildtup 186.269s
	steps: 256850
	23400.4,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<14,10>}
	23255,{<10,9>,<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>}
	23190.9,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>,<14,11>}
	23180.6,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>}
	23143.9,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<15,9>}
	23140.3,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>,<15,9>}
	23105.7,{<10,10>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>}
	23082.1,{<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>}
	23052.5,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<14,10>,<15,9>,<15,10>}
	23050.2,{<10,9>,<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<13,9>,<13,10>,<14,9>,<14,10>}
	*/
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto ind = histogramsIndependent;
	auto algn = histogramsAlignment;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto arpr = histogramRepasRed;
	auto prar = histogramRepaRedsIndependent;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
	{
	    return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
	{
	    return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
	};
	auto hrpr = historyRepasRed;
	auto aralgn = [](const HistogramRepa& ar)
	{
	    auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
	    return ar.facLn() - ax->facLn();
	};

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	// model 3
	size_t xmax = 512;
	size_t omax = 40;
	size_t bmax = 40*4;
	size_t mmax = 4;
	size_t umax = 256;
	size_t pmax = 1;
	{
	    auto start = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    auto end = chrono::system_clock::now();
	    cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto pr = historyRepasRed(*hr);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto prs = historyRepasRed(*hrs);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto t = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
	    end = chrono::system_clock::now();
	    cout << "buildtup " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    auto xx = std::move(std::get<0>(t));
	    auto s = std::get<1>(t);
	    cout << "steps: " << s << endl;
	    cout << "tuples: " << xx->size() << endl;

	    s = 0;
	    std::size_t p = 0;
	    start = chrono::system_clock::now();
	    for (auto& kk : *xx)
	    {
		auto t2 = parametersSystemsPartitionerMaxRollByMRepa_ui(mmax, umax, pmax, kk, *hr, *hrs);
		p += std::get<0>(t2)->size();
		s += std::get<1>(t2);
	    }
	    end = chrono::system_clock::now();
	    cout << "parter " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    cout << "steps: " << s << endl;
	    cout << "partitions: " << p << endl;

	    /*
	    historyRepasShuffle_u 1.74723s
	    historyRepasRed(hr) 0.156003s
	    historyRepasRed(hrs) 0.156003s
	    buildtup 392.581s
	    steps: 416030
	    tuples: 40
	    parter 50.2028s
	    steps: 442000
	    partitions: 120
	    */
	}
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto ind = histogramsIndependent;
	auto algn = histogramsAlignment;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto arpr = histogramRepasRed;
	auto prar = histogramRepaRedsIndependent;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
	{
	    return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
	{
	    return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
	};
	auto hrpr = historyRepasRed;
	auto aralgn = [](const HistogramRepa& ar)
	{
	    auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
	    return ar.facLn() - ax->facLn();
	};
	auto tupler = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui;
	auto rrvqqy = parametersHistogramRepaVecsSetTuplePartitionTopByM_u;
	auto parter = parametersSystemsPartitionerMaxRollByMRepa_ui;
	auto roller = parametersRollerMaximumRollExcludedSelfRepa_i;

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	// model 3
	size_t xmax = 512;
	size_t omax = 40;
	size_t bmax = 40 * 4;
	size_t mmax = 4;
	size_t umax = 256;
	size_t pmax = 1;
	{
	    auto start = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    auto end = chrono::system_clock::now();
	    cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto pr = historyRepasRed(*hr);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto prs = historyRepasRed(*hrs);
	    end = chrono::system_clock::now();
	    cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

	    start = chrono::system_clock::now();
	    auto t = tupler(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
	    end = chrono::system_clock::now();
	    cout << "tupler " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
	    auto xx = std::move(std::get<0>(t));
	    auto s = std::get<1>(t);
	    cout << "steps: " << s << endl;
	    cout << "tuples: " << xx->size() << endl;

	    map<string, double> perf;
	    map<string, size_t> steps;
	    auto mark = chrono::system_clock::now();
	    for (auto& kk : *xx)
	    {
		auto z = (double)hr->size;

		mark = chrono::system_clock::now();
		auto ar = hrred(*hr, kk);
		auto ars = hrred(*hrs, kk);
		perf["hrred"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
		steps["hrred"] += 2;

		mark = chrono::system_clock::now();
		double y1 = ar->facLn() - ars->facLn();
		perf["facLn"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
		steps["facLn"] += 2;
		mark = chrono::system_clock::now();

		auto t = rrvqqy(mmax, umax, pmax, *ar, *ars, z, y1);
		perf["parter"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
		steps["parter"] += std::get<1>(t);

		auto xx = std::move(std::get<0>(t));
		for (auto& nn : *xx)
		{
		    mark = chrono::system_clock::now();
		    auto t2 = roller(nn, *ar, *ars, z);
		    perf["roller"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
		    steps["roller"] += std::get<1>(t2);
		}
	    }
	    cout << "perf: " << perf << endl;
	    cout << "steps: " << steps << endl;

	    /*
	    historyRepasShuffle_u 1.77843s
	    historyRepasRed(hr) 0.156003s
	    historyRepasRed(hrs) 0.156003s
	    tupler 395.88s
	    steps: 416030
	    tuples: 40
	    perf: {(facLn,0),(hrred,0.0936018),(parter,51.9198),(roller,2.01244)}
	    steps: {(facLn,80),(hrred,80),(parter,442000),(roller,523178)}
	    */
	}
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto ind = histogramsIndependent;
	auto algn = histogramsAlignment;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto arpr = histogramRepasRed;
	auto prar = histogramRepaRedsIndependent;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
	{
	    return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
	{
	    return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
	};
	auto hrpr = historyRepasRed;
	auto aralgn = [](const HistogramRepa& ar)
	{
	    auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
	    return ar.facLn() - ax->facLn();
	};
	auto tupler = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui;
	auto rrvqqy = parametersHistogramRepaVecsSetTuplePartitionTopByM_u;
	auto parter = parametersSystemsPartitionerMaxRollByMRepa_ui;
	auto roller = parametersRollerMaximumRollExcludedSelfRepa_i;

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	// model 35
	size_t xmax = 1024;
	size_t omax = 30;
	size_t bmax = 30 * 3;
	size_t mmax = 3;
	size_t umax = 256;
	size_t pmax = 1;
	{
	    map<string, double> perf;
	    map<string, size_t> steps;
	    auto mark = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    perf["historyRepasShuffle_u"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
	    steps["historyRepasShuffle_u"] += 1;

	    mark = chrono::system_clock::now();
	    auto pr = historyRepasRed(*hr);
	    perf["historyRepasRed"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
	    steps["historyRepasRed"] += 1;

	    mark = chrono::system_clock::now();
	    auto prs = historyRepasRed(*hrs);
	    perf["historyRepasRed"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
	    steps["historyRepasRed"] += 1;

	    mark = chrono::system_clock::now();
	    auto t = tupler(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
	    perf["tupler"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
	    steps["tupler"] += std::get<1>(t);
	    auto xx = std::move(std::get<0>(t));

	    for (auto& kk : *xx)
	    {
		auto z = (double)hr->size;

		mark = chrono::system_clock::now();
		auto ar = hrred(*hr, kk);
		auto ars = hrred(*hrs, kk);
		perf["hrred"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
		steps["hrred"] += 2;

		mark = chrono::system_clock::now();
		double y1 = ar->facLn() - ars->facLn();
		perf["facLn"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
		steps["facLn"] += 2;
		mark = chrono::system_clock::now();

		auto t = rrvqqy(mmax, umax, pmax, *ar, *ars, z, y1);
		perf["parter"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
		steps["parter"] += std::get<1>(t);

		auto xx = std::move(std::get<0>(t));
		for (auto& nn : *xx)
		{
		    mark = chrono::system_clock::now();
		    auto t2 = roller(nn, *ar, *ars, z);
		    perf["roller"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
		    steps["roller"] += std::get<1>(t2);
		}
	    }
	    cout << "historyRepasShuffle_u " << perf["historyRepasShuffle_u"] << "s" << endl;
	    cout << "steps: " << steps["historyRepasShuffle_u"] << endl;
	    cout << "historyRepasRed " << perf["historyRepasRed"] << "s" << endl;
	    cout << "steps: " << steps["historyRepasRed"] << endl;
	    cout << "tupler " << perf["tupler"] << "s" << endl;
	    cout << "steps: " << steps["tupler"] << endl;
	    cout << "hrred " << perf["hrred"] << "s" << endl;
	    cout << "steps: " << steps["hrred"] << endl;
	    cout << "facLn " << perf["facLn"] << "s" << endl;
	    cout << "steps: " << steps["facLn"] << endl;
	    cout << "parter " << perf["parter"] << "s" << endl;
	    cout << "steps: " << steps["parter"] << endl;
	    cout << "roller " << perf["roller"] << "s" << endl;
	    cout << "steps: " << steps["roller"] << endl;
	    /*
	    historyRepasShuffle_u 1.87204s
	    steps: 1
	    historyRepasRed 0.296406s
	    steps: 2
	    tupler 370.247s
	    steps: 389070
	    hrred 0.156003s
	    steps: 60
	    facLn 0s
	    steps: 60
	    parter 61.3892s
	    steps: 294930
	    roller 4.82049s
	    steps: 802096
	    */
	}
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto ind = histogramsIndependent;
	auto algn = histogramsAlignment;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto arpr = histogramRepasRed;
	auto prar = histogramRepaRedsIndependent;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
	{
	    return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
	{
	    return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
	};
	auto hrpr = historyRepasRed;
	auto aralgn = [](const HistogramRepa& ar)
	{
	    auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
	    return ar.facLn() - ax->facLn();
	};
	auto uuur = systemsSystemRepa;
	auto uruu = systemsRepasSystem;
	auto fffr = systemsFudsFudRepa_u;
	auto frff = systemsFudRepasFud_u;

	auto layerer = parametersSystemsLayererMaxRollByMExcludedSelfHighestIORepa_u;

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	// model 3
	size_t wmax = 2048;
	size_t lmax = 8;
	size_t xmax = 512;
	size_t omax = 40;
	size_t bmax = 40 * 4;
	size_t mmax = 4;
	size_t umax = 256;
	size_t pmax = 1;
	{
	    map<string, double> perf;

	    auto mark = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    perf["historyRepasShuffle_u"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();

	    mark = chrono::system_clock::now();
	    auto t = layerer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, vvk1, *hr, *hrs, 1, *ur);
	    perf["layerer"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
	    auto& fr = std::get<0>(t);
	    auto& mm = std::get<1>(t);
	    if (mm->size())
	    {
		auto& a = mm->back().first;
		auto& kk = mm->back().second;
		VarSet qq;
		for (std::size_t i = 0; i < kk.size(); i++)
		    qq.insert((ur->listVarSizePair[kk[i]]).first);
		cout << "a = " << a << endl;
		cout << "kk = " << qq << endl;
	    }
	    cout << "fudRepasSize(fr) = " << fudRepasSize(*fr) << endl;
	}
	/*
	>>> layerer
	>>> layer       fud: 1  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 416030        rate: 1066.88
	tupler 389.949s
	tuple cardinality: 40
	max tuple algn: 156208
	layer cardinality: 196
	parter  searched: 442000        rate: 8619.05
	parter 51.2818s
	roller  searched: 523178        rate: 251398
	roller 2.08108s
	der vars algn density: 141207
	dervarser       searched: 105580        rate: 742.594
	dervarser 142.177s
	application 0.976372s
	<<< layer 586.473s
	>>> layer       fud: 1  layer: 2
	substrate cardinality: 784
	fud cardinality: 196
	tupler  searched: 308712        rate: 1390.63
	tupler 221.995s
	tuple cardinality: 40
	max tuple algn: 99539.3
	layer cardinality: 100
	parter  searched: 7440  rate: 12394.3
	parter 0.600278s
	roller  searched: 744226        rate: 437419
	roller 1.7014s
	der vars algn density: 161478
	dervarser       searched: 180631        rate: 824.022
	dervarser 219.206s
	application 0.798009s
	<<< layer 444.306s
	>>> layer       fud: 1  layer: 3
	substrate cardinality: 784
	fud cardinality: 296
	tupler  searched: 436989        rate: 1450.31
	tupler 301.306s
	tuple cardinality: 40
	max tuple algn: 3244.27
	layer cardinality: 76
	parter  searched: 7440  rate: 14363.7
	parter 0.517973s
	roller  searched: 780016        rate: 561905
	roller 1.38816s
	der vars algn density: 107674
	dervarser       searched: 184660        rate: 1395.98
	dervarser 132.28s
	application 0.862928s
	<<< layer 436.361s
	<<< layerer 1467.59s
	a = 161478
	kk = {<<1,2>,12>,<<1,2>,14>,<<1,2>,15>,<<1,2>,16>,<<1,2>,18>,<<1,2>,51>,<<1,2>,56>,<<1,2>,61>,<<1,2>,63>,<<1,2>,73>,<<1,2>,77>}
	fudRepasSize(fr) = 296
	*/
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto ind = histogramsIndependent;
	auto algn = histogramsAlignment;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto arpr = histogramRepasRed;
	auto prar = histogramRepaRedsIndependent;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
	{
	    return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
	{
	    return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
	};
	auto hrpr = historyRepasRed;
	auto aralgn = [](const HistogramRepa& ar)
	{
	    auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
	    return ar.facLn() - ax->facLn();
	};
	auto uuur = systemsSystemRepa;
	auto uruu = systemsRepasSystem;
	auto fffr = systemsFudsFudRepa_u;
	auto frff = systemsFudRepasFud_u;

	auto layerer = parametersSystemsLayererMaxRollByMExcludedSelfHighestIORepa_u;

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	// model 35
	size_t wmax = 2048;
	size_t lmax = 8;
	size_t xmax = 1024;
	size_t omax = 30;
	size_t bmax = 30 * 3;
	size_t mmax = 3;
	size_t umax = 256;
	size_t pmax = 1;
	{
	    map<string, double> perf;

	    auto mark = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    perf["historyRepasShuffle_u"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();

	    mark = chrono::system_clock::now();
	    auto t = layerer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, vvk1, *hr, *hrs, 1, *ur);
	    perf["layerer"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
	    auto& fr = std::get<0>(t);
	    auto& mm = std::get<1>(t);
	    if (mm->size())
	    {
		auto& a = mm->back().first;
		auto& kk = mm->back().second;
		VarSet qq;
		for (std::size_t i = 0; i < kk.size(); i++)
		    qq.insert((ur->listVarSizePair[kk[i]]).first);
		cout << "a = " << a << endl;
		cout << "kk = " << qq << endl;
	    }
	    cout << "fudRepasSize(fr) = " << fudRepasSize(*fr) << endl;
	}
	/*
	>>> layerer
	>>> layer       fud: 1  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 389070        rate: 1047.9
	tupler 371.285s
	tuple cardinality: 30
	max tuple algn: 178925
	layer cardinality: 101
	parter  searched: 294930        rate: 4846.68
	parter 60.852s
	roller  searched: 802096        rate: 154438
	roller 5.19363s
	der vars algn density: 140988
	dervarser       searched: 34820 rate: 689.954
	dervarser 50.4671s
	application 0.848342s
	<<< layer 488.653s
	>>> layer       fud: 1  layer: 2
	substrate cardinality: 784
	fud cardinality: 101
	tupler  searched: 176058        rate: 1169.92
	tupler 150.487s
	tuple cardinality: 30
	max tuple algn: 135438
	layer cardinality: 77
	parter  searched: 3630  rate: 8638.15
	parter 0.420229s
	roller  searched: 759555        rate: 309677
	roller 2.45273s
	der vars algn density: 120890
	dervarser       searched: 56806 rate: 1064.27
	dervarser 53.3757s
	application 0.751577s
	<<< layer 207.494s
	<<< layerer 696.562s
	a = 140988
	kk = {<<1,1>,7>,<<1,1>,24>,<<1,1>,25>,<<1,1>,27>,<<1,1>,32>,<<1,1>,41>,<<1,1>,43>,<<1,1>,55>,<<1,1>,61>,<<1,1>,77>,<<1,1>,92>}
	fudRepasSize(fr) = 101
	*/
    }

    if (false)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto ind = histogramsIndependent;
	auto algn = histogramsAlignment;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto arpr = histogramRepasRed;
	auto prar = histogramRepaRedsIndependent;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
	{
	    return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
	{
	    return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
	};
	auto hrpr = historyRepasRed;
	auto aralgn = [](const HistogramRepa& ar)
	{
	    auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
	    return ar.facLn() - ax->facLn();
	};
	auto uuur = systemsSystemRepa;
	auto uruu = systemsRepasSystem;
	auto fffr = systemsFudsFudRepa_u;
	auto frff = systemsFudRepasFud_u;

	auto layerer = parametersSystemsLayererMaxRollByMExcludedSelfHighestIORepa_u;

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	// model 1
//	size_t wmax = 1024;
	size_t wmax = 32;
	size_t lmax = 8;
	size_t xmax = 256;
	size_t omax = 10;
	size_t bmax = 10 * 3;
	size_t mmax = 3;
	size_t umax = 256;
	size_t pmax = 1;
//	size_t fmax = 15;
	size_t fmax = 2;
	size_t mult = 1;
	size_t seed = 5;
	{
	    map<string, double> perf;

	    auto mark = chrono::system_clock::now();
	    auto hrs = historyRepasShuffle_u(*hr, 1);
	    perf["historyRepasShuffle_u"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();

	    mark = chrono::system_clock::now();
	    auto t = layerer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, vvk1, *hr, *hrs, 1, *ur);
	    perf["layerer"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
	    auto& fr = std::get<0>(t);
	    auto& mm = std::get<1>(t);
	    if (mm->size())
	    {
		auto& a = mm->back().first;
		auto& kk = mm->back().second;
		VarSet qq;
		for (std::size_t i = 0; i < kk.size(); i++)
		    qq.insert((ur->listVarSizePair[kk[i]]).first);
		cout << "a = " << a << endl;
		cout << "kk = " << qq << endl;
	    }
	    cout << "fudRepasSize(fr) = " << fudRepasSize(*fr) << endl;
	}
	/*
	hr->dimension
	785

	hr->size
	60000

	>>> layerer
	>>> layer	fud: 1	layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler	searched: 268440	rate: 3059.04
	tupler 87.753s
	tuple cardinality: 10
	max tuple algn: 133995
	layer cardinality: 38
	parter	searched: 10930	rate: 38053.4
	parter 0.287228s
	roller	searched: 31245	rate: 427624
	roller 0.0730666s
	der vars algn density: 56977
	dervarser	searched: 2426	rate: 3122.04
	dervarser 0.777056s
	application 0.366584s
	<<< layer 89.257s
	>>> layer	fud: 1	layer: 2
	substrate cardinality: 784
	fud cardinality: 38
	tupler	searched: 56839	rate: 2869.46
	tupler 19.8083s
	tuple cardinality: 10
	max tuple algn: 63424.4
	layer cardinality: 25
	parter	searched: 1210	rate: 76612.7
	parter 0.0157937s
	roller	searched: 16853	rate: 786624
	roller 0.0214245s
	der vars algn density: 65722.6
	dervarser	searched: 4735	rate: 3428.19
	dervarser 1.38119s
	application 0.364668s
	<<< layer 21.5913s
	>>> layer	fud: 1	layer: 3
	substrate cardinality: 784
	fud cardinality: 63
	tupler	searched: 84320	rate: 2276.67
	tupler 37.0366s
	tuple cardinality: 10
	max tuple algn: 19838.5
	layer cardinality: 21
	parter	searched: 10930	rate: 60754.2
	parter 0.179905s
	roller	searched: 33163	rate: 850393
	roller 0.0389972s
	der vars algn density: 64125.9
	dervarser	searched: 6536	rate: 2939.56
	dervarser 2.22346s
	application 0.376406s
	<<< layer 39.8554s
	<<< layerer 151.03s
	a = 65722.6
	kk = {<<1,2>,1>,<<1,2>,2>,<<1,2>,5>,<<1,2>,23>,<<1,2>,25>}
	fudRepasSize(fr) = 63
	*/
    }

    if (true)
    {
	auto uvars = systemsSetVar;
	auto vol = systemsSetVarsVolume_u;
	auto aall = histogramsList;
	auto cart = systemsSetVarsSetStateCartesian_u;
	auto single = histogramSingleton_u;
	auto ind = histogramsIndependent;
	auto algn = histogramsAlignment;
	auto aaar = systemsHistogramsHistogramRepa_u;
	auto araa = systemsHistogramRepasHistogram_u;
	auto arpr = histogramRepasRed;
	auto prar = histogramRepaRedsIndependent;
	auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
	{
	    return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
	};
	auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
	{
	    return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
	};
	auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
	{
	    return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
	};
	auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
	{
	    return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
	};
	auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
	{
	    return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
	};
	auto hrpr = historyRepasRed;
	auto aralgn = [](const HistogramRepa& ar)
	{
	    auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
	    return ar.facLn() - ax->facLn();
	};
	auto uuur = systemsSystemRepa;
	auto uruu = systemsRepasSystem;
	auto fffr = systemsFudsFudRepa_u;
	auto frff = systemsFudRepasFud_u;

	auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

	auto xx = trainBucketedIO(2);
	auto& uu = std::get<0>(xx);
	auto& ur = std::get<1>(xx);
	auto& hr = std::get<2>(xx);

	Variable digit("digit");
	auto vv = *uvars(*uu);
	auto vvl = VarUSet();
	vvl.insert(digit);
	auto vvk = VarUSet(vv);
	vvk.erase(digit);

	cout << "hr->dimension" << endl
	    << hr->dimension << endl << endl;
	cout << "hr->size" << endl
	    << hr->size << endl << endl;

	auto& vvi = ur->mapVarSize();
	auto vvk0 = sorted(vvk);
	SizeList vvk1;
	for (auto& v : vvk0)
	    vvk1.push_back(vvi[v]);

	// model 1
	size_t wmax = 1024;
	size_t lmax = 8;
	size_t xmax = 256;
	size_t omax = 10;
	size_t bmax = 10 * 3;
	size_t mmax = 3;
	size_t umax = 256;
	size_t pmax = 1;
	size_t fmax = 15;
	size_t mult = 1;
	size_t seed = 5;
	{
	    auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax,  mult, seed, vvk1, *hr, *ur);
	    std::ofstream out("NIST_model1.bin", std::ios::binary);
	    applicationRepasPersistent(*dr, out); cout << endl;
	    out.close();
//	    cout << "dr = " << *dr << endl;
	    cout << "treesPaths(dr.slices)" << endl;
	    rpln(cout, *treesPaths(*dr->slices)); cout << endl;
	}

	/*
	hr->dimension
	785

	hr->size
	60000

	>>> applicationer
	>>> shuffler
	<<< shuffler 2.94749s
	>>> layerer
	>>> layer       fud: 1  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 268440        rate: 1871.95
	tupler 143.402s
	tuple cardinality: 10
	max tuple algn: 133993
	layer cardinality: 38
	parter  searched: 10930 rate: 9941.46
	parter 1.09944s
	roller  searched: 31309 rate: 207151
	roller 0.151141s
	der vars algn density: 118260
	dervarser       searched: 3976  rate: 808.693
	dervarser 4.91658s
	application 0.572878s
	<<< layer 150.146s
	>>> layer       fud: 1  layer: 2
	substrate cardinality: 784
	fud cardinality: 38
	tupler  searched: 56839 rate: 1236.58
	tupler 45.9648s
	tuple cardinality: 10
	max tuple algn: 64193.3
	layer cardinality: 25
	parter  searched: 1210  rate: 15039.2
	parter 0.0804563s
	roller  searched: 16916 rate: 360568
	roller 0.0469148s
	der vars algn density: 139903
	dervarser       searched: 7100  rate: 941.035
	dervarser 7.54489s
	application 0.564895s
	<<< layer 54.2069s
	>>> layer       fud: 1  layer: 3
	substrate cardinality: 784
	fud cardinality: 63
	tupler  searched: 84320 rate: 1046.45
	tupler 80.5775s
	tuple cardinality: 10
	max tuple algn: 37662.1
	layer cardinality: 13
	parter  searched: 10930 rate: 11769.4
	parter 0.928681s
	roller  searched: 79872 rate: 696850
	roller 0.114619s
	der vars algn density: 139876
	dervarser       searched: 7926  rate: 903.044
	dervarser 8.77699s
	application 0.550554s
	<<< layer 90.9509s
	<<< layerer 295.717s
	>>> transer
	fud: 1
	fud slize size: 60000
	derived cardinality: 10
	derived algn density: 139903
	derived algn density per size: 2.33171
	derived impl bi-valency percent: 64.7868
	<<< transer 0.0887764s
	>>> slicer
	slize size: 34171
	slize variable: (<<1,s>,32>,2)
	<<< slicer 0.206706s
	>>> shuffler
	<<< shuffler 1.54659s
	>>> layerer
	>>> layer       fud: 2  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 261135        rate: 3329.03
	tupler 78.4417s
	tuple cardinality: 10
	max tuple algn: 79140.3
	layer cardinality: 38
	parter  searched: 10930 rate: 9632.9
	parter 1.13465s
	roller  searched: 31741 rate: 203174
	roller 0.156226s
	der vars algn density: 66845.8
	dervarser       searched: 3936  rate: 1389.1
	dervarser 2.8335s
	application 0.328774s
	<<< layer 82.8976s
	>>> layer       fud: 2  layer: 2
	substrate cardinality: 784
	fud cardinality: 38
	tupler  searched: 57046 rate: 2154.94
	tupler 26.4722s
	tuple cardinality: 10
	max tuple algn: 47285.4
	layer cardinality: 24
	parter  searched: 1210  rate: 12811.6
	parter 0.094446s
	roller  searched: 34869 rate: 460702
	roller 0.0756866s
	der vars algn density: 84420.1
	dervarser       searched: 6874  rate: 1536.1
	dervarser 4.47498s
	application 0.32413s
	<<< layer 31.4439s
	>>> layer       fud: 2  layer: 3
	substrate cardinality: 784
	fud cardinality: 62
	tupler  searched: 83747 rate: 1785.24
	tupler 46.9107s
	tuple cardinality: 10
	max tuple algn: 5058.26
	layer cardinality: 23
	parter  searched: 10930 rate: 12772.1
	parter 0.855772s
	roller  searched: 3599156       rate: 2.22981e+06
	roller 1.61411s
	der vars algn density: 82752.7
	dervarser       searched: 9771  rate: 1709.74
	dervarser 5.7149s
	application 0.3508s
	<<< layer 55.4489s
	<<< layerer 170.03s
	>>> transer
	fud: 2
	fud slize size: 34171
	derived cardinality: 10
	derived algn density: 84420.1
	derived algn density per size: 2.47052
	derived impl bi-valency percent: 65.7938
	<<< transer 0.0721219s
	>>> slicer
	slize size: 21557
	slize variable: (<<2,s>,10>,2)
	<<< slicer 0.278651s
	>>> shuffler
	<<< shuffler 0.942971s
	>>> layerer
	>>> layer       fud: 3  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 244713        rate: 5113.18
	tupler 47.8592s
	tuple cardinality: 10
	max tuple algn: 48183.1
	layer cardinality: 39
	parter  searched: 10930 rate: 9390.96
	parter 1.16389s
	roller  searched: 32136 rate: 209108
	roller 0.153681s
	der vars algn density: 39747.5
	dervarser       searched: 4082  rate: 2207.99
	dervarser 1.84874s
	application 0.226122s
	<<< layer 51.2541s
	>>> layer       fud: 3  layer: 2
	substrate cardinality: 784
	fud cardinality: 39
	tupler  searched: 54823 rate: 3288.2
	tupler 16.6726s
	tuple cardinality: 10
	max tuple algn: 42488
	layer cardinality: 25
	parter  searched: 1210  rate: 11894.8
	parter 0.101725s
	roller  searched: 35895 rate: 392811
	roller 0.0913798s
	der vars algn density: 49431
	dervarser       searched: 7178  rate: 2422.57
	dervarser 2.96297s
	application 0.224773s
	<<< layer 20.0559s
	>>> layer       fud: 3  layer: 3
	substrate cardinality: 784
	fud cardinality: 64
	tupler  searched: 80462 rate: 2903.53
	tupler 27.7118s
	tuple cardinality: 10
	max tuple algn: 28761.2
	layer cardinality: 22
	parter  searched: 10930 rate: 11961.8
	parter 0.913744s
	roller  searched: 1687204       rate: 2.07833e+06
	roller 0.811807s
	der vars algn density: 51044.4
	dervarser       searched: 9479  rate: 2779.05
	dervarser 3.41088s
	application 0.227604s
	<<< layer 33.0792s
	>>> layer       fud: 3  layer: 4
	substrate cardinality: 784
	fud cardinality: 86
	tupler  searched: 88870 rate: 2967.46
	tupler 29.9481s
	tuple cardinality: 10
	max tuple algn: 22631.1
	layer cardinality: 16
	parter  searched: 10930 rate: 11347.4
	parter 0.96322s
	roller  searched: 489090        rate: 1.76379e+06
	roller 0.277294s
	der vars algn density: 51392.4
	dervarser       searched: 11166 rate: 2834.82
	dervarser 3.93888s
	application 0.237041s
	<<< layer 35.367s
	>>> layer       fud: 3  layer: 5
	substrate cardinality: 784
	fud cardinality: 102
	tupler  searched: 96103 rate: 3009.46
	tupler 31.9337s
	tuple cardinality: 10
	max tuple algn: 17688
	layer cardinality: 11
	parter  searched: 10930 rate: 11643.9
	parter 0.938689s
	roller  searched: 489090        rate: 1.86428e+06
	roller 0.262348s
	der vars algn density: 48814.5
	dervarser       searched: 12889 rate: 2946.76
	dervarser 4.37395s
	application 0.246002s
	<<< layer 37.7571s
	<<< layerer 177.688s
	>>> transer
	fud: 3
	fud slize size: 21557
	derived cardinality: 10
	derived algn density: 51392.4
	derived algn density per size: 2.38402
	derived impl bi-valency percent: 65.1645
	<<< transer 0.0506782s
	>>> slicer
	slize size: 20957
	slize variable: (<<1,s>,1>,2)
	<<< slicer 0.375847s
	>>> shuffler
	<<< shuffler 0.91544s
	>>> layerer
	>>> layer       fud: 4  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 243310        rate: 5110.72
	tupler 47.6077s
	tuple cardinality: 10
	max tuple algn: 48169.1
	layer cardinality: 38
	parter  searched: 10930 rate: 8994.38
	parter 1.2152s
	roller  searched: 31467 rate: 188426
	roller 0.166999s
	der vars algn density: 28471.3
	dervarser       searched: 2791  rate: 3258.22
	dervarser 0.856603s
	application 0.23321s
	<<< layer 50.0822s
	>>> layer       fud: 4  layer: 2
	substrate cardinality: 784
	fud cardinality: 38
	tupler  searched: 47112 rate: 4158.08
	tupler 11.3302s
	tuple cardinality: 10
	max tuple algn: 12543.8
	layer cardinality: 21
	parter  searched: 400   rate: 11256
	parter 0.0355366s
	roller  searched: 59310 rate: 455947
	roller 0.130081s
	der vars algn density: 31764.8
	dervarser       searched: 4625  rate: 3741.59
	dervarser 1.2361s
	application 0.221915s
	<<< layer 12.9566s
	>>> layer       fud: 4  layer: 3
	substrate cardinality: 784
	fud cardinality: 59
	tupler  searched: 54260 rate: 4268.68
	tupler 12.7112s
	tuple cardinality: 10
	max tuple algn: -9886.12
	layer cardinality: 21
	parter  searched: 400   rate: 13682.6
	parter 0.0292341s
	roller  searched: 919416        rate: 1.42923e+06
	roller 0.643294s
	der vars algn density: 31340.1
	dervarser       searched: 6855  rate: 4343.81
	dervarser 1.57811s
	application 0.223849s
	<<< layer 15.1883s
	<<< layerer 78.4017s
	>>> transer
	fud: 4
	fud slize size: 20957
	derived cardinality: 6
	derived algn density: 31764.8
	derived algn density per size: 1.51571
	derived impl bi-valency percent: 67.7054
	<<< transer 0.0447722s
	>>> slicer
	slize size: 13163
	slize variable: (<<3,s>,21>,2)
	<<< slicer 0.398356s
	>>> shuffler
	<<< shuffler 0.571468s
	>>> layerer
	>>> layer       fud: 5  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 235665        rate: 8339.97
	tupler 28.2573s
	tuple cardinality: 10
	max tuple algn: 30697.5
	layer cardinality: 38
	parter  searched: 10930 rate: 9965.34
	parter 1.0968s
	roller  searched: 32131 rate: 205903
	roller 0.156049s
	der vars algn density: 25049.8
	dervarser       searched: 3996  rate: 3416.37
	dervarser 1.16966s
	application 0.168829s
	<<< layer 30.8512s
	>>> layer       fud: 5  layer: 2
	substrate cardinality: 784
	fud cardinality: 38
	tupler  searched: 66616 rate: 4100.72
	tupler 16.245s
	tuple cardinality: 10
	max tuple algn: 30183.8
	layer cardinality: 30
	parter  searched: 10930 rate: 10323.6
	parter 1.05874s
	roller  searched: 77749 rate: 463491
	roller 0.167747s
	der vars algn density: 31891
	dervarser       searched: 6957  rate: 4021.4
	dervarser 1.72999s
	application 0.157879s
	<<< layer 19.3618s
	>>> layer       fud: 5  layer: 3
	substrate cardinality: 784
	fud cardinality: 68
	tupler  searched: 62546 rate: 5752.44
	tupler 10.873s
	tuple cardinality: 10
	max tuple algn: 15403.3
	layer cardinality: 22
	parter  searched: 1210  rate: 12391.9
	parter 0.0976442s
	roller  searched: 44086 rate: 463560
	roller 0.0951031s
	der vars algn density: 35628.9
	dervarser       searched: 10443 rate: 4148.77
	dervarser 2.51713s
	application 0.175527s
	<<< layer 13.7606s
	>>> layer       fud: 5  layer: 4
	substrate cardinality: 784
	fud cardinality: 90
	tupler  searched: 88564 rate: 4974.49
	tupler 17.8036s
	tuple cardinality: 10
	max tuple algn: -4118.49
	layer cardinality: 20
	parter  searched: 10930 rate: 13165.6
	parter 0.830193s
	roller  searched: 3524772       rate: 2.51295e+06
	roller 1.40264s
	der vars algn density: 35743.1
	dervarser       searched: 13177 rate: 4573.94
	dervarser 2.88089s
	application 0.157678s
	<<< layer 23.0774s
	>>> layer       fud: 5  layer: 5
	substrate cardinality: 784
	fud cardinality: 110
	tupler  searched: 99278 rate: 5154.05
	tupler 19.2621s
	tuple cardinality: 10
	max tuple algn: -4776.12
	layer cardinality: 16
	parter  searched: 10930 rate: 13313.1
	parter 0.820994s
	roller  searched: 3931820       rate: 2.21574e+06
	roller 1.77449s
	der vars algn density: 35568.7
	dervarser       searched: 15346 rate: 5032.1
	dervarser 3.04962s
	application 0.16458s
	<<< layer 25.0743s
	<<< layerer 112.232s
	>>> transer
	fud: 5
	fud slize size: 13163
	derived cardinality: 10
	derived algn density: 35743.1
	derived algn density per size: 2.71543
	derived impl bi-valency percent: 67.6087
	<<< transer 0.0392188s
	>>> slicer
	slize size: 11384
	slize variable: (<<2,s>,1>,2)
	<<< slicer 0.463038s
	>>> shuffler
	<<< shuffler 0.457886s
	>>> layerer
	>>> layer       fud: 6  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 234976        rate: 9876.96
	tupler 23.7903s
	tuple cardinality: 10
	max tuple algn: 30253.3
	layer cardinality: 40
	parter  searched: 10930 rate: 10718.5
	parter 1.01974s
	roller  searched: 32728 rate: 241014
	roller 0.135793s
	der vars algn density: 22446.5
	dervarser       searched: 4310  rate: 4150.88
	dervarser 1.03833s
	application 0.142279s
	<<< layer 26.1288s
	>>> layer       fud: 6  layer: 2
	substrate cardinality: 784
	fud cardinality: 40
	tupler  searched: 64212 rate: 5312.79
	tupler 12.0863s
	tuple cardinality: 10
	max tuple algn: 27590.8
	layer cardinality: 28
	parter  searched: 10930 rate: 10559.8
	parter 1.03505s
	roller  searched: 80994 rate: 524983
	roller 0.154279s
	der vars algn density: 27252.4
	dervarser       searched: 7695  rate: 4355.46
	dervarser 1.76675s
	application 0.136357s
	<<< layer 15.1811s
	>>> layer       fud: 6  layer: 3
	substrate cardinality: 784
	fud cardinality: 68
	tupler  searched: 81775 rate: 5350.67
	tupler 15.2831s
	tuple cardinality: 10
	max tuple algn: 13720.5
	layer cardinality: 21
	parter  searched: 10930 rate: 11600.7
	parter 0.942182s
	roller  searched: 3708482       rate: 2.1448e+06
	roller 1.72906s
	der vars algn density: 27473.8
	dervarser       searched: 9383  rate: 5095.56
	dervarser 1.84141s
	application 0.141042s
	<<< layer 19.9388s
	>>> layer       fud: 6  layer: 4
	substrate cardinality: 784
	fud cardinality: 89
	tupler  searched: 89328 rate: 5495.41
	tupler 16.255s
	tuple cardinality: 10
	max tuple algn: 12458.9
	layer cardinality: 4
	parter  searched: 10930 rate: 11583.7
	parter 0.94357s
	roller  searched: 3931820       rate: 2.09861e+06
	roller 1.87353s
	der vars algn density: 27214.3
	dervarser       searched: 10211 rate: 5022.2
	dervarser 2.03317s
	application 0.141638s
	<<< layer 21.2491s
	<<< layerer 82.5804s
	>>> transer
	fud: 6
	fud slize size: 11384
	derived cardinality: 10
	derived algn density: 27473.8
	derived algn density per size: 2.41337
	derived impl bi-valency percent: 65.3773
	<<< transer 0.0380389s
	>>> slicer
	slize size: 10515
	slize variable: (<<4,s>,7>,2)
	<<< slicer 0.576836s
	>>> shuffler
	<<< shuffler 0.449647s
	>>> layerer
	>>> layer       fud: 7  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 224088        rate: 9838.11
	tupler 22.7776s
	tuple cardinality: 10
	max tuple algn: 23770.7
	layer cardinality: 33
	parter  searched: 10930 rate: 9600.78
	parter 1.13845s
	roller  searched: 31555 rate: 199024
	roller 0.158549s
	der vars algn density: 19963.7
	dervarser       searched: 3186  rate: 4206.27
	dervarser 0.75744s
	application 0.135182s
	<<< layer 24.9697s
	>>> layer       fud: 7  layer: 2
	substrate cardinality: 784
	fud cardinality: 33
	tupler  searched: 41394 rate: 7511.69
	tupler 5.51061s
	tuple cardinality: 10
	max tuple algn: 16865.8
	layer cardinality: 29
	parter  searched: 400   rate: 13038.8
	parter 0.0306777s
	roller  searched: 23401 rate: 376845
	roller 0.0620972s
	der vars algn density: 24626.1
	dervarser       searched: 6940  rate: 4868.76
	dervarser 1.42541s
	application 0.147032s
	<<< layer 7.17817s
	>>> layer       fud: 7  layer: 3
	substrate cardinality: 784
	fud cardinality: 62
	tupler  searched: 75977 rate: 5798.3
	tupler 13.1033s
	tuple cardinality: 10
	max tuple algn: 3798.44
	layer cardinality: 26
	parter  searched: 10930 rate: 12280
	parter 0.890069s
	roller  searched: 70286 rate: 667255
	roller 0.105336s
	der vars algn density: 27119.3
	dervarser       searched: 10205 rate: 5113.63
	dervarser 1.99565s
	application 0.140472s
	<<< layer 16.237s
	>>> layer       fud: 7  layer: 4
	substrate cardinality: 784
	fud cardinality: 88
	tupler  searched: 87419 rate: 6152.55
	tupler 14.2086s
	tuple cardinality: 10
	max tuple algn: -4488.73
	layer cardinality: 15
	parter  searched: 10930 rate: 13131.8
	parter 0.832333s
	roller  searched: 489090        rate: 1.95536e+06
	roller 0.250128s
	der vars algn density: 27071.6
	dervarser       searched: 11416 rate: 5577.94
	dervarser 2.04663s
	application 0.135982s
	<<< layer 17.4761s
	<<< layerer 65.9464s
	>>> transer
	fud: 7
	fud slize size: 10515
	derived cardinality: 10
	derived algn density: 27119.3
	derived algn density per size: 2.57911
	derived impl bi-valency percent: 66.5924
	<<< transer 0.0397646s
	>>> slicer
	slize size: 7901
	slize variable: (<<5,s>,7>,2)
	<<< slicer 0.660972s
	>>> shuffler
	<<< shuffler 0.337362s
	>>> layerer
	>>> layer       fud: 8  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 230181        rate: 13644.4
	tupler 16.87s
	tuple cardinality: 10
	max tuple algn: 18970.3
	layer cardinality: 33
	parter  searched: 10930 rate: 9900.31
	parter 1.10401s
	roller  searched: 32689 rate: 218822
	roller 0.149386s
	der vars algn density: 13904.7
	dervarser       searched: 2968  rate: 6065.16
	dervarser 0.489353s
	application 0.116605s
	<<< layer 18.7321s
	>>> layer       fud: 8  layer: 2
	substrate cardinality: 784
	fud cardinality: 33
	tupler  searched: 41835 rate: 9862.5
	tupler 4.24183s
	tuple cardinality: 10
	max tuple algn: 14213.7
	layer cardinality: 29
	parter  searched: 400   rate: 11684.8
	parter 0.0342324s
	roller  searched: 59582 rate: 445232
	roller 0.133822s
	der vars algn density: 14581.2
	dervarser       searched: 5725  rate: 7482.68
	dervarser 0.7651s
	application 0.10651s
	<<< layer 5.28367s
	>>> layer       fud: 8  layer: 3
	substrate cardinality: 784
	fud cardinality: 62
	tupler  searched: 55460 rate: 11170
	tupler 4.96508s
	tuple cardinality: 10
	max tuple algn: 7348.51
	layer cardinality: 20
	parter  searched: 400   rate: 12975.1
	parter 0.0308282s
	roller  searched: 230297        rate: 936658
	roller 0.245871s
	der vars algn density: 13646.2
	dervarser       searched: 7954  rate: 8999.28
	dervarser 0.883848s
	application 0.107153s
	<<< layer 6.23496s
	<<< layerer 30.3168s
	>>> transer
	fud: 8
	fud slize size: 7901
	derived cardinality: 8
	derived algn density: 14581.2
	derived algn density per size: 1.84548
	derived impl bi-valency percent: 65.083
	<<< transer 0.0292976s
	>>> slicer
	slize size: 7686
	slize variable: (<<3,s>,1>,2)
	<<< slicer 0.770651s
	>>> shuffler
	<<< shuffler 0.335274s
	>>> layerer
	>>> layer       fud: 9  layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 212145        rate: 13501.5
	tupler 15.7127s
	tuple cardinality: 10
	max tuple algn: 17083.4
	layer cardinality: 36
	parter  searched: 10930 rate: 9662.65
	parter 1.13116s
	roller  searched: 31830 rate: 217518
	roller 0.146333s
	der vars algn density: 13907.9
	dervarser       searched: 3426  rate: 6036.17
	dervarser 0.567579s
	application 0.106203s
	<<< layer 17.6663s
	>>> layer       fud: 9  layer: 2
	substrate cardinality: 784
	fud cardinality: 36
	tupler  searched: 42510 rate: 10381.1
	tupler 4.09495s
	tuple cardinality: 10
	max tuple algn: 15346.7
	layer cardinality: 22
	parter  searched: 400   rate: 12169.7
	parter 0.0328685s
	roller  searched: 44896 rate: 428777
	roller 0.104707s
	der vars algn density: 18187.9
	dervarser       searched: 6068  rate: 6301.23
	dervarser 0.962987s
	application 0.111011s
	<<< layer 5.30875s
	>>> layer       fud: 9  layer: 3
	substrate cardinality: 784
	fud cardinality: 58
	tupler  searched: 51938 rate: 10827.4
	tupler 4.7969s
	tuple cardinality: 10
	max tuple algn: 9186.94
	layer cardinality: 26
	parter  searched: 1210  rate: 13230.4
	parter 0.091456s
	roller  searched: 44622 rate: 503326
	roller 0.0886543s
	der vars algn density: 19350.2
	dervarser       searched: 9767  rate: 6529.14
	dervarser 1.49591s
	application 0.112301s
	<<< layer 6.58756s
	>>> layer       fud: 9  layer: 4
	substrate cardinality: 784
	fud cardinality: 84
	tupler  searched: 83513 rate: 8023.85
	tupler 10.4081s
	tuple cardinality: 10
	max tuple algn: 2289.89
	layer cardinality: 20
	parter  searched: 10930 rate: 12693.1
	parter 0.8611s
	roller  searched: 3931820       rate: 2.14446e+06
	roller 1.83347s
	der vars algn density: 19235.1
	dervarser       searched: 11775 rate: 7584.53
	dervarser 1.5525s
	application 0.113433s
	<<< layer 14.7708s
	<<< layerer 44.3966s
	>>> transer
	fud: 9
	fud slize size: 7686
	derived cardinality: 10
	derived algn density: 19350.2
	derived algn density per size: 2.5176
	derived impl bi-valency percent: 66.1388
	<<< transer 0.0303374s
	>>> slicer
	slize size: 7103
	slize variable: (<<7,s>,4>,2)
	<<< slicer 0.769169s
	>>> shuffler
	<<< shuffler 0.288241s
	>>> layerer
	>>> layer       fud: 10 layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 214113        rate: 14724.2
	tupler 14.5416s
	tuple cardinality: 10
	max tuple algn: 18066.3
	layer cardinality: 27
	parter  searched: 10930 rate: 10193
	parter 1.0723s
	roller  searched: 32283 rate: 234809
	roller 0.137486s
	der vars algn density: 14605.7
	dervarser       searched: 2402  rate: 6090.29
	dervarser 0.394398s
	application 0.108269s
	<<< layer 16.2565s
	>>> layer       fud: 10 layer: 2
	substrate cardinality: 784
	fud cardinality: 27
	tupler  searched: 42445 rate: 8904.16
	tupler 4.76687s
	tuple cardinality: 10
	max tuple algn: 13115.7
	layer cardinality: 28
	parter  searched: 1210  rate: 14102.9
	parter 0.0857979s
	roller  searched: 21749 rate: 425888
	roller 0.0510674s
	der vars algn density: 17286.1
	dervarser       searched: 5609  rate: 6617.6
	dervarser 0.847588s
	application 0.110525s
	<<< layer 5.86428s
	>>> layer       fud: 10 layer: 3
	substrate cardinality: 784
	fud cardinality: 55
	tupler  searched: 68722 rate: 7878.9
	tupler 8.72229s
	tuple cardinality: 10
	max tuple algn: 3762.9
	layer cardinality: 18
	parter  searched: 10930 rate: 12057.4
	parter 0.906495s
	roller  searched: 2871578       rate: 2.08521e+06
	roller 1.37712s
	der vars algn density: 17673.6
	dervarser       searched: 7123  rate: 7012.35
	dervarser 1.01578s
	application 0.107127s
	<<< layer 12.131s
	>>> layer       fud: 10 layer: 4
	substrate cardinality: 784
	fud cardinality: 73
	tupler  searched: 75361 rate: 8316.21
	tupler 9.06195s
	tuple cardinality: 10
	max tuple algn: 3145.67
	layer cardinality: 24
	parter  searched: 10930 rate: 11689.5
	parter 0.935028s
	roller  searched: 409210        rate: 1.80263e+06
	roller 0.227008s
	der vars algn density: 17891.7
	dervarser       searched: 10223 rate: 7600.84
	dervarser 1.34498s
	application 0.110453s
	<<< layer 11.6817s
	>>> layer       fud: 10 layer: 5
	substrate cardinality: 784
	fud cardinality: 97
	tupler  searched: 87895 rate: 8793.12
	tupler 9.99589s
	tuple cardinality: 10
	max tuple algn: 2722.73
	layer cardinality: 18
	parter  searched: 10930 rate: 12202.1
	parter 0.895746s
	roller  searched: 482484        rate: 1.8457e+06
	roller 0.26141s
	der vars algn density: 17808.5
	dervarser       searched: 13740 rate: 7882.54
	dervarser 1.74309s
	application 0.114731s
	<<< layer 13.012s
	<<< layerer 59.0042s
	>>> transer
	fud: 10
	fud slize size: 7103
	derived cardinality: 10
	derived algn density: 17891.7
	derived algn density per size: 2.51889
	derived impl bi-valency percent: 66.1483
	<<< transer 0.0202565s
	>>> slicer
	slize size: 5536
	slize variable: (<<6,s>,20>,2)
	<<< slicer 0.872089s
	>>> shuffler
	<<< shuffler 0.221576s
	>>> layerer
	>>> layer       fud: 11 layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 205006        rate: 18880.1
	tupler 10.8583s
	tuple cardinality: 10
	max tuple algn: 14728.6
	layer cardinality: 31
	parter  searched: 10930 rate: 10046.7
	parter 1.08792s
	roller  searched: 32336 rate: 226010
	roller 0.143073s
	der vars algn density: 11768.3
	dervarser       searched: 2970  rate: 6599.63
	dervarser 0.450025s
	application 0.0718555s
	<<< layer 12.6126s
	>>> layer       fud: 11 layer: 2
	substrate cardinality: 784
	fud cardinality: 31
	tupler  searched: 56847 rate: 8872.89
	tupler 6.40682s
	tuple cardinality: 10
	max tuple algn: 9571.07
	layer cardinality: 34
	parter  searched: 10930 rate: 11402.3
	parter 0.958578s
	roller  searched: 187878        rate: 837830
	roller 0.224244s
	der vars algn density: 14275.7
	dervarser       searched: 6911  rate: 7948.13
	dervarser 0.869512s
	application 0.0733707s
	<<< layer 8.53373s
	>>> layer       fud: 11 layer: 3
	substrate cardinality: 784
	fud cardinality: 65
	tupler  searched: 58068 rate: 13511.5
	tupler 4.29769s
	tuple cardinality: 10
	max tuple algn: 5496.01
	layer cardinality: 22
	parter  searched: 1210  rate: 15909.5
	parter 0.076055s
	roller  searched: 151734        rate: 1.14001e+06
	roller 0.133099s
	der vars algn density: 14673.6
	dervarser       searched: 9862  rate: 8937.44
	dervarser 1.10345s
	application 0.0767021s
	<<< layer 5.68816s
	>>> layer       fud: 11 layer: 4
	substrate cardinality: 784
	fud cardinality: 87
	tupler  searched: 81037 rate: 10964.1
	tupler 7.39109s
	tuple cardinality: 10
	max tuple algn: -1960.04
	layer cardinality: 20
	parter  searched: 10930 rate: 12968.7
	parter 0.842797s
	roller  searched: 3931820       rate: 2.17198e+06
	roller 1.81024s
	der vars algn density: 14520.1
	dervarser       searched: 12875 rate: 9605.9
	dervarser 1.34032s
	application 0.0747362s
	<<< layer 11.4604s
	<<< layerer 38.3377s
	>>> transer
	fud: 11
	fud slize size: 5536
	derived cardinality: 10
	derived algn density: 14673.6
	derived algn density per size: 2.65057
	derived impl bi-valency percent: 67.1233
	<<< transer 0.0194947s
	>>> slicer
	slize size: 5391
	slize variable: (<<4,s>,1>,2)
	<<< slicer 0.905798s
	>>> shuffler
	<<< shuffler 0.211554s
	>>> layerer
	>>> layer       fud: 12 layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 214771        rate: 20004.7
	tupler 10.736s
	tuple cardinality: 10
	max tuple algn: 12998.7
	layer cardinality: 30
	parter  searched: 10930 rate: 10380.7
	parter 1.05292s
	roller  searched: 32328 rate: 218759
	roller 0.147779s
	der vars algn density: 11033.2
	dervarser       searched: 2830  rate: 7165.25
	dervarser 0.394962s
	application 0.069515s
	<<< layer 12.4024s
	>>> layer       fud: 12 layer: 2
	substrate cardinality: 784
	fud cardinality: 30
	tupler  searched: 57300 rate: 9041.9
	tupler 6.33716s
	tuple cardinality: 10
	max tuple algn: 11290.8
	layer cardinality: 31
	parter  searched: 10930 rate: 10696.4
	parter 1.02184s
	roller  searched: 208812        rate: 1.08667e+06
	roller 0.192157s
	der vars algn density: 14190.6
	dervarser       searched: 6338  rate: 8158.56
	dervarser 0.776853s
	application 0.0797984s
	<<< layer 8.40903s
	>>> layer       fud: 12 layer: 3
	substrate cardinality: 784
	fud cardinality: 61
	tupler  searched: 72150 rate: 10487.5
	tupler 6.87962s
	tuple cardinality: 10
	max tuple algn: 4239.61
	layer cardinality: 22
	parter  searched: 10930 rate: 12163
	parter 0.898627s
	roller  searched: 3665992       rate: 2.26527e+06
	roller 1.61835s
	der vars algn density: 13944.9
	dervarser       searched: 7874  rate: 9640.12
	dervarser 0.816795s
	application 0.0792571s
	<<< layer 10.2939s
	<<< layerer 31.1466s
	>>> transer
	fud: 12
	fud slize size: 5391
	derived cardinality: 10
	derived algn density: 14190.6
	derived algn density per size: 2.63228
	derived impl bi-valency percent: 66.987
	<<< transer 0.0186104s
	>>> slicer
	slize size: 5369
	slize variable: (<<6,s>,1>,2)
	<<< slicer 1.02691s
	>>> shuffler
	<<< shuffler 0.22123s
	>>> layerer
	>>> layer       fud: 13 layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 208236        rate: 18847.3
	tupler 11.0486s
	tuple cardinality: 10
	max tuple algn: 14624.5
	layer cardinality: 30
	parter  searched: 10930 rate: 9751.11
	parter 1.1209s
	roller  searched: 43106 rate: 296829
	roller 0.145222s
	der vars algn density: 10137.6
	dervarser       searched: 2710  rate: 7876.04
	dervarser 0.344081s
	application 0.0693537s
	<<< layer 12.7294s
	>>> layer       fud: 13 layer: 2
	substrate cardinality: 784
	fud cardinality: 30
	tupler  searched: 37680 rate: 13836.6
	tupler 2.72322s
	tuple cardinality: 10
	max tuple algn: 10286.1
	layer cardinality: 23
	parter  searched: 400   rate: 11567.2
	parter 0.0345804s
	roller  searched: 135983        rate: 694032
	roller 0.195932s
	der vars algn density: 12770.7
	dervarser       searched: 5466  rate: 7915.67
	dervarser 0.690529s
	application 0.0664657s
	<<< layer 3.71189s
	>>> layer       fud: 13 layer: 3
	substrate cardinality: 784
	fud cardinality: 53
	tupler  searched: 48188 rate: 14414.1
	tupler 3.3431s
	tuple cardinality: 10
	max tuple algn: 9314.17
	layer cardinality: 23
	parter  searched: 400   rate: 12984
	parter 0.030807s
	roller  searched: 46373 rate: 472117
	roller 0.0982236s
	der vars algn density: 10521.7
	dervarser       searched: 7846  rate: 10869
	dervarser 0.721868s
	application 0.0691824s
	<<< layer 4.26665s
	<<< layerer 20.7575s
	>>> transer
	fud: 13
	fud slize size: 5369
	derived cardinality: 10
	derived algn density: 12770.7
	derived algn density per size: 2.3786
	derived impl bi-valency percent: 65.1252
	<<< transer 0.0166437s
	>>> slicer
	slize size: 5095
	slize variable: (<<5,s>,1>,2)
	<<< slicer 1.08037s
	>>> shuffler
	<<< shuffler 0.19098s
	>>> layerer
	>>> layer       fud: 14 layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 186765        rate: 19546.1
	tupler 9.55508s
	tuple cardinality: 10
	max tuple algn: 13414.3
	layer cardinality: 38
	parter  searched: 10930 rate: 10428.8
	parter 1.04805s
	roller  searched: 32614 rate: 235372
	roller 0.138563s
	der vars algn density: 10695.1
	dervarser       searched: 3896  rate: 8406.64
	dervarser 0.463443s
	application 0.0730335s
	<<< layer 11.2793s
	>>> layer       fud: 14 layer: 2
	substrate cardinality: 784
	fud cardinality: 38
	tupler  searched: 41284 rate: 15597.7
	tupler 2.6468s
	tuple cardinality: 10
	max tuple algn: 5607.48
	layer cardinality: 21
	parter  searched: 400   rate: 11986.9
	parter 0.0333697s
	roller  searched: 59637 rate: 478234
	roller 0.124703s
	der vars algn density: 7720.6
	dervarser       searched: 4856  rate: 13164.2
	dervarser 0.36888s
	application 0.0689499s
	<<< layer 3.2439s
	<<< layerer 14.5662s
	>>> transer
	fud: 14
	fud slize size: 5095
	derived cardinality: 10
	derived algn density: 10695.1
	derived algn density per size: 2.09913
	derived impl bi-valency percent: 63.134
	<<< transer 0.0169863s
	>>> slicer
	slize size: 4959
	slize variable: (<<4,s>,10>,2)
	<<< slicer 1.14869s
	>>> shuffler
	<<< shuffler 0.208712s
	>>> layerer
	>>> layer       fud: 15 layer: 1
	substrate cardinality: 784
	fud cardinality: 0
	tupler  searched: 184926        rate: 19416.3
	tupler 9.52428s
	tuple cardinality: 10
	max tuple algn: 13499.1
	layer cardinality: 35
	parter  searched: 10930 rate: 10236
	parter 1.0678s
	roller  searched: 32512 rate: 222585
	roller 0.146066s
	der vars algn density: 9985.75
	dervarser       searched: 3330  rate: 7893.57
	dervarser 0.421863s
	application 0.0714813s
	<<< layer 11.2327s
	>>> layer       fud: 15 layer: 2
	substrate cardinality: 784
	fud cardinality: 35
	tupler  searched: 39330 rate: 15111.5
	tupler 2.60265s
	tuple cardinality: 10
	max tuple algn: 6356.32
	layer cardinality: 18
	parter  searched: 400   rate: 12317.1
	parter 0.0324751s
	roller  searched: 59742 rate: 520242
	roller 0.114835s
	der vars algn density: 7593.15
	dervarser       searched: 3998  rate: 13238.2
	dervarser 0.302006s
	application 0.076768s
	<<< layer 3.1313s
	<<< layerer 14.4013s
	>>> transer
	fud: 15
	fud slize size: 4959
	derived cardinality: 10
	derived algn density: 9985.75
	derived algn density per size: 2.01366
	derived impl bi-valency percent: 62.5373
	<<< transer 0.0175083s
	<<< applicationer 1255.93s

	treesPaths(dr.slices)
	[861,1205,2114]
	[861,1205,2115]
	[861,1205,2116]
	[861,1205,2117]
	[861,1205,2118]
	[861,1205,2119]
	[861,1205,2120]
	[861,1205,2121]
	[861,1205,2122]
	[861,1205,2123]
	[861,1205,2124]
	[861,1205,2125]
	[861,1206]
	[861,1207]
	[861,1208]
	[861,1209]
	[861,1210]
	[861,1211,1567]
	[861,1211,1568]
	[861,1211,1569]
	[861,1211,1570,1905]
	[861,1211,1570,1906]
	[861,1211,1570,1907]
	[861,1211,1570,1908]
	[861,1211,1570,1909]
	[861,1211,1570,1910]
	[861,1211,1570,1911]
	[861,1211,1570,1912]
	[861,1211,1570,1913]
	[861,1211,1570,1914]
	[861,1211,1570,1915]
	[861,1211,1570,1916]
	[861,1211,1570,1917]
	[861,1211,1571]
	[861,1212]
	[861,1213]
	[861,1214,2364]
	[861,1214,2365]
	[861,1214,2366]
	[861,1214,2367]
	[861,1214,2368]
	[861,1214,2369]
	[861,1214,2370]
	[861,1214,2371]
	[861,1214,2372]
	[861,1214,2373]
	[861,1214,2374]
	[861,1214,2375]
	[861,1214,2376]
	[861,1214,2377]
	[861,1214,2378]
	[861,1214,2379]
	[861,1214,2380]
	[861,1214,2381]
	[861,1214,2382]
	[861,1214,2383]
	[861,1214,2384]
	[861,1214,2385]
	[861,1214,2386]
	[861,1214,2387]
	[861,1214,2388]
	[861,1214,2389]
	[861,1214,2390]
	[861,1215]
	[862]
	[863]
	[864]
	[865]
	[866]
	[867]
	[868]
	[869]
	[870]
	[871]
	[872]
	[873]
	[874]
	[875]
	[876]
	[877]
	[878]
	[879]
	[880]
	[881]
	[882]
	[883]
	[884]
	[885]
	[886]
	[887]
	[888]
	[889]
	[890]
	[891]
	[892,979,1443,2202]
	[892,979,1443,2203]
	[892,979,1443,2204]
	[892,979,1443,2205]
	[892,979,1443,2206]
	[892,979,1443,2207]
	[892,979,1443,2208]
	[892,979,1443,2209]
	[892,979,1443,2210]
	[892,979,1443,2211]
	[892,979,1443,2212]
	[892,979,1443,2213]
	[892,979,1443,2214]
	[892,979,1443,2215]
	[892,979,1444]
	[892,979,1445]
	[892,979,1446]
	[892,979,1447]
	[892,979,1448]
	[892,979,1449]
	[892,979,1450]
	[892,979,1451]
	[892,979,1452]
	[892,979,1453]
	[892,979,1454]
	[892,979,1455]
	[892,979,1456]
	[892,979,1457]
	[892,979,1458]
	[892,979,1459]
	[892,979,1460]
	[892,979,1461]
	[892,979,1462,2025]
	[892,979,1462,2026]
	[892,979,1462,2027]
	[892,979,1462,2028]
	[892,979,1462,2029]
	[892,979,1462,2030]
	[892,979,1463]
	[892,980]
	[892,981]
	[892,982]
	[892,983]
	[892,984]
	[892,985]
	[892,986]
	[892,987]
	[892,988,1103,1778]
	[892,988,1103,1779]
	[892,988,1103,1780]
	[892,988,1103,1781]
	[892,988,1103,1782]
	[892,988,1103,1783]
	[892,988,1103,1784]
	[892,988,1103,1785]
	[892,988,1103,1786]
	[892,988,1103,1787]
	[892,988,1103,1788]
	[892,988,1103,1789]
	[892,988,1104]
	[892,988,1105]
	[892,988,1106]
	[892,988,1107]
	[892,988,1108]
	[892,988,1109]
	[892,988,1110]
	[892,988,1111]
	[892,988,1112]
	[892,988,1113]
	[892,988,1114]
	[892,988,1115]
	[892,988,1116]
	[892,988,1117]
	[892,988,1118]
	[892,988,1119]
	[892,988,1120]
	[892,988,1121]
	[892,988,1122]
	[892,988,1123,1342,2275]
	[892,988,1123,1342,2276]
	[892,988,1123,1342,2277]
	[892,988,1123,1342,2278]
	[892,988,1123,1342,2279]
	[892,988,1123,1342,2280]
	[892,988,1123,1342,2281]
	[892,988,1123,1342,2282]
	[892,988,1123,1342,2283]
	[892,988,1123,1342,2284]
	[892,988,1123,1342,2285]
	[892,988,1123,1342,2286]
	[892,988,1123,1342,2287]
	[892,988,1123,1342,2288]
	[892,988,1123,1342,2289]
	[892,988,1123,1342,2290]
	[892,988,1123,1342,2291]
	[892,988,1123,1342,2292]
	[892,988,1123,1342,2293]
	[892,988,1123,1342,2294]
	[892,988,1123,1342,2295]
	[892,988,1123,1342,2296]
	[892,988,1123,1342,2297]
	[892,988,1123,1342,2298]
	[892,988,1123,1342,2299]
	[892,988,1123,1342,2300]
	[892,988,1123,1342,2301]
	[892,988,1123,1342,2302]
	[892,988,1123,1342,2303]
	[892,988,1123,1342,2304]
	[892,988,1123,1342,2305]
	[892,988,1123,1342,2306]
	[892,988,1123,1342,2307]
	[892,988,1123,1342,2308]
	[892,988,1123,1342,2309]
	[892,988,1123,1342,2310]
	[892,988,1123,1343]
	[892,988,1123,1344]
	[892,988,1123,1345]
	[892,988,1123,1346]
	[892,988,1123,1347]
	[892,988,1123,1348,1654]
	[892,988,1123,1348,1655]
	[892,988,1123,1348,1656]
	[892,988,1123,1348,1657]
	[892,988,1123,1348,1658]
	[892,988,1123,1348,1659]
	[892,988,1123,1348,1660]
	[892,988,1123,1348,1661]
	[892,988,1123,1348,1662]
	[892,988,1123,1348,1663]
	[892,988,1123,1348,1664]
	[892,988,1123,1348,1665]
	[892,988,1123,1348,1666]
	[892,988,1123,1348,1667]
	[892,988,1123,1348,1668]
	[892,988,1123,1348,1669]
	[892,988,1123,1348,1670]
	[892,988,1123,1348,1671]
	[892,988,1123,1348,1672]
	[892,988,1123,1348,1673]
	[892,988,1123,1349]
	[892,988,1124]
	[892,989]
	[893]

	NIST_model1.bin 556,280 bytes
	*/
    }


    return 0;
}

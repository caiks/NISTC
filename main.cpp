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
		    ll1.push_back((ur.listVarUCharPair[i]).first);
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

    if (true)
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
		    ll1.push_back((ur->listVarUCharPair[i]).first);
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
		    ll1.push_back((ur->listVarUCharPair[i]).first);
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
		    ll1.push_back((ur->listVarUCharPair[i]).first);
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
		    ll1.push_back((ur->listVarUCharPair[i]).first);
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

    return 0;
}

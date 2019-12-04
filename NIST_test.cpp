#include "NISTDev.h"

using namespace Alignment;
using namespace NIST;
using namespace std;

typedef std::chrono::duration<double> sec; 
typedef std::chrono::high_resolution_clock clk;

int main(int argc, char **argv)
{
    auto uvars = systemsSetVar;
    auto single = histogramSingleton_u;
    auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
    {
	return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
    };
    auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
    auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
    auto hrred = setVarsHistoryRepasReduce_u;
    auto frmul = historyRepasFudRepasMultiply_u;
    auto frvars = fudRepasSetVar;
    auto frder = fudRepasDerived;
    auto frund = fudRepasUnderlying;
    auto frdep = fudRepasSetVarsDepends;

    string model(argv[1]);

    cout << "model: " << model << endl;

    std::unique_ptr<System> uu;
    std::unique_ptr<SystemRepa> ur;
    std::unique_ptr<HistoryRepa> hr;
    {
	auto xx = trainBucketedIO(2);
	uu = std::move(std::get<0>(xx));
	ur = std::move(std::get<1>(xx));
	hr = std::move(std::get<2>(xx));
    }

    Variable digit("digit");
    auto vv = *uvars(*uu);
    auto vvl = VarUSet();
    vvl.insert(digit);
    auto vvk = VarUSet(vv);
    vvk.erase(digit);

    auto& vvi = ur->mapVarSize();
    SizeList vvk1;
    for (auto& v : sorted(vvk))
	vvk1.push_back(vvi[v]);

    SizeList vvl1{ vvi[digit] };

    cout << "train size: " << hr->size << endl;

    StrVarPtrMap m;
    std::ifstream in(model+".bin", std::ios::binary);
    auto ur1 = persistentsSystemRepa(in, m);
    auto dr = persistentsApplicationRepa(in);
    in.close();

    cout << "model cardinality: " << fudRepasSize(*dr->fud) << endl;
    cout << "derived  cardinality: " << frder(*dr->fud)->size() << endl;
    cout << "underlying cardinality: " << frund(*dr->fud)->size() << endl;

    std::map<std::size_t, std::size_t> sp;
    {
	auto hr1 = frmul(*hr, *dr->fud);
	if (hr1->evient)
	    hr1->transpose();
	auto z = hr1->size;
	auto& mvv = hr1->mapVarInt();
	auto sh = hr1->shape;
	auto rr = hr1->arr;
	auto pl = mvv[vvi[digit]];
	auto sl = sh[pl];
	auto nn = treesLeafNodes(*dr->slices);
	SizeList al(sl);
	for (auto& s : *nn)
	{
	    for (std::size_t k = 0; k < sl; k++)
		al[k] = 0;
	    auto pk = mvv[s.first];
	    for (std::size_t j = 0; j < z; j++)
	    {
		std::size_t u = rr[pk*z + j];
		if (u)
		{
		    std::size_t w = rr[pl*z + j];
		    al[w]++;
		}
	    }
	    std::size_t c = 0;
	    std::size_t cl = sl;
	    for (std::size_t k = 0; k < sl; k++)
	    {
		auto u = al[k];
		if (u > c)
		{
		    c = u;
		    cl = k;
		}
	    }
	    sp[s.first] = cl;
	}

    }
    //cout << "sp" << endl
    //    << sp << endl << endl;

    {
	auto xx = testBucketedIO(2);
	hr = std::move(std::get<2>(xx));
    }

    cout << "test size: " << hr->size << endl;

    std::size_t a = 0;
    std::size_t x = 0;
    {
	SizeList ww{ vvi[digit] };
	auto nn = treesLeafNodes(*dr->slices);
	for (auto& s : *nn)
	    ww.push_back(s.first);
	auto hr1 = hrhrred(ww.size(), ww.data(), *frmul(*hr, *dr->fud));
	if (!hr1->evient)
	    hr1->transpose();
	auto n = hr1->dimension;
	auto vv = hr1->vectorVar;
	auto sh = hr1->shape;
	auto z = hr1->size;
	auto rr = hr1->arr;
	auto sl = sh[0];
	for (std::size_t j = 0; j < z; j++)
	{
	    std::size_t cl = rr[j*n];
	    for (std::size_t i = 1; i < n; i++)
	    {
		std::size_t u = rr[j*n + i];
		if (u)
		{
		    std::size_t l = sp[vv[i]];
		    if (l == cl)
			a++;
		    else if (l == sl)
			x++;
		    break;
		}
	    }
	}

    }
    cout << "effective size: " << hr->size - x << endl;
    cout << "matches: " << a << endl;

    return 0;
}

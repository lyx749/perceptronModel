#ifndef GET_DATA_SET_HPP
#define GET_DATA_SET_HPP
#include <vector>
#include <map>
#include "config.h"
#include <random>
using inputAndOutputDataSet = std::pair<std::vector<std::pair<int, int>>, std::vector<int>>;

const int maxDataSetSize = 10;

double getDoubleRandom(double begin, double end)
{
    std::random_device seed;
    std::mt19937 get(seed());
    std::uniform_real_distribution<double> dis(begin, end);
    return dis(get);
}

int getIntRandom(int begin, int end)
{
    std::random_device seed;
    std::mt19937 get(seed());
    std::uniform_int_distribution dis(begin, end);
    return dis(get);
}

class getDataSet
{
private:
    static inline getDataSet *interface = nullptr;
    inputAndOutputDataSet IOSet;
    getDataSet(){};

public:
    static inline getDataSet *GetInterface()
    {
        if (!interface)
        {
            interface = new getDataSet();
            static freeSource f;
        }
        return interface;
    }
    inputAndOutputDataSet getSet()
    {
        int size = getIntRandom(1, maxDataSetSize);
        IOSet.first.resize(size);
        IOSet.second.resize(size);
        for (int i = 0; i < size; ++i)
        {
            std::pair<int, int> temp;
            temp.first = getIntRandom(0, 1);
            temp.second = getIntRandom(0, 1);
            IOSet.first[i] = temp;
            if (operatingMode == 1)
            {
                IOSet.second[i] = temp.first | temp.second;
            }
            else
            {
                IOSet.second[i] = temp.first & temp.second;
            }
        }
        return this->IOSet;
    }
    class freeSource
    {
    public:
        ~freeSource()
        {
            delete interface;
        }
    };
};

#endif
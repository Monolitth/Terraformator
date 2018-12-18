#ifndef WG_H
#define WG_H

#include <vector>

class wg
{
public:

    void ds(std::vector<std::vector<int>>&map,int WS, int NHMax, int NHMin);
    void ds(std::vector<std::vector<int>>&map,int WS, int NHMax, int NHMin, int seed);

    int getseednum(int seed);
};

#endif // WG_H

#include <time.h>
#include <stdlib.h>
#include <vector>
using namespace std;


#ifndef WG_H
#define WG_H

class wg
{
public:

    void ds(vector<vector<int>> &map, int WS, int NHMax, int NHMin);
    void ds(vector<vector<int>> &map, int WS, int NHMax, int NHMin, int seed);

    int getseednum(int seed);
};

#endif // WG_H

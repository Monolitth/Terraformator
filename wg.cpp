#include "wg.h"
#include <time.h>
#include <stdlib.h>

int wg::getseednum(int seed) // number generation from seed
{
    while (seed > 9999999)
            seed /= 10;
        seed = (seed << 13) ^ seed;
        int floor = (1.0 - ((seed * (seed * seed * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0)*100000.0;
        return floor;
}

void wg::ds(std::vector<std::vector<int>>&map, int WS, int NHMax, int NHMin)
{
    //============================> World Generation <============================//
        srand(time(0));
        map[0][0] = rand() % NHMax + NHMin;
        srand(time(0));
        map[0][WS - 1] = rand() % NHMax + NHMin;
        srand(time(0));
        map[WS - 1][0] = rand() % NHMax + NHMin;
        srand(time(0));
        map[WS - 1][WS - 1] = rand() % NHMax + NHMin;

        for (int sideLength = WS - 1; sideLength >= 2; sideLength /= 2) {
            int halfSide = sideLength / 2;

            for (int x = 0; x<WS - 1; x += sideLength) {
                for (int y = 0; y<WS - 1; y += sideLength) {
                    int avg = map[x][y] + //top left
                        map[x + sideLength][y] +//top right
                        map[x][y + sideLength] + //lower left
                        map[x + sideLength][y + sideLength];//lower right
                    avg /= 4.0;

                    srand(time(0));
                    map[x + halfSide][y + halfSide] =
                        avg + rand() % NHMax + NHMin;
                }
            }

            for (int x = 0; x<WS - 1; x += halfSide) {
                for (int y = (x + halfSide) % sideLength; y<WS - 1; y += sideLength) {
                    int avg =
                        map[(x - halfSide + WS) % WS][y] + //left of center
                        map[(x + halfSide) % WS][y] + //right of center
                        map[x][(y + halfSide) % WS] + //below center
                        map[x][(y - halfSide + WS) % WS]; //above center
                    avg /= 4.0;

                    srand(time(0));
                    avg = avg + rand() % NHMax + NHMin;
                    map[x][y] = avg;

                    if (x == 0)  map[WS - 1][y] = avg;
                    if (y == 0)  map[x][WS - 1] = avg;
                }
            }
        }
}

void wg::ds(std::vector<std::vector<int>>&map, int WS, int NHMax, int NHMin, int seed)
{
    //============================> World Generation <============================//
        srand(getseednum(seed));
        map[0][0] = rand() % NHMax + NHMin;
        srand(getseednum(seed * 2));
        map[0][WS - 1] = rand() % NHMax + NHMin;
        srand(getseednum(seed * 3));
        map[WS - 1][0] = rand() % NHMax + NHMin;
        srand(getseednum(seed * 4));
        map[WS - 1][WS - 1] = rand() % NHMax + NHMin;

        for (int sideLength = WS - 1; sideLength >= 2; sideLength /= 2) {
            int halfSide = sideLength / 2;

            for (int x = 0; x<WS - 1; x += sideLength) {
                for (int y = 0; y<WS - 1; y += sideLength) {
                    int avg = map[x][y] + //top left
                        map[x + sideLength][y] +//top right
                        map[x][y + sideLength] + //lower left
                        map[x + sideLength][y + sideLength];//lower right
                    avg /= 4.0;

                    srand(getseednum(seed * sideLength * halfSide * 2));
                    map[x + halfSide][y + halfSide] =
                        avg + rand() % NHMax + NHMin;
                }
            }

            for (int x = 0; x<WS - 1; x += halfSide) {
                for (int y = (x + halfSide) % sideLength; y<WS - 1; y += sideLength) {
                    int avg =
                        map[(x - halfSide + WS) % WS][y] + //left of center
                        map[(x + halfSide) % WS][y] + //right of center
                        map[x][(y + halfSide) % WS] + //below center
                        map[x][(y - halfSide + WS) % WS]; //above center
                    avg /= 4.0;

                    srand(getseednum(seed * sideLength * halfSide * 4));
                    avg = avg + rand() % NHMax + NHMin;
                    map[x][y] = avg;

                    if (x == 0)  map[WS - 1][y] = avg;
                    if (y == 0)  map[x][WS - 1] = avg;
                }
            }
        }
}

#ifndef WORLD_H
#define WORLD_H
#include "preset.h"
#include <QString>


class world
{
public:
    world(QString);

    int height_map[WS][WS];

    void load();
};

#endif // WORLD_H

#include "world.h"
#include "appsettings.h"
#include <QFile>
#include <QTextStream>

world::world(QString fname)
{
    const auto &lp = appSettings::instance().worldsPath();

    QString worldpath = lp + fname + ".wrld";

    QFile file(worldpath);

    file.open(QIODevice::ReadOnly);

    if(file.isOpen())
    {
        QTextStream in(&file);

        for(int i = 0; i < WS; i++) // y cord
        {
            QString Line;
            Line = in.readLine();
            int column = 0;
            int c = 1;
            int n = 0;
            int num = 0;
            while(column != Line.size()) // x cord
            {
                if(n > 65) break;
                if(Line[column] == ' ')
                {
                    column++;
                    c = 1;
                    n++;
                    if(c != 1)
                    height_map[WS][n] = num;
                    else {
                        continue;
                    }
                    num = 0;
                    continue;
                }
                else
                {
                    num += Line.toInt() * c;
                    c++;
                }
            }
        }
    }

    file.close();
}

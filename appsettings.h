#include "appsettings.h"
#include <QDirIterator>

static const QString worldpath = "./";

appSettings::appSettings()
{
    load();
}

appSettings::~appSettings()
{
    save();
}

appSettings &appSettings::instance()
{
    static appSettings res;
    return res;
}

void appSettings::load()
{
    savedWorlds.clear();
    QDirIterator it(worldsPath());
    while(it.hasNext())
    {
        it.next();
        QFileInfo info(it.fileInfo());
        if(info.completeSuffix() == "wrld")
            savedWorlds.push_back(info.baseName());
    }
}
void appSettings::save()
{

}

unsigned appSettings::screenWidth() const
{
    static unsigned res{800};
    return res;
}
unsigned appSettings::screenHeight() const
{
    static unsigned res{600};
    return res;
}

QString appSettings::worldsPath() const
{
    return worldpath;
}

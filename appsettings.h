#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <vector>

class appSettings
{
    unsigned mScreenWidth{0};
    unsigned mScreenHeight{0};

    appSettings();
    ~appSettings();
public:

    appSettings(const appSettings&) = delete;
    appSettings & operator=(const appSettings&) = delete;

    static appSettings &instance();

    void load();
    void save();

    unsigned screenWidth() const;
    unsigned screenHeight() const;
    QString worldsPath() const;

    std::vector<QString> savedWorlds;
};

#endif // APPSETTINGS_H

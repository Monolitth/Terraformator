#ifndef TERRAFORMATOR_H
#define TERRAFORMATOR_H

#include <QGLWidget>
#include "wg.h"
#include "preset.h"

class Terraformator : public QGLWidget
{
public:
    enum class eState
    {
        MENU,
        PLAY,
        LOAD,
        SETTINGS,
        SEEDG,
        RANDG,
        EXIT
    };

    enum class eMenu
    {
        START = -1,
        PLAY,
        LOAD,
        SETTINGS,
        EXIT,
        END
    };

    enum class ePlay
    {
        START = -1,
        GWORLDCHOOSEU,
        GWORLDCHOOSER,
        PLAY,
        EXIT
    };

private:
    eState mState{eState::MENU};
    eMenu mCurrentMenu{eMenu::PLAY};
    ePlay mPlay{ePlay::GWORLDCHOOSEU};

    std::vector<std::pair<eMenu, std::string>> mvMenu;
    std::vector<std::pair<ePlay, std::string>> mvPlay;

    std::vector<std::vector<int>> map;

    QString wName;
    QString wSeed;

    bool nameinput{false};
    bool seedinput{false};

    void _proccesing();
    void _draw();

    void _draw_menu();
    void _draw_play();
    void _draw_randg();
    void _draw_seedg();

    void _key_Released_menu(int);
    void _key_Released_play(int);
    void _key_Released_settings(int);
    void _key_Released_load(int);
    void _key_Released_randg(int);
    void _key_Released_seedg(int);
public:

    Terraformator();

    void InitializeGL();

    void resizeGL(int,int)             override;
    void paintGL()                     override;
    void keyReleaseEvent(QKeyEvent*)   override;
};

#endif // TERRAFORMATOR_H

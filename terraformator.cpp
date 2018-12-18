#include "terraformator.h"
#include "appsettings.h"
#include "preset.h"
#include "wg.h"
#include <QKeyEvent>
#include <QFile>
#include <QDir>
#include <QTextStream>

// Additional Func //
Terraformator::eMenu operator++(Terraformator::eMenu &aMenu)
{
    aMenu = Terraformator::eMenu(int(aMenu) + 1);
    if(aMenu == Terraformator::eMenu::END)
        aMenu = Terraformator::eMenu::PLAY;
    return aMenu;
}

Terraformator::eMenu operator--(Terraformator::eMenu &aMenu)
{
    aMenu = Terraformator::eMenu(int(aMenu) - 1);
    if(aMenu == Terraformator::eMenu::START)
        aMenu = Terraformator::eMenu::EXIT;
    return aMenu;
}

Terraformator::ePlay operator++(Terraformator::ePlay &aPlay)
{
    aPlay = Terraformator::ePlay(int(aPlay) + 1);
    if(aPlay == Terraformator::ePlay::PLAY)
        aPlay = Terraformator::ePlay::GWORLDCHOOSEU;
    return aPlay;
}

Terraformator::ePlay operator--(Terraformator::ePlay &aPlay)
{
    aPlay = Terraformator::ePlay(int(aPlay) - 1);
    if(aPlay == Terraformator::ePlay::START)
        aPlay = Terraformator::ePlay::GWORLDCHOOSER;
    return aPlay;
}

Terraformator::eState mStateToGameState(const Terraformator::eMenu &aMenu)
{
    switch(aMenu)
    {
    case Terraformator::eMenu::START:
    case Terraformator::eMenu::END:        return Terraformator::eState::MENU;
    case Terraformator::eMenu::PLAY:       return Terraformator::eState::PLAY;
    case Terraformator::eMenu::EXIT:       return Terraformator::eState::EXIT;
    case Terraformator::eMenu::LOAD:       return Terraformator::eState::LOAD;
    case Terraformator::eMenu::SETTINGS:   return Terraformator::eState::SETTINGS;
    }
    return Terraformator::eState::MENU;
}

Terraformator::eState mPlayToGameState(const Terraformator::ePlay & aPlay)
{
    switch(aPlay)
    {
    case Terraformator::ePlay::GWORLDCHOOSER: return Terraformator::eState::SEEDG; // TODO: исправить несоответствие // repair it
    case Terraformator::ePlay::GWORLDCHOOSEU: return Terraformator::eState::RANDG; // repair it
    }
    return Terraformator::eState::PLAY;
}
//                 //


Terraformator::Terraformator()
{
    mvMenu.push_back({eMenu::PLAY, "Play"});
    mvMenu.push_back({eMenu::LOAD, "Load"});
    mvMenu.push_back({eMenu::SETTINGS, "Settings"});
    mvMenu.push_back({eMenu::EXIT, "Exit"});

    mvPlay.push_back({ePlay::GWORLDCHOOSER, "Random"});
    mvPlay.push_back({ePlay::GWORLDCHOOSEU, "User"});

    for(size_t i = 0; i < WS; ++i) // Заполнение карты нулями
        {
            std::vector<int> temp;
            for(size_t j = 0; j < WS; ++j)
                temp.push_back(0);
            map.push_back(temp);
        }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void Terraformator::InitializeGL()
{
    static auto w = appSettings::instance().screenWidth();
    static auto h = appSettings::instance().screenHeight();
    glOrtho(0,w,h,0,0,1);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::resizeGL(int aW,int aH)
{
    static auto w = appSettings::instance().screenWidth();
    static auto h = appSettings::instance().screenHeight();
    glLoadIdentity();
    glViewport(0,0,(GLint)aW, (GLint)aH);
    glOrtho(0,w,h,0,0,1);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglClearColor(Qt::darkCyan);

    _proccesing();

    _draw();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::keyReleaseEvent(QKeyEvent* apKeyEvent)
{
    switch(mState)
    {
    case eState::MENU:
        _key_Released_menu(apKeyEvent->key());
        break;
    case eState::PLAY:
        _key_Released_play(apKeyEvent->key());
        break;
    case eState::EXIT:
        close();
        break;
    case eState::LOAD:
        _key_Released_load(apKeyEvent->key());
        break;
    case eState::SETTINGS:
        _key_Released_settings(apKeyEvent->key());
        break;
    case eState::RANDG:
        _key_Released_randg(apKeyEvent->key());
        break;
    case eState::SEEDG:
        _key_Released_seedg(apKeyEvent->key());
        break;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_proccesing()
{
    switch(mState)
    {
    case eState::MENU:
        break;
    case eState::EXIT:
        close();
        break;
    case eState::PLAY:
        break;
    case eState::LOAD:
        break;
    case eState::SETTINGS:
        break;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_draw()
{
    switch(mState)
    {
    case eState::MENU:
        _draw_menu();
        break;
    case eState::EXIT:
        break;
    case eState::PLAY:
        _draw_play();
        break;
    case eState::RANDG:
        _draw_randg();
        break;
    case eState::SEEDG:
        _draw_seedg();
        break;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_draw_menu()
{
    static auto app_w = appSettings::instance().screenWidth()  /2.f;
    static auto app_h = appSettings::instance().screenHeight() /3.f;

    static auto font          = QFont("Sans", 25);
    static auto font_selected = QFont("Sans", 30);
    static auto Tfont         = QFont("Sans", 25);
    Tfont.setBold(true);
    font_selected.setBold(true);

    auto x  = app_w - 100;
    auto y  = app_h;
    auto dy = 55.f;
    int end = mvMenu.size();

    qglColor(Qt::white);
    renderText(x-90,y,"Terraformator", Tfont);
    y+= dy;
    for(int i = 0; i < end; i++)
    {
        if(i == (int)mCurrentMenu)
        {
            qglColor(Qt::red);
            renderText(x,y,mvMenu[i].second.c_str(), font_selected);
        }
        else
        {
            qglColor(Qt::white);
            renderText(x,y,mvMenu[i].second.c_str(), font);
        }
        y+= dy;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_draw_play()
{
    static auto app_w = appSettings::instance().screenWidth()  /2.f;
    static auto app_h = appSettings::instance().screenHeight() /3.f;

    static auto font          = QFont("Sans", 25);
    static auto font_selected = QFont("Sans", 30);
    static auto Tfont         = QFont("Sans", 25);
    Tfont.setBold(true);
    font_selected.setBold(true);

    auto x  = app_w - 100;
    auto y  = app_h;
    auto dy = 185.f;
    int end = mvPlay.size();
    qglColor(Qt::white);
    renderText(x-100,y,"Choose your world", Tfont);
    y+= 55;
    for(int i = 0; i < end; i++)
    {
        if(i == (int)mPlay)
        {
            qglColor(Qt::red);
            renderText(x-55,y,mvPlay[i].second.c_str(), font_selected);
        }
        else
        {
            qglColor(Qt::white);
            renderText(x-30,y,mvPlay[i].second.c_str(), font);
        }
        x+= dy;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_draw_randg()
{
    static auto app_w = appSettings::instance().screenWidth()  /2.f;
    static auto app_h = appSettings::instance().screenHeight() /3.f;

    static auto font          = QFont("Sans", 25);
    static auto Tfont         = QFont("Sans", 25);
    Tfont.setBold(true);

    auto x  = app_w - 100;
    auto y  = app_h;
    auto dy = 55.f;
    auto dx = 20.f;
    if(!nameinput)
    {
    qglColor(Qt::white);
    renderText(x,y,"Input world name:", Tfont);
    y += dy;
    renderText(x, y, wName, font);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_draw_seedg()
{
    static auto app_w = appSettings::instance().screenWidth()  /2.f;
    static auto app_h = appSettings::instance().screenHeight() /3.f;

    static auto font          = QFont("Sans", 25);
    static auto Tfont         = QFont("Sans", 25);
    Tfont.setBold(true);

    auto x  = app_w - 100;
    auto y  = app_h;
    auto dy = 55.f;
    auto dx = 20.f;
    qglColor(Qt::white);
    if(!nameinput)
    {
    renderText(x,y,"Input world name:", Tfont);
    y += dy;
    renderText(x, y, wName, font);
    }
    else
    {
        renderText(x,y,"Input seed:", Tfont);
        y += dy;
        renderText(x, y, wSeed, font);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------


void Terraformator::_key_Released_menu(int aKey)
{
    switch(aKey)
    {
    case     Qt::Key_Up:
        --mCurrentMenu;
        break;
    case   Qt::Key_Down:
        ++mCurrentMenu;
        break;
    case  Qt::Key_Enter:
    case Qt::Key_Return:
        mState = mStateToGameState(mCurrentMenu);
        break;
    }
    updateGL();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_key_Released_play(int aKey)
{
    switch(aKey)
    {
    case     Qt::Key_Left:
        ++mPlay;
        break;
    case   Qt::Key_Right:
        --mPlay;
        break;
    case  Qt::Key_Enter:
    case Qt::Key_Return:
        mState = mPlayToGameState(mPlay);
        break;
    case Qt::Key_Escape:
        mState = eState::MENU;
        break;
    }
    updateGL();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_key_Released_settings(int aKey)
{
    switch(aKey)
    {
    case Qt::Key_Escape:
        mState = eState::MENU;
        break;
    }
    updateGL();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_key_Released_load(int aKey)
{
    switch(aKey)
    {
    case Qt::Key_Escape:
        mState = eState::MENU;
        break;
    }
    updateGL();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
    void Terraformator::_key_Released_randg(int aKey)
    {
        switch(aKey)
        {
        case Qt::Key_Escape:
            mState = eState::MENU;
            wName.clear();
            nameinput = false;
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if(!nameinput)
                nameinput = true;
            if(nameinput)
            {
                if(wName.size() == 0 || wName.size() == 1)
                    nameinput = false;
                else {
                    wg GEN;
                    GEN.ds(map, WS, NHMax, NHMin);

                    const auto &lp = appSettings::instance().worldsPath();

                    QString path =  "./" + wName + ".wrld";
                    QFile file(path);
                    file.open(QIODevice::WriteOnly);
                    QTextStream in(&file);

                        for(int i = 0; i < WS; i++)
                        {
                            for(int o = 0; o < WS; o++)
                            {
                                in << map[i][o];
                                in << " ";
                            }
                            in << endl << endl;
                        }
                        file.close();

                        mState = eState::MENU;
                        nameinput = false;

            }
            }
            break;
        case Qt::Key_0:
            wName += '0';
            break;
        case Qt::Key_1:
            wName += '1';
            break;
        case Qt::Key_2:
            wName += '2';
            break;
        case Qt::Key_3:
            wName += '3';
            break;
        case Qt::Key_4:
            wName += '4';
            break;
        case Qt::Key_5:
            wName += '5';
            break;
        case Qt::Key_6:
            wName += '6';
            break;
        case Qt::Key_7:
            wName += '7';
            break;
        case Qt::Key_8:
            wName += '8';
            break;
        case Qt::Key_9:
            wName += '9';
            break;
        case Qt::Key_Q:
            wName += 'Q';
            break;
        case Qt::Key_W:
            wName += 'W';
            break;
        case Qt::Key_E:
            wName += 'E';
            break;
        case Qt::Key_R:
            wName += 'R';
            break;
        case Qt::Key_T:
            wName += 'T';
            break;
        case Qt::Key_Y:
            wName += 'Y';
            break;
        case Qt::Key_U:
            wName += 'U';
            break;
        case Qt::Key_I:
            wName += 'I';
            break;
        case Qt::Key_O:
            wName += 'O';
            break;
        case Qt::Key_P:
            wName += 'P';
            break;
        case Qt::Key_A:
            wName += 'A';
            break;
        case Qt::Key_S:
            wName += 'S';
            break;
        case Qt::Key_D:
            wName += 'D';
            break;
        case Qt::Key_F:
            wName += 'F';
            break;
        case Qt::Key_G:
            wName += 'G';
            break;
        case Qt::Key_H:
            wName += 'H';
            break;
        case Qt::Key_J:
            wName += 'J';
            break;
        case Qt::Key_K:
            wName += 'K';
            break;
        case Qt::Key_L:
            wName += 'L';
            break;
        case Qt::Key_Z:
            wName += 'Z';
            break;
        case Qt::Key_X:
            wName += 'X';
            break;
        case Qt::Key_C:
            wName += 'C';
            break;
        case Qt::Key_V:
            wName += 'V';
            break;
        case Qt::Key_B:
            wName += 'B';
            break;
        case Qt::Key_N:
            wName += 'N';
            break;
        case Qt::Key_M:
            wName += 'M';
            break;
        }
        updateGL();
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------
    void Terraformator::_key_Released_seedg(int aKey)
    {
        switch(aKey)
        {
        case Qt::Key_Escape:
            mState = eState::MENU;
            wName.clear();
            nameinput = false;
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if(!nameinput)
                nameinput = true;
            if(!seedinput)
                seedinput = true;
            break;
        case Qt::Key_0:
            if(nameinput)
                wSeed += '0';
            wName += '0';
            break;
        case Qt::Key_1:
            if(nameinput)
                wSeed += '1';
            wName += '1';
            break;
        case Qt::Key_2:
            if(nameinput)
                wSeed += '2';
            wName += '2';
            break;
        case Qt::Key_3:
            if(nameinput)
                wSeed += '3';
            wName += '3';
            break;
        case Qt::Key_4:
            if(nameinput)
                wSeed += '4';
            wName += '4';
            break;
        case Qt::Key_5:
            if(nameinput)
                wSeed += '5';
            wName += '5';
            break;
        case Qt::Key_6:
            if(nameinput)
                wSeed += '6';
            wName += '6';
            break;
        case Qt::Key_7:
            if(nameinput)
                wSeed += '7';
            wName += '7';
            break;
        case Qt::Key_8:
            if(nameinput)
                wSeed += '8';
            wName += '8';
            break;
        case Qt::Key_9:
            if(nameinput)
                wSeed += '9';
            wName += '9';
            break;
        case Qt::Key_Q:
            wName += 'Q';
            break;
        case Qt::Key_W:
            wName += 'W';
            break;
        case Qt::Key_E:
            wName += 'E';
            break;
        case Qt::Key_R:
            wName += 'R';
            break;
        case Qt::Key_T:
            wName += 'T';
            break;
        case Qt::Key_Y:
            wName += 'Y';
            break;
        case Qt::Key_U:
            wName += 'U';
            break;
        case Qt::Key_I:
            wName += 'I';
            break;
        case Qt::Key_O:
            wName += 'O';
            break;
        case Qt::Key_P:
            wName += 'P';
            break;
        case Qt::Key_A:
            wName += 'A';
            break;
        case Qt::Key_S:
            wName += 'S';
            break;
        case Qt::Key_D:
            wName += 'D';
            break;
        case Qt::Key_F:
            wName += 'F';
            break;
        case Qt::Key_G:
            wName += 'G';
            break;
        case Qt::Key_H:
            wName += 'H';
            break;
        case Qt::Key_J:
            wName += 'J';
            break;
        case Qt::Key_K:
            wName += 'K';
            break;
        case Qt::Key_L:
            wName += 'L';
            break;
        case Qt::Key_Z:
            wName += 'Z';
            break;
        case Qt::Key_X:
            wName += 'X';
            break;
        case Qt::Key_C:
            wName += 'C';
            break;
        case Qt::Key_V:
            wName += 'V';
            break;
        case Qt::Key_B:
            wName += 'B';
            break;
        case Qt::Key_N:
            wName += 'N';
            break;
        case Qt::Key_M:
            wName += 'M';
            break;
        }
        updateGL();

    }


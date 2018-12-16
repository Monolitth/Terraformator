#include "terraformator.h"
#include "appsettings.h"
#include <QKeyEvent>

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
    case Terraformator::ePlay::GWORLDCHOOSER: return Terraformator::eState::RANDG;
    case Terraformator::ePlay::GWORLDCHOOSEU: return Terraformator::eState::SEEDG;
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
        break;
    case eState::SEEDG:
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
    auto dy = 185.f;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void Terraformator::_draw_seedg()
{
    
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
        --mPlay;
        break;
    case   Qt::Key_Right:
        ++mPlay;
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
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
        case Qt::Key_0:
            if(nameinput = true)
            {
                wSeed.push_back(aKey);
                break;
            }
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if(!nameinput)
                nameinput = true;
            if(!seedinput)
                seedinput = true;
        case Qt::Key_Any:
            if(!nameinput)
                wName.push_back(aKey);
        }
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------
    void Terraformator::_key_Released_seedg(int aKey)
    {
        
    }
    

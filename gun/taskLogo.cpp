#include "stdafx.h"
#include "taskLogo.h"
#include "taskGameLocal.h"

void TaskLogo::vBegin(){
    _step = LOGO;
    
    _pSptLogo = lw::Sprite::createFromAtlas(_af("teamLogo.png"));
    _pSptLogo->setPos(_as(170), _as(150));
    _pSptTitle = lw::Sprite::createFromAtlas(_af("title.png"));
    _pSptTitle->setPos(_as(146), _as(218));
    
    _alpha = 1.f;
    
    _pSndOpening = lw::SoundSource::create("opening.wav", 1, false);
    _pSndOpening->play();
}

void TaskLogo::vEnd(){
    delete _pSptLogo;
    delete _pSptTitle;
    delete _pSndOpening;
}

void TaskLogo::vMain(){
    if ( !_pSndOpening->isPlaying() ){
        switchTo(TaskGameLocal::ps());
    }
}

void TaskLogo::vDraw(){
    glClearColor(117.f/255.f, 150.f/255.f, 166.f/255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if ( _step == LOGO ){
        _alpha -= .015f;
        _pSptLogo->setColor(lw::Color(1.f, 1.f, 1.f, _alpha));
        _pSptLogo->draw();
        if ( _alpha <= 0 ){
            _step = TITLE;
        }
    }else{
        _alpha += .015f;
        _pSptTitle->setColor(lw::Color(1.f, 1.f, 1.f, _alpha));
        _pSptTitle->draw();
//        if ( _alpha >= 5.f ){
//            stop();
//            TaskMode::s().start();
//        }
    }
}

bool TaskLogo::vEvent(const lw::TouchEvent& evt){
    return false;
}

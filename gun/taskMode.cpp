#include "stdafx.h"
#include "TaskMode.h"

void TaskMode::vBegin(){
    float w, h;
    lw::App::s().getScreenSize(w, h);
    _pSptBGLeft = lw::Sprite::createFromAtlas("white.png");
    float u, v, uvw, uvh;
    _pSptBGLeft->getUV(u, v, uvw, uvh);
    u += 2;
    v += 2;
    uvw -= 4;
    uvh -= 4;
    _pSptBGLeft->setUV(u, v, uvw, uvh);
    _pSptBGLeft->setSize(w*.5f, h);
    _pSptBGLeft->setColor(lw::Color(117, 150, 166, 255));
    _pSptBGRight = lw::Sprite::createFromAtlas("white.png");
    _pSptBGRight->setUV(u, v, uvw, uvh);
    _pSptBGRight->setSize(w*.5f, h);
    _pSptBGRight->setPos(w*.5f, 0.f);
    _pSptBGRight->setColor(lw::Color(238, 226, 211, 255));
}

void TaskMode::vEnd(){
    delete _pSptBGLeft;
    delete _pSptBGRight;
}

void TaskMode::vMain(){
    
}

void TaskMode::vDraw(){
    glClearColor(117.f/255.f, 150.f/255.f, 166.f/255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _pSptBGLeft->draw();
    _pSptBGRight->draw();
}

bool TaskMode::vEvent(const lw::TouchEvent& evt){
    return false;
}

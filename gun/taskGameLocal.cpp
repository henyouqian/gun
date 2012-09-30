#include "stdafx.h"
#include "taskGameLocal.h"

namespace {
    const cml::Vector2 wheelBulletPos[6] = {
        cml::Vector2(71.f, 240.f),
        cml::Vector2(79.f, 256.f),
        cml::Vector2(71.f, 272.f),
        cml::Vector2(52.f, 272.f),
        cml::Vector2(43.f, 256.f),
        cml::Vector2(52.f, 240.f),
    };
}

void TaskGameLocal::vBegin(){
    lw::srand();
    
    _pSptBG = lw::Sprite::createFromFile("white.png");
    float scale = lw::App::s().getScreenScale();
    _pSptBG->setSize(480*scale, 320*scale);
    _pSptBG->setColor(lw::Color(238, 226, 211, 255));
    
    _pSptGun = lw::Sprite::createFromAtlas(_af("gun.png"));
    _pSptGun->setPos(_as(76), _as(41));
    
    _pSptHammer = lw::Sprite::createFromAtlas(_af("hammer.png"));
    _pSptHammer->setAnchor(_as(2), _as(38));
    _pSptHammer->setPos(_as(303), _as(80));
    
    _step = READY;
    _evtHammer = NULL;
    
    _pSndGunLoad = lw::SoundSource::create("gunload.wav", 1, false);
    _pSndFire = lw::SoundSource::create("fire.wav", 1, false);
    _pSndMiss = lw::SoundSource::create("miss.wav", 1, false);
    
    for ( int i = 0; i < 3; ++i ){
        std::stringstream ss;
        ss << "count" << i+1 << ".png";
        _pSptCount[i] = lw::Sprite::createFromAtlas(_af(ss.str().c_str()));
        _pSptCount[i]->setAnchor(_as(25), _as(17));
        _pSptCount[i]->setPos(_as(260), _as(220));
    }
    
    _pSptWheel = lw::Sprite::createFromAtlas(_af("wheel.png"));
    _pSptWheel->setPos(_as(233), _as(56));
    
    _pSptWheelUI = lw::Sprite::createFromAtlas(_af("wheelUI.png"));
    _pSptWheelUI->setPos(_as(27), _as(226));
    
    _pSptPlayer1 = lw::Sprite::createFromAtlas(_af("player1.png"));
    _pSptPlayer1->setPos(_as(226), _as(273));
    _pSptPlayer2 = lw::Sprite::createFromAtlas(_af("player2.png"));
    _pSptPlayer2->setPos(_as(226), _as(273));
    
    for ( int i = 0; i < 5; ++i ){
        std::stringstream ss;
        ss << i+1 << "-6" << ".png";
        _pSptRound[i] = lw::Sprite::createFromAtlas(_af(ss.str().c_str()));
        _pSptRound[i]->setPos(_as(44), _as(287));
    }
    
    _pSptYouWin = lw::Sprite::createFromAtlas(_af("youwin.png"));
    _pSptYouWin->setPos(_as(228), _as(286));
    _pSptYouLose = lw::Sprite::createFromAtlas(_af("youlose.png"));
    _pSptYouLose->setPos(_as(226), _as(286));
    
    _pSptQuestionMark = lw::Sprite::createFromAtlas(_af("questionMark.png"));
    _pSptQuestionMark->setAnchor(_as(7), _as(7));
    _pSptLoseMark = lw::Sprite::createFromAtlas(_af("loseMark.png"));
    _pSptLoseMark->setAnchor(_as(7), _as(7));
    
    _hammerBack = false;
    
    reset();
}

void TaskGameLocal::vEnd(){
    delete _pSptBG;
    delete _pSptGun;
    delete _pSptHammer;
    delete _pSptWheelUI;
    delete _pSptPlayer1;
    delete _pSptPlayer2;
    delete _pSptYouWin;
    delete _pSptYouLose;
    delete _pSptLoseMark;
    delete _pSptQuestionMark;
    delete _pSndGunLoad;
    delete _pSndFire;
    delete _pSndMiss;
    for ( int i = 0; i < 3; ++i ){
        delete _pSptCount[i];
    }
    for ( int i = 0; i < 5; ++i ){
        delete _pSptRound[i];
    }
}

void TaskGameLocal::vMain(){
    if ( _step == READY ){
        if ( _hammerBack && _evtHammer == NULL ){
            float rot = _pSptHammer->getRotate();
            rot -= 0.15f;
            if ( rot < 0.f ){
                rot = 0.f;
                _hammerBack = false;
            }
            _pSptHammer->setRotate(rot);
        }
    }else if ( _step == SECOND_COUNT ){
        _secondCount += 0.033333f;
        if ( _secondCount >= 3.f ){
            if ( _round < _fireRound ){
                miss();
            }else{
                fire();
            }
        }
    }
}

void TaskGameLocal::vDraw(){
    glClearColor(117.f/255.f, 150.f/255.f, 166.f/255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _pSptBG->draw();
    _pSptGun->draw();
    _pSptHammer->draw();
    _pSptWheel->draw();
    
    if ( _step == SECOND_COUNT ){
        for ( int i = 0; i < 3; ++i ){
            float t = _secondCount - (float)i;
            if ( t > 0.f && t < 1.f ){
                float scale = t*2.f;
                _pSptCount[2-i]->setScale(scale, scale);
                float a = std::min(-t*3.f+3.f, 1.f);
                _pSptCount[2-i]->setColor(lw::Color(1.f, 1.f, 1.f, a));
                _pSptCount[2-i]->draw();
            }
        }
    }
    
    _pSptWheelUI->draw();
    
    if ( _round % 2 == 0 ){
        _pSptPlayer1->draw();
    }else{
        _pSptPlayer2->draw();
    }
    
    _pSptRound[_round]->draw();
    
    if ( _result == 1 ){
        _pSptYouWin->draw();
    }else if ( _result == 2 ){
        _pSptYouLose->draw();
    }
    
    for ( int i = 0; i < 6; ++i ){
        if ( i >= _round ){
            if ( i == _round && _result == 2 ){
                _pSptLoseMark->setPos(wheelBulletPos[i][0], wheelBulletPos[i][1]);
                _pSptLoseMark->draw();
            }else{
                if ( i == _round && _result == 1 ){
                    continue;
                }
                _pSptQuestionMark->setPos(wheelBulletPos[i][0], wheelBulletPos[i][1]);
                _pSptQuestionMark->draw();
            }
        }
    }
}

bool TaskGameLocal::vEvent(const lw::TouchEvent& evt){
    if ( _step == READY ){
        if ( evt.type == lw::TouchEvent::TOUCH ){
            if ( _evtHammer == NULL ){
                if ( evt.x >_as(280) && evt.x <_as(340) && evt.y > _as(0) && evt.y < _as(70)){
                    _evtHammer = &evt;
                    _hammerTouchDir.set(evt.x-_as(303), evt.y-_as(80));
                    
                }
            }
        }else if ( evt.type == lw::TouchEvent::MOVE ){
            if ( &evt == _evtHammer ){
                cml::Vector2 v2(evt.x-_as(303), evt.y-_as(80));
                if ( v2.length() < .01f ){
                    _hammerBack = true;
                    _evtHammer = NULL;
                    return false;
                }
                v2.normalize();
                float rot = cml::signed_angle_2D(_hammerTouchDir, v2);
                lwinfo(rot);
                rot = std::max(0.f, rot);
                const float lim = .8f;
                if ( rot >= lim ){
                    rot = lim;
                    _pSndGunLoad->play();
                    _step = SECOND_COUNT;
                    _secondCount = 0.f;
                    _evtHammer = NULL;
                }
                _pSptHammer->setRotate(rot);
            }
            
        }else if ( evt.type == lw::TouchEvent::UNTOUCH ){
            if ( &evt == _evtHammer ){
                _hammerBack = true;
                _evtHammer = NULL;
            }
        }
        
    }else if ( _step == RESULT ){
        if ( evt.type == lw::TouchEvent::TOUCH ){
            reset();
        }
    }
    return false;
}

void TaskGameLocal::reset(){
    _round = 0;
    _fireRound = rand()%6;
    _result = 0;
    _step = READY;
}

void TaskGameLocal::fire(){
    _step = RESULT;
    _pSndFire->play();
    _pSptHammer->setRotate(0.f);
    _result = 2;
}

void TaskGameLocal::miss(){
    _step = READY;
    _pSndMiss->play();
    _pSptHammer->setRotate(0.f);
    if ( _round == 4 ){
        _result = 1;
        _step = RESULT;
    }else{
        _round++;
    }
}


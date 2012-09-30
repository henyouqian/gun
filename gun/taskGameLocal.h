#ifndef __TASK_GAMELOCAL_H__
#define __TASK_GAMELOCAL_H__

class TaskGameLocal : public lw::Task, public lw::Singleton<TaskGameLocal>{
public:
    virtual void vBegin();
    virtual void vEnd();
    virtual void vMain();
    virtual void vDraw();
    virtual bool vEvent(const lw::TouchEvent& evt);
    
private:
    lw::Sprite *_pSptBG;
    lw::Sprite *_pSptGun;
    lw::Sprite *_pSptHammer;
    lw::Sprite *_pSptCount[3];
    lw::Sprite *_pSptWheel;
    lw::Sprite *_pSptWheelUI;
    lw::Sprite *_pSptPlayer1;
    lw::Sprite *_pSptPlayer2;
    lw::Sprite *_pSptRound[5];
    lw::Sprite *_pSptYouWin;
    lw::Sprite *_pSptYouLose;
    lw::Sprite *_pSptQuestionMark;
    lw::Sprite *_pSptLoseMark;
    enum Step{
        READY,
        SECOND_COUNT,
        RESULT,
    };
    Step _step;
    const lw::TouchEvent* _evtHammer;
    cml::Vector2 _hammerTouchDir;
    lw::SoundSource *_pSndGunLoad;
    float _secondCount;
    lw::SoundSource *_pSndFire;
    lw::SoundSource *_pSndMiss;
    bool _hammerBack;
    int _round;
    int _fireRound;
    int _result;    //0=none, 1=win, 2=lose

    void reset();
    void fire();
    void miss();
};

#endif //__TASK_GAMELOCAL_H__
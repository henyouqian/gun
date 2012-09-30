#ifndef __TASK_LOGO_H__
#define __TASK_LOGO_H__

class TaskLogo : public lw::Task, public lw::Singleton<TaskLogo>{
public:
    virtual void vBegin();
    virtual void vEnd();
    virtual void vMain();
    virtual void vDraw();
    virtual bool vEvent(const lw::TouchEvent& evt);
    
private:
    enum Step{
        LOGO,
        TITLE,
    };
    Step _step;
    lw::Sprite *_pSptLogo;
    lw::Sprite *_pSptTitle;
    float _alpha;
    lw::SoundSource *_pSndOpening;
};

#endif //__TASK_LOGO_H__
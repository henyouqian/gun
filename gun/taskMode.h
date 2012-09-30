#ifndef __TASK_MODE_H__
#define __TASK_MODE_H__

class TaskMode : public lw::Task, public lw::Singleton<TaskMode>{
public:
    virtual void vBegin();
    virtual void vEnd();
    virtual void vMain();
    virtual void vDraw();
    virtual bool vEvent(const lw::TouchEvent& evt);
    
private:
    lw::Sprite *_pSptBGLeft;
    lw::Sprite *_pSptBGRight;
};

#endif //__TASK_MODE_H__
#include "app.h"
#include "taskLogo.h"
#include "taskMode.h"
#include "taskGameLocal.h"

App::App(){
    lw::addAtlas("tex1.xml");
    
    new TaskLogo();
    new TaskMode();
    new TaskGameLocal();
    
    //TaskLogo::s().start();
    TaskGameLocal::s().start();
}

App::~App(){
    delete TaskLogo::ps();
    delete TaskMode::ps();
    delete TaskGameLocal::ps();
}
//
//  MainMenuScene.h
//  Zombie3_4
//
//  Created by jl on 15/6/3.
//
//

#ifndef __Zombie3_4__MainMenuScene__
#define __Zombie3_4__MainMenuScene__

#include <stdio.h>


#include "GameHeader.h"

/**
 k_ClassDes
 */

class MainMenuScene : public Layer
{
public:
    static Scene* createScene();
    CREATE_FUNC(MainMenuScene);
    virtual bool init();
protected:
    Layout* m_RootNode;
private:
    void Button_play_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //
    void Button_quit_BtnOnTouch(Ref* sender,Widget::TouchEventType type);
};


#endif /* defined(__Zombie3_4__MainMenuScene__) */

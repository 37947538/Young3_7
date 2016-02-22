//
//  BossLevelLayer.h
//  Zombie3_4
//
//  Created by liuye on 15/9/10.
//
//

#ifndef __Zombie3_4__BossLevelLayer__
#define __Zombie3_4__BossLevelLayer__

#include <stdio.h>
#include "PopBase.h"

class BossLevelLayer : public PopBase
{
public:
    CREATE_FUNC(BossLevelLayer);
    virtual bool init();
private:
    void Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type);
    void LevelButton_OnTouch(Ref* sender,Widget::TouchEventType type);
};

#endif /* defined(__Zombie3_4__BossLevelLayer__) */

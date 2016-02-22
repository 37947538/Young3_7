//
//  DayRewardLayer.h
//  Zombie3_4
//  每日奖励
//  Created by liuye on 15/10/20.
//
//

#ifndef __Zombie3_4__DayRewardLayer__
#define __Zombie3_4__DayRewardLayer__

#include <stdio.h>
#include "PopBase.h"

class DayRewardLayer : public PopBase
{
public:
    ~DayRewardLayer();
    DayRewardLayer();
    CREATE_FUNC(DayRewardLayer);
    virtual bool init();
    virtual void onEnter();
    GameCallback updateCalllback;
protected:
    Layout* m_RootNode;
private:
    void closeButton_OnTouch(Ref* sender,Widget::TouchEventType type);      //关闭
    void enterButton_OnTouch(Ref* sender,Widget::TouchEventType type);      //确定
};

#endif /* defined(__Zombie3_4__DayRewardLayer__) */

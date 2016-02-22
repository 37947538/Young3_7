//
//  LotteryLayer.h
//  Zombie3_4
//  抽奖界面
//  Created by yuankang on 15/7/27.
//
//

#ifndef __Zombie3_4__LotteryLayer__
#define __Zombie3_4__LotteryLayer__

#include "GameHeader.h"
#include "PopBase.h"

class LotteryLayer : public PopBase
{
public:
    static Scene* createScene();
    CREATE_FUNC(LotteryLayer);
    virtual bool init();
    GameCallback updateCallback;                 //更新回调
protected:
    Layout* m_RootNode;
private:
    void onEnter();
    void Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //关闭
    void Button_Luck_BtnOnTouch(Ref* sender,Widget::TouchEventType type);
};

#endif /* defined(__Zombie3_4__LotteryLayer__) */

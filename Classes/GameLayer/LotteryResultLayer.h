//
//  LotteryResultLayer.h
//  Zombie3_4
//
//  Created by liuye on 15/8/31.
//
//

#ifndef __Zombie3_4__LotteryResultLayer__
#define __Zombie3_4__LotteryResultLayer__

#include <stdio.h>
#include "PopBase.h"
#include "Weapon.h"

class LotteryResultLayer : public PopBase
{
public:
    static Scene* createScene();
    CREATE_FUNC(LotteryResultLayer);
    virtual bool init();
    void setTypeID(int typeID){ m_TypeID=typeID; }
    GameCallback closeBtnCallback;                  //关闭回调
protected:
    Layout* m_RootNode;
    Button* m_CloseButton;
    Vector<__Integer*> vectorQuality;
    int m_TypeID=0;                                 //抽奖类型
    int m_QualityCount=0;                           //奖励品级数
private:
    void onEnter();
    void Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //关闭
    void randStart();
    void luck(int index);
    void setCloseButtonVisible();
};

#endif /* defined(__Zombie3_4__LotteryResultLayer__) */

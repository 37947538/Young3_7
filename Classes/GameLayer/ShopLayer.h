//
//  ShopLayer.h
//  Zombie3_4
//
//  Created by yuankang on 15/7/27.
//
//

#ifndef __Zombie3_4__ShopLayer__
#define __Zombie3_4__ShopLayer__

#include "GameHeader.h"
#include "PopBase.h"

class ShopLayer : public PopBase
{
public:
    CREATE_FUNC(ShopLayer);
    virtual bool init();
    GameCallback updateCallback;                 //更新回调
protected:
    Layout* m_RootNode;
private:
    void onEnter();
    void Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type);          //关闭
    void Button_BuyGold_BtnOnTouch(Ref* sender,Widget::TouchEventType type);        //购买金币
    void Button_BuyDia_BtnOnTouch(Ref* sender,Widget::TouchEventType type);         //购买钻石
};

#endif /* defined(__Zombie3_4__ShopLayer__) */

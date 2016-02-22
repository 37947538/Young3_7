//
//  PopBuyHeroLayer.h
//  Zombie3_4
//
//  Created by liuye on 15/8/27.
//
//

#ifndef __Zombie3_4__PopBuyHeroLayer__
#define __Zombie3_4__PopBuyHeroLayer__

#include <stdio.h>
#include "PopBase.h"

class PopBuyHeroLayer : public PopBase
{
public:
    ~PopBuyHeroLayer();
    PopBuyHeroLayer();
    CREATE_FUNC(PopBuyHeroLayer);
    CC_SYNTHESIZE(int, m_HeroIndex, HeroIndex);
    virtual bool init();
    virtual void onEnter();
    GameCallback testCallback;
    GameCallback enterCallback;
protected:
    Layout* m_RootNode;
    Text* m_GoldText;
    Text* m_HeroNameText;
private:
    void closeButton_OnTouch(Ref* sender,Widget::TouchEventType type);    //取消
    void testButton_OnTouch(Ref* sender,Widget::TouchEventType type);     //试玩
    void enterButton_OnTouch(Ref* sender,Widget::TouchEventType type);    //确定
    void setDataView();
};

#endif /* defined(__Zombie3_4__PopBuyHeroLayer__) */

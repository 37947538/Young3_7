//
//  PopFinishBuyHeroLayer.h
//  Zombie3_4
//
//  Created by liuye on 15/9/2.
//
//

#ifndef __Zombie3_4__PopFinishBuyHeroLayer__
#define __Zombie3_4__PopFinishBuyHeroLayer__

#include <stdio.h>
#include "PopBase.h"

class PopFinishBuyHeroLayer : public PopBase
{
public:
    ~PopFinishBuyHeroLayer();
    PopFinishBuyHeroLayer();
    CREATE_FUNC(PopFinishBuyHeroLayer);
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
    void enterButton_OnTouch(Ref* sender,Widget::TouchEventType type);    //确定
    void setDataView();
};

#endif /* defined(__Zombie3_4__PopFinishBuyHeroLayer__) */

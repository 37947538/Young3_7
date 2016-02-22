//
//  PopOverLayer.h
//  Zombie3_4
//
//  Created by liuye on 15/8/26.
//
//

#ifndef __Zombie3_4__PopOverLayer__
#define __Zombie3_4__PopOverLayer__

#include <stdio.h>
#include "PopBase.h"

class PopOverLayer : public PopBase
{
public:
    ~PopOverLayer();
    PopOverLayer();
    CREATE_FUNC(PopOverLayer);
    CC_SYNTHESIZE(int, m_TypeID, TypeID);
    virtual bool init();
    virtual void onEnter();
    GameCallback enterCallback;
protected:
    Layout* m_RootNode;
private:
    void enterButton_OnTouch(Ref* sender,Widget::TouchEventType type);    //确定
};

#endif /* defined(__Zombie3_4__PopOverLayer__) */

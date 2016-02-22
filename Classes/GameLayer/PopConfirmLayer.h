//
//  PopConfirmLayer.h
//  Zombie3_4
//
//  Created by liuye on 15/8/26.
//
//

#ifndef __Zombie3_4__PopConfirmLayer__
#define __Zombie3_4__PopConfirmLayer__

#include <stdio.h>
#include "PopBase.h"

class PopConfirmLayer : public PopBase
{
public:
    CREATE_FUNC(PopConfirmLayer);
    virtual bool init();
    virtual void onEnter();
    void setInfoString(const std::string& msg);
    GameCallback enterCallback;
protected:
    Layout* m_RootNode;
    Text* m_GoldText;
private:
    void closeButton_OnTouch(Ref* sender,Widget::TouchEventType type);    //取消
    void enterButton_OnTouch(Ref* sender,Widget::TouchEventType type);    //确定
};

#endif /* defined(__Zombie3_4__PopConfirmLayer__) */

//
//  ButtonHelper.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/18.
//
//

#include "ButtonHelper.h"


void ButtonHelper::buttonRed(Ref* sender, Widget::TouchEventType type){
    auto btn=(ui::Button*)sender;
    if (type==Widget::TouchEventType::BEGAN || type==Widget::TouchEventType::MOVED)
    {
        btn->setColor(Color3B::RED);
    }else
    {
        btn->setColor(Color3B::WHITE);
    }
}

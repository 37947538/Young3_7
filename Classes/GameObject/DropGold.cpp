//
//  DropGold.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/29.
//
//

#include "DropGold.h"

bool DropGold::init()
{
    m_goldSpr = Sprite::create("imgs/jinbi_2.png");
    this->addChild(m_goldSpr);
    return true;
}

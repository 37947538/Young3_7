//
//  GameBaseObject.cpp
//  Zombie3_4
//
//  Created by jl on 15/6/11.
//
//

#include "GameBaseObject.h"

GameBaseObject::GameBaseObject()
{
    m_obb=new APOBB();
}

GameBaseObject::~GameBaseObject()
{
    delete m_obb;
}

//
//  EnemyEventObject.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/10.
//
//

#include "EnemyEventObject.h"

EnemyEventObject::~EnemyEventObject()
{
    CC_SAFE_RELEASE_NULL(m_EventArg);
}

EnemyEventObject::EnemyEventObject()
{
    m_EventArg=nullptr;
    m_EnemyEvent=GameEnum::EnemyEvent::EnemyEventNone;
}
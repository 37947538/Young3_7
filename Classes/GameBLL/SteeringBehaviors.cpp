//
//  SteeringBehaviorss.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/10.
//
//

#include "SteeringBehaviors.h"
#include "GameHeader.h"
#include "BaseActionObject.h"
#include <cassert>
#include "APLibHeader.h"

SteeringBehaviors::SteeringBehaviors(BaseActionObject *agent)
{
    m_pBaseActionObject=agent;
}

SteeringBehaviors::~SteeringBehaviors()
{
    
}

//计算合力
Vec2 SteeringBehaviors::calculate()
{
    m_vSteeringForce=Vec2::ZERO;
    
    return m_vSteeringForce;
}

//计算合力
Vec2 SteeringBehaviors::calculate(float ft)
{
    m_vSteeringForce=Vec2::ZERO;
    if (m_pBaseActionObject->m_dMaxForce > 0) {
        float fdist=ft*m_pBaseActionObject->m_dAddSpeed;
        fdist=APMin(fdist, m_pBaseActionObject->m_dMaxForce);
        m_pBaseActionObject->m_dMaxForce-=fdist;
        m_vSteeringForce=m_pBaseActionObject->m_vHeading*fdist;
    }
    
    else if(m_pBaseActionObject->m_dMaxForce < 0)    // 向后跳
    {
        float fdist=ft*m_pBaseActionObject->m_dAddSpeed;
        m_pBaseActionObject->m_dMaxForce-=fdist;
        if (m_pBaseActionObject->m_dMaxForce > 0) {
            m_pBaseActionObject->m_dMaxForce=0;
        }
        m_vSteeringForce=m_pBaseActionObject->m_vHeading*fdist;
    }
    return m_vSteeringForce;
}

//靠近目标
Vec2 SteeringBehaviors::seek(Vec2 TargetPos)
{
    Vec2 desiredVelocity=(TargetPos-m_pBaseActionObject->getPosition());
    desiredVelocity.normalize();
    desiredVelocity*=m_pBaseActionObject->MaxSpeed();
    return desiredVelocity-m_pBaseActionObject->getVelocity();
}


//
//  AttackObject.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/9.
//
//

#include "AttackObject.h"

AttackObject::~AttackObject()
{
    CC_SAFE_RELEASE_NULL(m_AttackObject);
}

AttackObject::AttackObject()
{
    m_AttackObject=nullptr;
    m_isSubBoold=false;
    m_isHitDown=false;
    m_attRange=Rect::ZERO;
    m_Attack=0;
    m_RepelPower=0.0f;
}

//克隆对象
AttackObject* AttackObject::clone()
{
    auto aClone=AttackObject::create();
    aClone->setAttackObject(m_AttackObject);
    aClone->setIsSubBoold(m_isSubBoold);
    aClone->setIsHitDown(m_isHitDown);
    aClone->setAttRange(m_attRange);
    aClone->setAttack(m_Attack);
    aClone->setRepelPower(m_RepelPower);
    return aClone;
}

void AttackObject::setAttRange(Rect rect)
{
    m_attRange=rect;
}

Rect AttackObject::getAttRange()
{
    return m_attRange;
}

//获取碰撞矩形
APOBB* AttackObject::getOBB()
{
    /*
    auto box=m_Bullet->getBoundingBox();
    auto pos=this->getPosition();
    auto m_BulletSize=box.size;
    auto rect=Rect(pos.x-m_BulletSize.width*0.5, pos.y-m_BulletSize.height*0.5, m_BulletSize.width, m_BulletSize.height);
    */
    auto rect=m_attRange;
    Vec2 pt = Vec2(rect.origin.x,rect.origin.y);
    m_obb->setVertex(0, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x+rect.size.width,rect.origin.y);
    m_obb->setVertex(1, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height);
    m_obb->setVertex(2, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x,rect.origin.y+rect.size.height);
    m_obb->setVertex(3, pt.x, pt.y);
    
    return m_obb;
}
//
//  BulletObject.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/17.
//
//

#include "BulletObject.h"

BulletObject::~BulletObject()
{
    
}

BulletObject::BulletObject()
{
    m_Bullet=nullptr;
    m_AttackType=0;
    m_PenetrateAttack=false;
    m_IsCollision=true;
    m_isDone=false;
    m_DoneCallback=nullptr;
}

//设置移动目标
void BulletObject::setTargetPos(Vec2 var, float speed)
{
    _previousPosition = _startPosition = getPosition();
    //求向量
    m_positionDelta=var-getPosition();
    //求距离
    float fDist=var.distance(getPosition());
    //数度 像素/秒
    float fSpeed=speed;
    //求时间
    totalTime=fDist/fSpeed;
    currTime=0.0;
}

//更新子弹逻辑
void BulletObject::update(float ft)
{
    if (m_isDone) {
        return;
    }
    currTime+=ft;
    float roteTime=currTime/totalTime;
    
    Vec2 currentPos = getPosition();
    Vec2 diff = currentPos - _previousPosition;
    _startPosition = _startPosition + diff;
    Vec2 newPos = _startPosition + (m_positionDelta * roteTime);
    setPosition(newPos);
    _previousPosition = newPos;
    
    if (roteTime>=1.0) {
        m_isDone=true;
        executeCallback();
    }
}

//设置子弹精灵
void BulletObject::setSprite(Sprite* spr)
{
    m_Bullet=spr;
    this->addChild(m_Bullet);
}

//获取英雄碰撞矩形
APOBB* BulletObject::getOBB()
{
    auto box=m_Bullet->getBoundingBox();
    auto pos=this->getPosition();
    auto m_BulletSize=box.size;
    auto rect=Rect(pos.x-m_BulletSize.width*0.5, pos.y-m_BulletSize.height*0.5, m_BulletSize.width, m_BulletSize.height);
    
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

//执行回调
void BulletObject::executeCallback()
{
    //回掉函数
    CCASSERT(m_DoneCallback, "callback not null");
    m_DoneCallback(this);
}

//是否攻击（已经攻击过的就不在攻击了，避免重复攻击）
bool BulletObject::isAttack(GameBaseObject* currObject)
{
    bool result=lastVector.contains(currObject);
    if (result) {
        return false;
    }else{
        lastVector.pushBack(currObject);
        return true;
    }
}
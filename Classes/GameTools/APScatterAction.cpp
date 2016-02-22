//
//  APScatterAction.cpp
//  Zombie3_4
//
//  Created by yuankang on 15/7/24.
//
//

#include "APScatterAction.h"

APScatterAction* APScatterAction::create(float _height, float _minX, float _maxX, float _rotate)
{
    APScatterAction *ret = new APScatterAction();
    ret->initWithDuration(_height, _minX, _maxX, _rotate);
    ret->autorelease();
    return ret;
}

bool APScatterAction::initWithDuration(float _height, float _minX, float _maxX, float _rotate)
{
    float xOffset = getRandFloat(_minX, _maxX);
    m_height = _height;
    //左右位移与抛出的高有关
    auto x = m_height-xOffset;
    if(getRandFloat(-m_height,m_height)<0){
        x = -m_height+xOffset;
    }
    m_width = x;
    //默认世界重力为0.9798（地球重力）
    m_gravity = 0.9798;
    //随机质量
    m_mass = getRandFloat(4.5f, 6.0f);
    //四舍五入取弹跳次数（弹力与高度，重力及质量有关）
    m_jumps = m_height/(m_mass*m_gravity*40)+0.5;
    //约动作时间
    m_duration = m_height/(m_gravity*285);
    //旋转
    m_rotation = _rotate==0.0 ? _rotate : m_width / 25 + _rotate;
    
    ActionInterval::initWithDuration(m_duration);
    
    return true;
}

void APScatterAction::update(float t)
{
    if (_target)
    {
        //根据动作分割的跳跃次数分配位移
        float frac = fmodf( t * m_jumps, 1.0f );
        float y = m_height * 4.5 * frac * (1 - frac);
        y += 0 * t;
        float x = m_width * t;
        //受质量及重力影响动能减小
        m_height-=m_mass*m_gravity;
        //动能越小受外力影响越大
        if (m_height<60) {
            m_height-=1;
            y-=1;
        }
        if (m_height<0) {
            m_height=0;
        }
        _target->setRotation(m_baseRotate+=m_rotation);
        Vec2 currentPos = _target->getPosition();
        Vec2 diff = currentPos - m_previousPos;
        m_startPosition = diff + m_startPosition;
        Vec2 newPos = m_startPosition + Vec2(x,y);
        _target->setPosition(newPos);
        m_previousPos = newPos;
    }
}

void APScatterAction::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    m_previousPos = m_startPosition = target->getPosition();
    m_groundY = target->getPositionY()-target->getContentSize().height/2;
}

APScatterAction *APScatterAction::clone() const
{
    APScatterAction *ret = APScatterAction::create(m_height, m_rotation);
    return ret;
}

//获取随机数
float APScatterAction::getRandFloat(float minNum, float maxNum)
{
    float fRand = CCRANDOM_0_1()*(maxNum-minNum)+minNum;
    return fRand;
}
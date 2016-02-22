//
//  DropObject.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/29.
//
//

#include "DropObject.h"

//获取英雄碰撞矩形
APOBB* DropObject::getOBB()
{
    float fWidht=30;
    float fHeight=30;
    Vec2 pos=this->getPosition();
    auto rect=Rect(pos.x-fWidht*0.5, pos.y-fHeight*0.5, fWidht, fHeight);
    
    Vec2 pt = Vec2(rect.origin.x,rect.origin.y);
    m_obb->setVertex(0, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x+rect.size.width,rect.origin.y);
    m_obb->setVertex(1, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height);
    m_obb->setVertex(2, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x,rect.origin.y+rect.size.height);
    m_obb->setVertex(3, pt.x, pt.y);
    //获取obb
    return m_obb;
}

//获取掉落类型
DropObject::DropType DropObject::getType()
{
    return DropType::None;
}

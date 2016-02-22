//
//  EnemyBow.cpp
//  Zombie3_4
//  弓箭手－发射子弹
//  Created by liuye on 15/8/27.
//
//

#include "EnemyBow.h"
#include "GameBLL.h"
#include "EnemyModel.h"
#include "BulletObject.h"
#include "BulletBLL.h"

EnemyBow::~EnemyBow()
{
    
}

EnemyBow::EnemyBow()
{
    
}

//敌兵数据
void EnemyBow::loadData(EnemyModel* arg1)
{
    EnemyBase::loadData(arg1);
}

AttackObject* EnemyBow::createAttackObject()
{
    auto model=getEnemyModel();
    float attackDist=model->AttackDist;                                 //攻击距离
    Vec2 startOffsetPos=PointFromString(model->BulletStartOffset);      //添加子弹开始坐标偏移量(例如弓箭子弹偏上)
    Vec2 endOffsetPos=PointFromString(model->BulletEndOffset);          //添加子弹结束坐标偏移量(例如法师子弹向下攻击)
    bool facing=getFacing();                                            //获取方向
    if(!facing){
        attackDist*=-1;
    }
    //创建子弹
    auto bullet=BulletObject::create();
    bullet->setAttackType(2);
    bullet->setAttackObject(this);
    auto bulletSprite=Sprite::createWithSpriteFrameName(model->BulletName);
    bulletSprite->setFlippedX(!facing);
    bullet->setSprite(bulletSprite);
    bullet->setPosition(getPosition()+startOffsetPos);
    bullet->setTargetPos(getPosition()+Vec2(attackDist,startOffsetPos.y)+endOffsetPos);
    BulletBLL::getInstance()->addBullet(bullet);

    if (model->IsBulletRate==1) {
        auto seq=Sequence::create(RotateBy::create(0.3, -360), NULL);
        bullet->runAction(seq);
    }
    
    return nullptr;
}

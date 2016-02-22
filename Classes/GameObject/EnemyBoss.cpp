//
//  EnemyBoss.cpp
//  Zombie3_4
//  敌兵Boss
//  Created by liuye on 15/8/27.
//
//

#include "EnemyBoss.h"
#include "GameBLL.h"
#include "EnemyModel.h"
#include "BulletObject.h"

EnemyBoss::~EnemyBoss()
{
    
}

EnemyBoss::EnemyBoss()
{
    
}

//敌兵数据
void EnemyBoss::loadData(EnemyModel* arg1)
{
    EnemyBase::loadData(arg1);
}

AttackObject* EnemyBoss::createAttackObject()
{
    auto model=getEnemyModel();
    
    float attackDist=model->AttackDist;         //攻击距离
    bool facing=getFacing();                    //获取方向

    //创建攻击对象
    auto att=AttackObject::create();
    att->setAttackObject(this);
    Vec2 pos=this->getPosition();
    float attStartPosX=getPositionX();
    if (!facing) {
        attStartPosX-=attackDist;
    }
    
    Rect attRect=Rect(attStartPosX,getPositionY(),attackDist, 100);
    att->setAttRange(attRect);
    
    return att;
}

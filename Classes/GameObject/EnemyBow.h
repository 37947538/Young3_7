//
//  EnemyBow.h
//  Zombie3_4
//  弓箭手－发射子弹
//  Created by liuye on 15/8/27.
//
//

#ifndef __Zombie3_4__EnemyBow__
#define __Zombie3_4__EnemyBow__

#include <stdio.h>
#include "EnemyBase.h"

class EnemyBow : public EnemyBase
{
public:
    ~EnemyBow();
    EnemyBow();
    virtual void loadData(EnemyModel* arg1);                        //敌兵数据
    virtual AttackObject* createAttackObject();                     //创建攻击对象
};

#endif /* defined(__Zombie3_4__EnemyBow__) */

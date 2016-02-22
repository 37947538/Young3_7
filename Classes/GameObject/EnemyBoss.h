//
//  EnemyBoss.h
//  Zombie3_4
//  敌兵Boss
//  Created by liuye on 15/8/27.
//
//

#ifndef __Zombie3_4__EnemyBoss__
#define __Zombie3_4__EnemyBoss__

#include <stdio.h>
#include "EnemyBase.h"

class EnemyBoss : public EnemyBase
{
public:
    ~EnemyBoss();
    EnemyBoss();
    virtual void loadData(EnemyModel* arg1);                        //敌兵数据
    virtual AttackObject* createAttackObject();                     //创建攻击对象
};

#endif /* defined(__Zombie3_4__EnemyBoss__) */

//
//  EnemyCannon.h
//  Zombie3_4
//  炮兵－抛物线发射子弹
//  Created by liuye on 15/8/27.
//
//

#ifndef __Zombie3_4__EnemyCannon__
#define __Zombie3_4__EnemyCannon__

#include <stdio.h>
#include "EnemyBase.h"

class EnemyCannon : public EnemyBase
{
public:
    ~EnemyCannon();
    EnemyCannon();
    virtual void loadData(EnemyModel* arg1);                        //敌兵数据
    virtual AttackObject* createAttackObject();                     //创建攻击对象
    virtual BTNodeInputData* readBevNodeInputData();                //获取怪的状态数据
protected:
    void bulletExplode(const Vec2& pos);
};

#endif /* defined(__Zombie3_4__EnemyCannon__) */

//
//  EnemyConditionFactory.h
//  Zombie3_4
//  敌兵条件工厂
//  Created by jl on 15/8/9.
//
//

#ifndef __Zombie3_4__EnemyConditionFactory__
#define __Zombie3_4__EnemyConditionFactory__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"
#include "EnemyPreconditionHasPassive.h"
#include "EnemyPreconditionHasBeAttack.h"
#include "EnemyPrecondition.h"
#include "APBevTreePreconditionNot.h"
#include "EnemyBevTreeNode.h"

class EnemyConditionFactory
{
public:
    
    //是否被击倒
    static APBevTreePrecondition* createHasBeDown(APBevTreeNode* parent)
    {
        auto bDown=new EnemyPreconditionBeDown();
        parent->setNodePrecondition(bDown);
        return bDown;
    }
    
    
    //是否被击状态
    static APBevTreePrecondition* createHasPassive(APBevTreeNode* parent,bool isOpposite=false)
    {
        if(!isOpposite)
        {
            auto bIsPassiveNode=new EnemyPreconditionHasPassive();
            parent->setNodePrecondition(bIsPassiveNode);
            return bIsPassiveNode;
        }else
        {
            auto bIsPassiveNode=new EnemyPreconditionHasPassive();
            APBevTreePreconditionNot *notNode=new APBevTreePreconditionNot(bIsPassiveNode);
            parent->setNodePrecondition(notNode);
            return bIsPassiveNode;
        }
        return nullptr;
    }
    
    //是否被打
    static APBevTreePrecondition* createHasBeAttack(APBevTreeNode* parent)
    {
        auto bTrueBeAttack=new APBevTreePreconditionNot(new EnemyPreconditionHasBeAttack());
        parent->setNodePrecondition(bTrueBeAttack);
        return bTrueBeAttack;
    }
    
    //追逐目标
    static APBevTreePrecondition* createHasTarget(APBevTreeNode* parent)
    {
        auto bNot=new EnemyPreconditionHasTarget();
        parent->setNodePrecondition(bNot);
        return bNot;
    }
    
    //永真条件
    static APBevTreePrecondition* createHasTrue(APBevTreeNode* parent)
    {
        auto bTrue=new APBevTreePreconditionTrue();
        parent->setNodePrecondition(bTrue);
        return bTrue;
    }
    
    //是否死亡
    static APBevTreePrecondition* createHasDie(APBevTreeNode* parent)
    {
        auto bTrue=new EnemyPreconditionHasDie();
        parent->setNodePrecondition(bTrue);
        return bTrue;
    }
    
    //怪攻击英雄条件
    static APBevTreePrecondition* createEnemyAttHero(APBevTreeNode* parent)
    {
        auto bTrue=new EnemyPreconditionEnemyAttHero();
        parent->setNodePrecondition(bTrue);
        return bTrue;
    }
    
    
    
};
#endif /* defined(__Zombie3_4__EnemyConditionFactory__) */

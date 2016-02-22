//
//  HeroBevFactory.h
//  Zombie3_4
//  英雄行为树工厂类
//  Created by jl on 15/8/19.
//
//

#ifndef __Zombie3_4__HeroBevFactory__
#define __Zombie3_4__HeroBevFactory__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "HeroPrecondition.h"


class HeroBevFactory
{
public:
    //是否英雄控制状态
    static APBevTreePrecondition* createHasPlayerControl(APBevTreeNode* parent,bool isOpposite=false)
    {
        if(!isOpposite)
        {
            auto bIsPassiveNode=new HeroPreconditionPlayerControll();
            parent->setNodePrecondition(bIsPassiveNode);
            return bIsPassiveNode;
        }else
        {
            auto bIsPassiveNode=new HeroPreconditionPlayerControll();
            APBevTreePreconditionNot *notNode=new APBevTreePreconditionNot(bIsPassiveNode);
            parent->setNodePrecondition(notNode);
            return bIsPassiveNode;
        }
        return nullptr;
    }
    
    //是否英雄控制状态
    static APBevTreePrecondition* createHasControlMove(APBevTreeNode* parent)
    {
        auto bMove=new HeroPreconditionControllMove();
        parent->setNodePrecondition(bMove);
        return bMove;
    }
    
    //是否英雄控制攻击
    static APBevTreePrecondition* createHasControlAtt(APBevTreeNode* parent)
    {
        auto bAtt=new HeroPreconditionControllAtt();
        parent->setNodePrecondition(bAtt);
        return bAtt;
    }
    //是否英雄控制攻击
    static APBevTreePrecondition* createHasControlSkill(APBevTreeNode* parent)
    {
        auto bSk=new HeroPreconditionControllSkill();
        parent->setNodePrecondition(bSk);
        return bSk;
    }
    //是否英雄控制NPC攻击中
    static APBevTreePrecondition* createHasNpcAttacking(APBevTreeNode* parent)
    {
        auto bNpcAttacking=new HeroPreconditionNpcAttacking();
        parent->setNodePrecondition(bNpcAttacking);
        return bNpcAttacking;
    }
    //NPC是否可以攻击怪物
    static APBevTreePrecondition* createHasNpcAttackMonster(APBevTreeNode* parent)
    {
        auto bNpcAttacking=new HeroPreconditionNpcAttackMonster();
        parent->setNodePrecondition(bNpcAttacking);
        return bNpcAttacking;
    }
    
    //NPC是否跟踪主英雄位置
    static APBevTreePrecondition* createHasNpcFollow(APBevTreeNode* parent)
    {
        auto bNpcAttacking=new HeroPreconditionNpcFollow();
        parent->setNodePrecondition(bNpcAttacking);
        return bNpcAttacking;
    }
    
    //英雄是否被打
    static APBevTreePrecondition* createHasBeAttack(APBevTreeNode* parent)
    {
        auto bAttack=new HeroPreconditionHasBeAttack();
        parent->setNodePrecondition(bAttack);
        return bAttack;
    }
    
};
#endif /* defined(__Zombie3_4__HeroBevFactory__) */

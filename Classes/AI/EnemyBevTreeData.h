//
//  EnemyBevTreeData.h
//  Zombie3_4
//
//  Created by jl on 15/6/26.
//
//

#ifndef __Zombie3_4__EnemyBevTreeData__
#define __Zombie3_4__EnemyBevTreeData__

#include <stdio.h>
#include <queue>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"
#include "EnemyBase.h"
#include "HeroBase.h"
#include "AttackObject.h"
#include "EnemyEventObject.h"

struct EnemyBevInputData
{
    float	m_TimeStep;                             //时长
    Vec2	m_TargetPosition2D;                     //目标位置英雄位置
    EnemyBase*	m_Owner;                            //敌兵自己
    Vec2	m_CurrentFacing;                        //当前朝向
    Vec2	m_CurrentPosition;                      //当前位置
    GameEnum::EnemyState m_InState;                 //敌兵输入状态
    Vector<AttackObject*>   attackList;             //攻击列表,有数据时触发攻击节点
    int m_iAttackDist;                              //攻击距离
};

struct EnemyBevOutputData
{
    Color3B   m_BodyColor;
    float     m_BodySize;
    Vec2	m_NextPosition;
    Vec2	m_NextFacing;                           //敌兵的方向
    GameEnum::EnemyState m_outState;                //敌兵输出状态
    Vector<EnemyEventObject*> m_OutEvent;           //敌兵事件
};

#endif /* defined(__Zombie3_4__EnemyBevTreeData__) */

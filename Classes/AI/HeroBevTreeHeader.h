//
//  HeroBevTreeHeader.h
//  Zombie3_4
//
//  Created by jl on 15/8/18.
//
//

#ifndef __Zombie3_4__HeroBevTreeHeader__
#define __Zombie3_4__HeroBevTreeHeader__

#include <stdio.h>

#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"
#include "EnemyBase.h"
#include "HeroBase.h"
#include "AttackObject.h"
#include "HeroEventObject.h"
#include "IUIControl.h"


struct HeroBevTreeInputData
{
    float	m_TimeStep;                             //时长
    IUIControl *m_PlayerControl=nullptr;            //玩家UI控制
    Vec2	m_MainHeroPosition;                     //主英雄位置
    Vec2	m_HeroPosition2D;                       //目标位置英雄位置
    Vec2	m_TargetPosition2D;                     //目标位置英雄位置
    HeroBase*	m_Owner;                            //英雄自己
    Vec2	m_CurrentFacing;                        //当前朝向
    Vec2	m_CurrentPosition;                      //当前位置
    GameEnum::EnemyState m_InState;                 //敌兵输入状态
    Vector<EnemyBase*> *m_EnemyList;                //敌兵列表
    Vector<AttackObject*>   attackList;             //攻击列表,有数据时触发攻击节点
    int m_iAttackDist;                              //攻击距离
};

struct HeroBevTreeOutputData
{
    Vec2    m_vVelocity;                            //英雄移动位置
    Vec2	m_NextPosition;
    Vec2	m_NextFacing;                           //英雄的方向
    Vector<HeroEventObject*> m_OutEvent;            //英雄事件
};

#endif /* defined(__Zombie3_4__HeroBevTreeHeader__) */

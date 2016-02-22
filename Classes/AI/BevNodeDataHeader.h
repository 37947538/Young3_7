//
//  BevNodeDataHeader.h
//  Zombie3_4
//  行为树节点头文件
//  Created by jl on 15/8/24.
//
//

#ifndef Zombie3_4_BevNodeDataHeader_h
#define Zombie3_4_BevNodeDataHeader_h

#include "AttackObject.h"
#include "GameEnum.h"
#include "IUIControl.h"

class BaseActionObject;

class BaseActionEvent : public Ref
{
public:
    ~BaseActionEvent(){ CC_SAFE_RELEASE_NULL(m_EventArg); };
    BaseActionEvent():m_EventArg(nullptr),m_BaseActionEvent(GameEnum::BaseActionEventType::EventNone){};
    CREATE_FUNC(BaseActionEvent);
    virtual bool init() { return true; };
    CC_SYNTHESIZE_RETAIN(Ref*, m_EventArg, EventArg);                        //参数
    CC_SYNTHESIZE(GameEnum::BodyState, m_EventBodyState, EventBodyState);              //状态
    CC_SYNTHESIZE(GameEnum::BaseActionEventType, m_BaseActionEvent, BaseActionEvent);  //事件
};

struct BTNodeInputData
{
    float	m_TimeStep;                             //时长
    Vec2	m_CurrPosition2D;                       //目标位置英雄位置
    Vec2	m_TargetPosition2D;                     //目标位置
    Vec2	m_MainHeroPosition2D;                   //主英雄位置
    BaseActionObject*	m_Owner;                    //对象自己
    GameEnum::BodyState m_OwnerState;               //主体状体
    Vec2	m_CurrentFacing;                        //当前朝向
    float m_RunMoveSpeed;                           //移动速度
    GameEnum::EnemyState m_InState;                 //敌兵输入状态
    int m_iAttackDist;                              //攻击距离
    int m_iAttackDistMin;                           //最小攻击距离
    bool m_IsMainHero=false;                        //是否是主英雄
    IUIControl *m_PlayerControl=nullptr;            //玩家UI控制
    float m_BeAttackFlyPower=0.0f;                  //被击飞的力量
    bool m_IsSkillMove=false;                       //释放技能时是否可以移动
    float m_MapMoveWidth=0.0f;                      //地图移动宽度
};

struct BTNodeOutputData
{
    Vec2    m_vVelocity;                            //主体速度
    Vec2    m_NextPosition;                         //下一个位置
    Vec2    m_NextFacing;                           //方向
    Vector<BaseActionEvent*> m_OutEvent;            //输出事件
};

#endif

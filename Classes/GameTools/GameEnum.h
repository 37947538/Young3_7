//
//  GameEnum.h
//  Zombie3_4
//  游戏枚举类型
//  Created by jl on 15/6/5.
//
//

#ifndef __Zombie3_4__GameEnum__
#define __Zombie3_4__GameEnum__

#include <stdio.h>

class GameEnum
{
public:
    enum class BodyState{   //基础动作状态
        None=-1,
        Finish,             //结束
        BeAttack,           //被攻击
        Down,               //被击倒
        Idle,               //空闲
        Die,                //死亡
        Stand,              //站立
        Run,                //跑
        Attack,             //攻击
        Skill,              //释放技能
    };
    
    enum class HeroState{   //英雄状态
        None=-1,
        Stand=0,
        Walk,
        Run,
        Attack1,
        Attack2,
        Attack3,
    };
    
    enum class EnemyState{   //敌兵状态
        None=-1,
        Finish,             //结束
        BeAttack,           //被攻击
        BeAttackDown,       //被击倒
        BeAttacking,        //被打中
        Idle,               //空闲
        Die,                //死亡
        Stand,
        Walk,
        Run,
        Attack1,
        Attack2,
        Attack3,
    };
    
    enum class EnemyEvent{              //敌兵参数事件
        EnemyEventNone=-1,              //空事件
        EventPlayAnimate,               //播放动画
        EventBeAttack,                  //被攻击
        EventBeAttackFinish,            //被打完成
        EventChangeStateIdle,           //切换待机状态
        EventChangeShaderBeAttackShader,//切换特效被击打状态
        EventDie,                       //死亡
        EventEnemyFinish,               //死亡收尾工作，清理内存
    };
    
    enum class BaseActionEventType{     //参数事件
        EventNone=-1,              //空事件
        PlayAnimate,               //播放动画
        BeAttack,                  //被攻击
        ChangeStateIdle,           //切换待机状态
        ChangeShaderBeAttackShader,//切换特效被击打状态
    };
};

#endif /* defined(__Zombie3_4__GameEnum__) */

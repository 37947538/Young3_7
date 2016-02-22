//
//  EnemyBevTreeNodeIdle.cpp
//  Zombie3_4
//
//  Created by jl on 15/6/29.
//
//

#include "EnemyBevTreeNodeIdle.h"
#include "EnemyBevTreeData.h"
#include "EnemyModel.h"
#include "EnemyBase.h"

//游戏进入
void EnemyBevTreeNodeIdle::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    auto enemy=inputData.m_Owner;
    auto actionModel=enemy->getActionFileMode();
    //播放动画名称
    animateName=actionModel->ActionIdle;
    //默认待机时间
    m_WaitingTime=1.0;
}

//怪攻击英雄
BevRunningStatus EnemyBevTreeNodeIdle::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
     float timeStep = inputData.m_TimeStep;
     m_WaitingTime -= timeStep;

    //判断是否动画播放完成
    auto state= inputData.m_Owner->getAnimateState(animateName);
    if (state!=BaseActionObject::AnimateState::Runing) {
        auto event= BaseActionEvent::create();
        event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
        event->setEventArg(__String::create(animateName));
        event->setEventBodyState(GameEnum::BodyState::Idle);
        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }
    
    if(m_WaitingTime < 0)
    {
        return k_BRS_Finish;
    }
    
    return k_BRS_Executing;
}

#pragma mark - 攻击前待机数
//游戏进入
void EnemyBevTreeNodeIdleAttackBefore::doEnter(const BevNodeInputParam& input)
{
    EnemyBevTreeNodeIdle::doEnter(input);
    //待机时间
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    auto enemy=(EnemyBase*)inputData.m_Owner;
    auto model=enemy->getEnemyModel();
    auto time=PointFromString(model->AttackBeforeTime);
    //默认待机时间
    float waitingTime=APTools::getRandFloat(time.x, time.y);
    setWaitingTime(waitingTime);
}

#pragma mark - 攻击后待机数
//游戏进入
void EnemyBevTreeNodeIdleAttackAfter::doEnter(const BevNodeInputParam& input)
{
    EnemyBevTreeNodeIdle::doEnter(input);
    //怪空闲
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    auto enemy=(EnemyBase*)inputData.m_Owner;
    auto model=enemy->getEnemyModel();
    auto time=PointFromString(model->AttackAfterTime);
    //默认待机时间
    float waitingTime=APTools::getRandFloat(time.x, time.y);
    setWaitingTime(waitingTime);
}

#pragma mark - 追逐待机数
//游戏进入
void EnemyBevTreeNodeIdleCatch::doEnter(const BevNodeInputParam& input)
{
    EnemyBevTreeNodeIdle::doEnter(input);
    //怪空闲
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    auto enemy=(EnemyBase*)inputData.m_Owner;
    auto model=enemy->getEnemyModel();
    auto time=PointFromString(model->CatchTime);
    //默认待机时间
    float waitingTime=APTools::getRandFloat(time.x, time.y);
    setWaitingTime(waitingTime);
}

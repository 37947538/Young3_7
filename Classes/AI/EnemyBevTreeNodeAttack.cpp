//
//  EnemyBevTreeNodeAttack.cpp
//  Zombie3_4
//
//  Created by jl on 15/6/26.
//
//

#include "EnemyBevTreeNodeAttack.h"
#include "EnemyBevTreeData.h"

//游戏进入
void EnemyBevTreeNodeAttack::doEnter(const BevNodeInputParam& input)
{
     //const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
     //m_WaitingTime=2.0;
     //m_EnemyRunState=true;
    m_isPlayAnimate=true;
}

//怪攻击英雄
BevRunningStatus EnemyBevTreeNodeAttack::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    EnemyBevOutputData& outputData = output.getRealDataType<EnemyBevOutputData>();
    
    if (m_isPlayAnimate) {
        m_isPlayAnimate=false;
        //播放动画名称
        animateName=inputData.m_Owner->getActionFileMode()->ActionAttackName1;
        auto event= EnemyEventObject::create();
        event->setEnemyEvent(GameEnum::EnemyEvent::EventPlayAnimate);
        event->setEventArg(__String::create(animateName));
        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }
    
    //判断是否动画播放完成
    auto state= inputData.m_Owner->getAnimateState(animateName);
    if (state==BaseActionObject::AnimateState::Finish) {
        return k_BRS_Finish;
    }
    

    return k_BRS_Executing;
}

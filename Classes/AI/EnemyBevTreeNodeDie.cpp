//
//  EnemyBevTreeNodeDie.cpp
//  Zombie3_4
//
//  Created by liuye on 15/8/10.
//
//

#include "EnemyBevTreeNodeDie.h"
#include "EnemyBevTreeData.h"

//游戏进入
void EnemyBevTreeNodeDie::doEnter(const BevNodeInputParam& input)
{
    m_isPlayAnimate=true;
    animateName="";
}

//怪物死亡
BevRunningStatus EnemyBevTreeNodeDie::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    EnemyBevOutputData& outputData = output.getRealDataType<EnemyBevOutputData>();
    
    if (m_isPlayAnimate) {
        m_isPlayAnimate=false;
        //播放动画名称
        animateName=inputData.m_Owner->getActionFileMode()->ActionDie;
        auto event= EnemyEventObject::create();
        event->setEnemyEvent(GameEnum::EnemyEvent::EventPlayAnimate);
        event->setEventArg(__String::create(animateName));
        outputData.m_OutEvent.pushBack(event);
        
        auto eventDie= EnemyEventObject::create();
        eventDie->setEnemyEvent(GameEnum::EnemyEvent::EventDie);
        outputData.m_OutEvent.pushBack(eventDie);
        return k_BRS_Executing;
    }
    
    //判断是否动画播放完成
    auto state= inputData.m_Owner->getAnimateState(animateName);
    if (state==BaseActionObject::AnimateState::Finish) {
        auto event= EnemyEventObject::create();
        event->setEnemyEvent(GameEnum::EnemyEvent::EventEnemyFinish);
        outputData.m_OutEvent.pushBack(event);
        
        return k_BRS_Finish;
    }
    
    return k_BRS_Executing;
}
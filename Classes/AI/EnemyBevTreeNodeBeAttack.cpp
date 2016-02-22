//
//  EnemyBevTreeNodeBeAttack.cpp
//  Zombie3_4
//
//  Created by jl on 15/6/29.
//
//

#include "EnemyBevTreeNodeBeAttack.h"
#include "EnemyBevTreeData.h"
#include "AttackObject.h"

//游戏进入
void EnemyBevTreeNodeBeAttack::doEnter(const BevNodeInputParam& input)
{
    //怪被攻击
    //animateName="";
    iAttDist=0;    //攻击距离
}

//怪攻击英雄
BevRunningStatus EnemyBevTreeNodeBeAttack::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    EnemyBevOutputData& outputData = output.getRealDataType<EnemyBevOutputData>();
    
    //是否有攻击
    for (int i=0 ; i < inputData.attackList.size(); i++) {
        auto att=inputData.attackList.at(i);
        auto enemyModel=inputData.m_Owner->getActionFileMode();
        //如果是击倒
        if (att->getIsHitDown()) {
             animateName=enemyModel->ActionBeAttackDown;
        }else if(enemyModel->ActionBeAttackDown==animateName)    //如果上次是击倒，本次还是被击倒
        {
             animateName=enemyModel->ActionBeAttackDown;
        }else                                                   //否则随机播放被打动画
        {
             animateName=inputData.m_Owner->getActionFileMode()->ActionBeAttack1;
        
             if (CCRANDOM_0_1() > 0.5) {
                 animateName=inputData.m_Owner->getActionFileMode()->ActionBeAttack2;
              }
        }
        
        //animateName=inputData.m_Owner->getActionFileMode()->ActionBeAttackDown;

        auto event= EnemyEventObject::create();
        event->setEnemyEvent(GameEnum::EnemyEvent::EventPlayAnimate);
        event->setEventArg(__String::create(animateName));
        outputData.m_OutEvent.pushBack(event);
        
        //扣血值
        auto eventSubblood= EnemyEventObject::create();
        eventSubblood->setEnemyEvent(GameEnum::EnemyEvent::EventBeAttack);
        eventSubblood->setEventArg(att->getAttackObject());
        outputData.m_OutEvent.pushBack(eventSubblood);
        
        //shader
        auto eventShader= EnemyEventObject::create();
        eventShader->setEnemyEvent(GameEnum::EnemyEvent::EventChangeShaderBeAttackShader);
        outputData.m_OutEvent.pushBack(eventShader);
                    
        iAttDist=10;
    }
    //发送清理攻击数据消息
    if (inputData.attackList.size() > 0) {
        auto eventShader= EnemyEventObject::create();
        eventShader->setEnemyEvent(GameEnum::EnemyEvent::EventBeAttackFinish);
        outputData.m_OutEvent.pushBack(eventShader);;
    }
   
    //计算被攻击位移
    iAttDist-=1;
    iAttDist= iAttDist < 0 ? 0 : iAttDist;
    outputData.m_NextPosition=inputData.m_CurrentPosition-inputData.m_CurrentFacing*iAttDist;
    return k_BRS_Executing;
}
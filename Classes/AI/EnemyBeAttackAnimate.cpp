//
//  EnemyBeAttackAnimate.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/7.
//
//

#include "EnemyBeAttackAnimate.h"
#include "EnemyBevTreeData.h"


//游戏进入
void EnemyBeAttackAnimate::doEnter(const BevNodeInputParam& input)
{
    //怪空闲
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    inputData.m_Owner->idleAnimate();
    /*
     const EnemyBevInputData& inputData = input.GetRealDataType<EnemyBevInputData>();
     m_WaitingTime=5.0;
     */
    //m_EnemyRunState=true;
}

//怪攻击英雄
BevRunningStatus EnemyBeAttackAnimate::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    /*
     const EnemyBevInputData& inputData = input.GetRealDataType<EnemyBevInputData>();
     EnemyBevOutputData& outputData = output.GetRealDataType<EnemyBevOutputData>();
     
     float timeStep = inputData.m_TimeStep;
     m_WaitingTime -= timeStep;
     //攻击动作
     outputData.m_outState=GameEnum::EnemyState::Attack;
     if(m_WaitingTime < 0)
     {
     return k_BRS_Finish;
     }
*/
    return k_BRS_Executing;
}


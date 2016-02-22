//
//  EnemyBevTreeNodeInverseMove.cpp
//  Zombie3_4
//
//  Created by jl on 15/6/29.
//
//

#include "EnemyBevTreeNodeInverseMove.h"
#include "EnemyBevTreeData.h"

//游戏进入
void EnemyBevTreeNodeInverseMove::doEnter(const BevNodeInputParam& input)
{
    //怪被攻击
    //const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    //inputData.m_Owner->beAttackAnimate();
    
}

//怪攻击英雄
BevRunningStatus EnemyBevTreeNodeInverseMove::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    
    /*
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    EnemyBevOutputData& outputData = output.getRealDataType<EnemyBevOutputData>();
    
    float timeStep = inputData.m_TimeStep;
    m_WaitingTime -= timeStep;
    
    
    Armature* enemyArm= inputData.m_Owner->getArmature();
    auto actionFileMode=inputData.m_Owner->getActionFileMode();
    if (enemyArm->getAnimation()->getCurrentMovementID()==actionFileMode->ActionBeAttack1) {
        if(enemyArm->getAnimation()->getCurrentPercent()==1.0)
        {
            return k_BRS_Finish;
        }
    }
    
    //攻击动作
    outputData.m_outState=GameEnum::EnemyState::BeAttacking;
    if(m_WaitingTime < 0)
    {
        //return k_BRS_Finish;
    }
    */
    //outputData.m_outState=GameEnum::EnemyState::BeAttacking;
    return k_BRS_Executing;
}

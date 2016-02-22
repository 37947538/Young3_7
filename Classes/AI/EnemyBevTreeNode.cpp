//
//  EnemyBevTreeNode.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/21.
//
//

#include "EnemyBevTreeNode.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"
#include "EnemyBevTreeData.h"
#include "EnemyModel.h"


//怪攻被击倒
bool EnemyPreconditionBeDown::externalCondition(const BevNodeInputParam& input) const
{
    const EnemyBevInputData&  inputData	= input.getRealDataType<EnemyBevInputData>();
    
    std::string strAttDown=inputData.m_Owner->getActionFileMode()->ActionBeAttackDown;
    if(inputData.m_Owner->getAnimateState(strAttDown)==BaseActionObject::AnimateState::Runing)
    {
        return true;
    }
    
    return false;
}

//怪攻被击倒
void EnemyBevTreeNodeBeDown::doEnter(const BevNodeInputParam& input)
{
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    //怪被攻击
    animateName=inputData.m_Owner->getActionFileMode()->ActionBeAttackDown;
    iAttDist=0;    //攻击距离
}

//怪攻被击倒
BevRunningStatus EnemyBevTreeNodeBeDown::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    //EnemyBevOutputData& outputData = output.getRealDataType<EnemyBevOutputData>();
    
    if(inputData.m_Owner->getAnimateState(animateName)==BaseActionObject::AnimateState::Finish)
    {
        return BevRunningStatus::k_BRS_Finish;
    }
    
    return BevRunningStatus::k_BRS_Executing;
}
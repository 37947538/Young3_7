//
//  EnemyBevTreeNodeFace.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/13.
//
//

#include "EnemyBevTreeNodeFace.h"
#include "EnemyBevTreeData.h"
#include "EnemyModel.h"


//游戏进入
void EnemyBevTreeNodeFace::doEnter(const BevNodeInputParam& input)
{
    //怪空闲
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    //播放动画名称
    //animateName=inputData.m_Owner->getActionFileMode()->ActionIdle;
    //默认待机时间
    //m_WaitingTime=1.0;
}

//怪攻击英雄
BevRunningStatus EnemyBevTreeNodeFace::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    EnemyBevOutputData& outputData = output.getRealDataType<EnemyBevOutputData>();
    
    float timeStep = inputData.m_TimeStep;
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    
    Vec2 curPosition2D=inputData.m_Owner->getPosition();
    Vec2 dir = targetPoint2D - curPosition2D;
    
    if (dir.x > 0) {
        outputData.m_NextFacing=Vec2(1,0);
    }else
    {
        outputData.m_NextFacing=Vec2(-1,0);
    }

    
    
    return k_BRS_Finish;
}


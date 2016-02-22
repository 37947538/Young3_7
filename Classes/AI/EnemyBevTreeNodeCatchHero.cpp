//
//  EnemyBevTreeNodeCatchHero.cpp
//  Zombie3_4
//
//  Created by jl on 15/6/26.
//
//

#include "EnemyBevTreeNodeCatchHero.h"
#include "EnemyBevTreeData.h"

#pragma mark - 执行行为 怪追英雄

//游戏进入
void EnemyBevTreeNodeCatchHero::doEnter(const BevNodeInputParam& input)
{
    //怪空闲
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    //inputData.m_Owner->runAnimate();
}


//怪追英雄
BevRunningStatus EnemyBevTreeNodeCatchHero::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    
    const EnemyBevInputData& inputData = input.getRealDataType<EnemyBevInputData>();
    EnemyBevOutputData& outputData = output.getRealDataType<EnemyBevOutputData>();
    
    float timeStep = inputData.m_TimeStep;
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    
    Vec2 curPosition2D=inputData.m_Owner->getPosition();
    Vec2 dir = targetPoint2D - curPosition2D;
    
    //EnemyBase* eBase=(EnemyBase*)inputData.m_Owner;
    //EnemyModel* emodel=eBase->getEnemyModel();
    
    if(fabsf(dir.x)  < 150.f)
    {
        return k_BRS_Finish;
    }
    else
    {
        if (dir.x > 0) {
            outputData.m_NextFacing=Vec2(1,0);
        }else
        {
            outputData.m_NextFacing=Vec2(-1,0);
        }
        outputData.m_outState=GameEnum::EnemyState::Run;
        dir.normalize();
        Vec2 nextPos2D = curPosition2D + dir * timeStep * 100;
        outputData.m_NextPosition = Vec2(nextPos2D.x, nextPos2D.y);
        
    }
    
    return k_BRS_Executing;
}

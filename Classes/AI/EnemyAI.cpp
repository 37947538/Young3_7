//
//  EnemyAI.cpp
//  HeroTower3_4
//
//  Created by jl on 15/5/11.
//
//

#include "EnemyAI.h"
#include "GameBLL.h"
#include "HeroBase.h"
#include "BaseActionObject.h"
#include "EnemyBase.h"
#include "EnemyBevTreeNodeAttack.h"
#include "EnemyBevTreeNodeCatchHero.h"
#include "APBevTreeHeader.h"
#include "EnemyBevTreeNodeBeAttack.h"
#include "EnemyBevTreeNodeInverseMove.h"
#include "EnemyBevTreeNodeIdle.h"
#include "EnemyBevTreeNodePassive.h"
#include "EnemyBevTreeNodeWaitAttack.h"
#include "EnemyBevTreeNodeAttack.h"
#include "EnemyConditionFactory.h"
#include "EnemyBevTreeData.h"
#include "EnemyBevTreeNodeDie.h"
#include "EnemyModel.h"
#include "EnemyBevTreeNodeFace.h"
#include "EnemyBevTreeNode.h"
#include "BTCondition.h"
#include "BTNode.h"
#include "APBevTreePreconditionOR.h"

EnemyAI::~EnemyAI()
{
    CC_SAFE_DELETE(m_BevTreeRoot);
}

EnemyAI::EnemyAI(EnemyBase *parent)
{
    m_Parent=parent;
    
    APBevTreeNodePrioritySelector* pRoot = new APBevTreeNodePrioritySelector(nullptr);
    m_BevTreeRoot=pRoot;
    m_BevTreeRoot->setDebugName("根节点");
}

//创建行为树
void EnemyAI::createBevTree()
{
    //Root-被动节点
    auto passiveNode =APBevTreeNodeFactory::createPrioritySelectorNode(m_BevTreeRoot, "被动行为(优先选择)");
    BTConditionIsBeAttack::create(passiveNode);
    {
        //Root-主动行为节点-准备攻击-翻面
        //APBevTreeNodeFactory::createTeminalNode<BevTreeNodeFace>(passiveNode, "面对攻击者");
        
        //Root-被动节点-被打节点(被攻击条件)
        APBevTreeNodeFactory::createTeminalNode<BevTreeNodeEnemyBeAttack>(passiveNode, "被打(叶子)");
    }
    
    //Root-主动行为节点
    auto mainActionNode =APBevTreeNodeFactory::createPrioritySelectorNode(m_BevTreeRoot, "主动行为");
    auto isBeattackCondition=new BTConditionIsBeAttack();
    auto notCondition=new APBevTreePreconditionNot(isBeattackCondition);
    mainActionNode->setNodePrecondition(notCondition);
    {
        //Root-主动行为节点-反向移动(实际距离小于最小攻击距离)
        auto readyMinAttackNode=APBevTreeNodeFactory::createSequenceNode(mainActionNode, "最小攻击还小");
        BTConditionIsMinAttackDist::create(readyMinAttackNode);
        {
            //Root-主动行为节点-反向攻击-待机
            auto beforeWait= APBevTreeNodeFactory::createTeminalNode<EnemyBevTreeNodeIdle>(readyMinAttackNode, "待机");
            ((EnemyBevTreeNodeIdle*)beforeWait)->setWaitingTime(1.0);
            APBevTreeNodeFactory::createTeminalNode<BevTreeNodeLeave>(readyMinAttackNode, "离开英雄");
            //Root-主动行为节点-反向攻击-待机
            APBevTreeNodeFactory::createTeminalNode<EnemyBevTreeNodeIdle>(readyMinAttackNode, "待机");
        }
        
        //Root-主动行为节点-准备攻击(实际距离小于攻击距离)
        auto readyAttackNode=APBevTreeNodeFactory::createSequenceNode(mainActionNode, "攻击");
        BTConditionIsAttackDist::create(readyAttackNode);
        {
            //Root-主动行为节点-准备攻击-翻面
            APBevTreeNodeFactory::createTeminalNode<BevTreeNodeFace>(readyAttackNode, "面对攻击者");
            //Root-主动行为节点-准备攻击-攻击前待机
            APBevTreeNodeFactory::createTeminalNode<EnemyBevTreeNodeIdleAttackBefore>(readyAttackNode, "前待");
            //Root-主动行为节点-准备攻击-攻击
            APBevTreeNodeFactory::createTeminalNode<BevTreeNodeEnemyAttack>(readyAttackNode, "攻击");
            //Root-主动行为节点-准备攻击-攻击后待机
            APBevTreeNodeFactory::createTeminalNode<EnemyBevTreeNodeIdleAttackAfter>(readyAttackNode, "后待机");
        }
        
        //Root-主动行为节点-追逐
        auto catchNode=APBevTreeNodeFactory::createSequenceNode(mainActionNode, "追逐");
        {
            //Root-主动行为节点-追逐英雄
            APBevTreeNodeFactory::createTeminalNode<BevTreeNodeCatch>(catchNode, "追逐英雄");
            //Root-主动行为节点-追逐待机
            APBevTreeNodeFactory::createTeminalNode<EnemyBevTreeNodeIdleCatch>(catchNode, "追逐待机");
        }
    }
}

// Update is called once per frame
void EnemyAI::update(float ft)
{
    //输入数据参数
    auto inputData =m_Parent->readBevNodeInputData();
    inputData->m_TimeStep = ft;
    BevNodeInputParam input(inputData);
    
    BTNodeOutputData* enemyOutData=m_Parent->getBevOutputData();
    BevNodeOutputParam output(enemyOutData);
    
    if(m_BevTreeRoot && m_BevTreeRoot->evaluate(input))
    {
        m_BevTreeRoot->tick(input, output);
    }
    if (m_BevTreeRoot->mo_ActiveNode) {
        //log("%s",m_BevTreeRoot->mo_ActiveNode->getDebugName());
    }
    m_Parent->updateAIOutData(enemyOutData);
}

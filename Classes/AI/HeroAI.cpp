//
//  HeroAI.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/18.
//
//

#include "HeroAI.h"
#include "HeroBevTreeHeader.h"
#include "HeroBevFactory.h"
#include "HeroBevTreeNode.h"
#include "BTNode.h"
#include "BTcondition.h"
#include "APBevTreePreconditionOR.h"

HeroAI::~HeroAI()
{
    CC_SAFE_DELETE(m_BevTreeRoot);
}

HeroAI::HeroAI(HeroBase *parent)
{
    m_Parent=parent;
    
    APBevTreeNodePrioritySelector* pRoot = new APBevTreeNodePrioritySelector(nullptr);
    m_BevTreeRoot=pRoot;
    m_BevTreeRoot->setDebugName("根节点");
}

//创建行为树
void HeroAI::createBevTree()
{
    //Root-被动节点
    auto passiveNode=APBevTreeNodeFactory::createPrioritySelectorNode(m_BevTreeRoot, "被动行为(优先选择)");
    BTConditionIsBeAttack::create(passiveNode);
    {
        //Root-被动节点-被打节点(被攻击条件)
        APBevTreeNodeFactory::createTeminalNode<BevTreeNodeBeAttack>(passiveNode, "被打(叶子)");
    }
    
    //Root-玩家控制节点
    auto controlNode=APBevTreeNodeFactory::createPrioritySelectorNode(m_BevTreeRoot, "控制节点");
    BTConditionPlayerControl::create(controlNode);
    {
        //Root-玩家控制节点-发射技能
        auto controlSkill=APBevTreeNodeFactory::createTeminalNode<BevTreeNodeSkill>(controlNode, "控制技能");
        BTConditionPlayerControlSkill::create(controlSkill);
        
        //Root-玩家控制节点-普通攻击
        auto controlAtt=APBevTreeNodeFactory::createTeminalNode<BevTreeNodeAttack>(controlNode, "控制普攻");
        BTConditionPlayerControlAtt::create(controlAtt);
        
        //Root-玩家控制节点-左右移动
        auto controlMove=APBevTreeNodeFactory::createTeminalNode<BevTreeNodeMove>(controlNode, "控制移动");
        BTConditionPlayerControlMove::create(controlMove);
        
        //Root-玩家控制节点-待机
        auto idleNode=APBevTreeNodeFactory::createTeminalNode<BevTreeNodeIdle>(controlNode, "待机");
        
        auto orCondition=new APBevTreePreconditionOR();
        auto noneState=new BTConditionCurrState();
        noneState->conditionState=GameEnum::BodyState::None;
        auto runState=new BTConditionCurrState();
        runState->conditionState=GameEnum::BodyState::Run;
        orCondition->addCondition(noneState);
        orCondition->addCondition(runState);
        idleNode->setNodePrecondition(orCondition);
    }
    //Root-NPC控制节点
    auto npcNode =APBevTreeNodeFactory::createPrioritySelectorNode(m_BevTreeRoot, "AI控制节点");
    auto btPlayerControl=new BTConditionPlayerControl();
    auto notCondition=new APBevTreePreconditionNot(btPlayerControl);
    npcNode->setNodePrecondition(notCondition);
    {
        //Root-NPC控制节点-攻击
        auto readyAttackNode=APBevTreeNodeFactory::createTeminalNode<HeroBevTreeNPCAttack>(npcNode, "攻击");
        BTConditionIsAttackDist::create(readyAttackNode);
        
        //Root-NPC控制节点-移动到目标
        auto moveToTargetNode=APBevTreeNodeFactory::createTeminalNode<BevTreeNodeMoveToTarget>(npcNode, "移动到目标");
        BTConditionIsCatchEnemy::create(moveToTargetNode);

        //Root-NPC控制节点-跟随
        auto followNode=APBevTreeNodeFactory::createTeminalNode<BevTreeNodeFollow>(npcNode, "跟随");
        BTConditionFollowHero::create(followNode);
        
        //Root-NPC控制节点-待机节点
        auto idleNode=APBevTreeNodeFactory::createTeminalNode<BevTreeNodeIdle>(npcNode, "待机");
        auto currState=new BTConditionCurrState();
        currState->conditionState=GameEnum::BodyState::None;
        auto waitRunCondition=new APBevTreePreconditionIsTrue(currState);
        idleNode->setNodePrecondition(waitRunCondition);
    }
}

// Update is called once per frame
void HeroAI::update(float ft)
{
    //输入数据参数
    auto inputData =m_Parent->readBevNodeInputData();
    inputData->m_TimeStep = ft;
    BevNodeInputParam input(inputData);
    
    BTNodeOutputData* outData=m_Parent->getBevOutputData();
    BevNodeOutputParam output(outData);
    
    if(m_BevTreeRoot && m_BevTreeRoot->evaluate(input))
    {
        m_BevTreeRoot->tick(input, output);
    }
    
    if (m_BevTreeRoot->mo_ActiveNode && inputData->m_IsMainHero==false) {
        log("%s",m_BevTreeRoot->mo_ActiveNode->getDebugName());
    }
    
    m_Parent->updateAIOutData(outData);
}

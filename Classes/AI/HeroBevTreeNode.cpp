//
//  HeroBevTreeNode.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/19.
//
//

#include "HeroBevTreeNode.h"
#include "HeroBevTreeHeader.h"
#include "HeroEventObject.h"

#pragma mark - HeroBevTreeNodeIdle
//进入
void HeroBevTreeNodeIdle::doEnter(const BevNodeInputParam& input)
{
    //空闲
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    //播放动画名称
    animateName=inputData.m_Owner->getActionFileMode()->ActionIdle;
}
//空闲
BevRunningStatus HeroBevTreeNodeIdle::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    HeroBevTreeOutputData& outputData = output.getRealDataType<HeroBevTreeOutputData>();

    outputData.m_vVelocity=Vec2::ZERO;
    //判断是否动画播放完成
    auto state= inputData.m_Owner->getAnimateState(animateName);
    if (state!=BaseActionObject::AnimateState::Runing) {
        auto event= HeroEventObject::create();
        event->setEnemyEvent(GameEnum::EnemyEvent::EventPlayAnimate);
        event->setEventArg(__String::create(animateName));
        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }
    
    return k_BRS_Executing;
}

#pragma mark - HeroBevTreeNodeMove
//进入
void HeroBevTreeNodeMove::doEnter(const BevNodeInputParam& input)
{
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    //播放动画名称
    animateName=inputData.m_Owner->getActionFileMode()->ActionRunName;
}
//控制英雄移动
BevRunningStatus HeroBevTreeNodeMove::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    HeroBevTreeOutputData& outputData = output.getRealDataType<HeroBevTreeOutputData>();
    
    if (inputData.m_PlayerControl->getButtonState(AttackButtonType::btLeft)) {
        outputData.m_vVelocity=Vec2(-inputData.m_Owner->getHeroModel()->RunMoveSpeed,0);
        outputData.m_NextFacing=Vec2(-1,0);
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btRight))
    {
        outputData.m_vVelocity=Vec2(inputData.m_Owner->getHeroModel()->RunMoveSpeed,0);
        outputData.m_NextFacing=Vec2(1,0);
    }
    
    float timeStep = inputData.m_TimeStep;
    m_WaitingTime -= timeStep;
    //
    //判断是否动画播放完成
    auto state= inputData.m_Owner->getAnimateState(animateName);
    if (state!=BaseActionObject::AnimateState::Runing) {
        auto event= HeroEventObject::create();
        event->setEnemyEvent(GameEnum::EnemyEvent::EventPlayAnimate);
        event->setEventArg(__String::create(animateName));
        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }
    
    if(m_WaitingTime < 0)
    {
        return k_BRS_Finish;
    }
    
    return k_BRS_Executing;
}

#pragma mark - HeroBevTreeNodeAtt
//进入
void HeroBevTreeNodeAtt::doEnter(const BevNodeInputParam& input)
{
    //
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    //播放动画名称
    animateName=inputData.m_Owner->commonAttack();
}
//控制英雄移动
BevRunningStatus HeroBevTreeNodeAtt::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    HeroBevTreeOutputData& outputData = output.getRealDataType<HeroBevTreeOutputData>();
    
    if (inputData.m_PlayerControl->isAttackButtonPress()) {
        inputData.m_Owner->commonAttack();
        outputData.m_vVelocity=Vec2::ZERO;
    }
    
    //判断是否动画播放完成
    auto state=inputData.m_Owner->getAnimateState(animateName);
    if (state==BaseActionObject::AnimateState::Finish) {
        return k_BRS_Finish;
    }
    
    return k_BRS_Executing;
}

#pragma mark - HeroBevTreeNodeSkill 控制技能攻击
//控制技能攻击
void HeroBevTreeNodeSkill::doEnter(const BevNodeInputParam& input)
{
    //空闲
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    //播放动画名称
    if (inputData.m_PlayerControl->getButtonState(AttackButtonType::btAttackA)) {
        animateName=inputData.m_Owner->getActionFileMode()->SkillName1;
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btAttackB)) {
        animateName=inputData.m_Owner->getActionFileMode()->SkillName2;
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btAttackC)) {
        animateName=inputData.m_Owner->getActionFileMode()->SkillName3;
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btAttackD)) {
        animateName=inputData.m_Owner->getActionFileMode()->SkillName4;
    }
    m_isPlayAnimate=true;
}
//控制技能攻击
BevRunningStatus HeroBevTreeNodeSkill::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    HeroBevTreeOutputData& outputData = output.getRealDataType<HeroBevTreeOutputData>();
    
    outputData.m_vVelocity=Vec2::ZERO;
    
    if (m_isPlayAnimate) {
        m_isPlayAnimate=false;
        auto event= HeroEventObject::create();
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

#pragma mark - HeroBevTreeNPCAttack Npc-攻击
//Npc-攻击
void HeroBevTreeNPCAttack::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    //获取当前在播放动画的名称
    animateName=inputData.m_Owner->getActionFileMode()->ActionAttackName1;
    m_WaitingTime=0;
}
//Npc-攻击
BevRunningStatus HeroBevTreeNPCAttack::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();

    //未播放完技能动画直接返回
    if (inputData.m_Owner->getBodyState()==GameEnum::BodyState::Skill) {
        return k_BRS_Executing;
    }
    
    m_WaitingTime+=inputData.m_TimeStep;
    
    float attactRandom=CCRANDOM_0_1();
    //技能攻击
    if (attactRandom < 0.15 && inputData.m_Owner->getBodyState()!=GameEnum::BodyState::Attack) {
        float skillRandom=CCRANDOM_0_1();
        //计算随机NPC播放技能
        if (skillRandom > 0.75 && skillRandom < 1.0) {
            animateName=inputData.m_Owner->getActionFileMode()->SkillName1;
        }else if (skillRandom > 0.5 && skillRandom < 0.75) {
            animateName=inputData.m_Owner->getActionFileMode()->SkillName2;
        }else if (skillRandom > 0.25 && skillRandom < 0.5) {
            animateName=inputData.m_Owner->getActionFileMode()->SkillName3;
        }else{
            animateName=inputData.m_Owner->getActionFileMode()->SkillName4;
        }
        auto event=BaseActionEvent::create();
        event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
        event->setEventArg(__String::create(animateName));
        event->setEventBodyState(GameEnum::BodyState::Skill);
        outputData.m_OutEvent.pushBack(event);
    }else   //普通攻击
    {
        if (m_WaitingTime>0.15) {
            m_WaitingTime=0;
            if (inputData.m_CurrPosition2D.x > inputData.m_TargetPosition2D.x) {
                outputData.m_NextFacing=Vec2(-1,0);
            }else{
                outputData.m_NextFacing=Vec2(1,0);
            }
        }
        
        inputData.m_Owner->commonAttack();
        
        
        /*
        auto heroModel=inputData.m_Owner->getActionFileMode();
        std::string strlastAnimateName=inputData.m_Owner->lastPlayAnimateName;
        std::string strName="null";
        std::vector<std::string> strVec;
        strVec.push_back(heroModel->ActionAttackName1);
        strVec.push_back(heroModel->ActionAttackName2);
        strVec.push_back(heroModel->ActionAttackName3);
        if (heroModel->ActionAttackName4!=strName) {
            strVec.push_back(heroModel->ActionAttackName4);
        }
        if (heroModel->ActionAttackName5!=strName) {
            strVec.push_back(heroModel->ActionAttackName5);
        }
        for (int i=0; i< strVec.size(); i++) {
            if (strlastAnimateName==strVec.at(i)) {
                int playIndex=i+1;
                playIndex= (playIndex==strVec.size()) ? 0 : playIndex;
                animateName=strVec.at(playIndex);
                break;
            }
        }*/
    }
    outputData.m_vVelocity=Vec2::ZERO;
    
    /*
    //普通攻击
    auto event=BaseActionEvent::create();
    event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
    event->setEventArg(__String::create(animateName));
    event->setEventBodyState(GameEnum::BodyState::Attack);
    outputData.m_OutEvent.pushBack(event);
    */
    return k_BRS_Executing;
}

#pragma mark - HeroBevTreeNPCFollow Npc-跟随英雄
//Npc-跟随英雄
void HeroBevTreeNPCFollow::doEnter(const BevNodeInputParam& input)
{
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    //播放动画名称
    animateName=inputData.m_Owner->getActionFileMode()->ActionRunName;
}
//Npc-跟随英雄
BevRunningStatus HeroBevTreeNPCFollow::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
    HeroBevTreeOutputData& outputData = output.getRealDataType<HeroBevTreeOutputData>();
    
    if (inputData.m_MainHeroPosition.x < inputData.m_HeroPosition2D.x) {
        outputData.m_vVelocity=Vec2(-inputData.m_Owner->getHeroModel()->RunMoveSpeed,0);
        outputData.m_NextFacing=Vec2(-1,0);
    }else
    {
        outputData.m_vVelocity=Vec2(inputData.m_Owner->getHeroModel()->RunMoveSpeed,0);
        outputData.m_NextFacing=Vec2(1,0);
    }
    
    float timeStep = inputData.m_TimeStep;
    m_WaitingTime -= timeStep;
    //判断是否动画播放完成
    auto state= inputData.m_Owner->getAnimateState(animateName);
    if (state!=BaseActionObject::AnimateState::Runing) {
        auto event= HeroEventObject::create();
        event->setEnemyEvent(GameEnum::EnemyEvent::EventPlayAnimate);
        event->setEventArg(__String::create(animateName));
        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }

    return k_BRS_Executing;
}

#pragma mark - HeroBevTreeBeAttack Npc-被攻击
//Npc-被攻击
void HeroBevTreeBeAttack::doEnter(const BevNodeInputParam& input)
{
//    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
//    //播放动画名称
//    animateName=inputData.m_Owner->getActionFileMode()->ActionRunName;
}
//Npc-被攻击
BevRunningStatus HeroBevTreeBeAttack::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
//    const HeroBevTreeInputData& inputData = input.getRealDataType<HeroBevTreeInputData>();
//    HeroBevTreeOutputData& outputData = output.getRealDataType<HeroBevTreeOutputData>();
//    
//    if (inputData.m_MainHeroPosition.x < inputData.m_HeroPosition2D.x) {
//        outputData.m_vVelocity=Vec2(-inputData.m_Owner->getHeroModel()->RunMoveSpeed,0);
//        outputData.m_NextFacing=Vec2(-1,0);
//    }else
//    {
//        outputData.m_vVelocity=Vec2(inputData.m_Owner->getHeroModel()->RunMoveSpeed,0);
//        outputData.m_NextFacing=Vec2(1,0);
//    }
//    
//    float timeStep = inputData.m_TimeStep;
//    m_WaitingTime -= timeStep;
//    //
//    //判断是否动画播放完成
//    auto state= inputData.m_Owner->getAnimateState(animateName);
//    if (state!=BaseActionObject::AnimateState::Runing) {
//        auto event= HeroEventObject::create();
//        event->setEnemyEvent(GameEnum::EnemyEvent::EventPlayAnimate);
//        event->setEventArg(__String::create(animateName));
//        outputData.m_OutEvent.pushBack(event);
//        return k_BRS_Executing;
//    }
//    
//    return k_BRS_Executing;
};

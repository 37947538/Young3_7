//
//  BTNode.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/25.
//
//

#include "BTNode.h"
#include "BaseActionObject.h"
#include "ActionFileModel.h"
#include "AttackObject.h"
#include "EnemyBase.h"
#include "EnemyModel.h"

#pragma mark - 主体模版
//模版进入
void BevTreeNodeTemp::doEnter(const BevNodeInputParam& input)
{
    //const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
}

//模版执行
BevRunningStatus BevTreeNodeTemp::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    //const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    //BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    //{
    //    return k_BRS_Finish;
    //}
    
    return k_BRS_Executing;
}

#pragma mark - 主体被击
//主体被击
void BevTreeNodeBeAttack::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    iAttDist=inputData.m_BeAttackFlyPower;
    if (iAttDist==0){
        iAttDist=APTools::getRand(5, 10);
    }
}

//主体死亡
BevRunningStatus BevTreeNodeBeAttack::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    /*
    if (!inputData.m_IsMainHero) {
        Vec2 targetPoint2D=inputData.m_TargetPosition2D;
        Vec2 curPosition2D=inputData.m_CurrPosition2D;
        Vec2 dir = targetPoint2D - curPosition2D;
        
        if (dir.x > 0) {
            outputData.m_NextFacing=Vec2(1,0);
        }else{
            outputData.m_NextFacing=Vec2(-1,0);
        }
    }
    //计算被攻击位移
    iAttDist-=1;
    iAttDist= iAttDist < 0 ? 0 : iAttDist;
    outputData.m_NextPosition=inputData.m_CurrPosition2D-inputData.m_CurrentFacing*iAttDist;
    */
    //log("inputData.m_CurrPosition2D=[%0.2f,%0.2f]",inputData.m_CurrPosition2D.x,inputData.m_CurrPosition2D.y);
    //log("inputData.m_NextPosition=[%0.2f,%0.2f]",outputData.m_NextPosition.x,outputData.m_NextPosition.y);
    
    return k_BRS_Executing;
}

#pragma mark - 主体攻击
/**
 *  主体攻击
 */
void BevTreeNodeAttack::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    //播放动画名称
    //animateName=inputData.m_Owner->commonAttack();
}

//主体攻击
BevRunningStatus BevTreeNodeAttack::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
 
    if (inputData.m_PlayerControl->isAttackButtonPress()) {
        inputData.m_Owner->commonAttack();
        outputData.m_vVelocity=Vec2::ZERO;
    }
    //方向
    if (inputData.m_PlayerControl->getButtonState(AttackButtonType::btLeft)) {
        outputData.m_NextFacing=Vec2(-1,0);
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btRight)) {
        outputData.m_NextFacing=Vec2(1,0);
    }
    
    //判断是否攻击动画播放完成
    auto state= inputData.m_Owner->getAnimateState(animateName);
    if (state==BaseActionObject::AnimateState::Finish) {
        return k_BRS_Finish;
    }

    return k_BRS_Executing;
}


#pragma mark - 主体怪攻击
/**
 *  主体攻击
 */
void BevTreeNodeEnemyAttack::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    //播放动画名称
    //animateName=inputData.m_Owner->commonAttack();
    isPlay=false;
    m_SkillTime=APTools::getRandFloat(2.0, 5.0);
}

//主体攻击
BevRunningStatus BevTreeNodeEnemyAttack::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
    m_Time+=inputData.m_TimeStep;
    if (!isPlay) {
        isPlay=true;
        std::string skillName=inputData.m_Owner->getActionFileMode()->SkillName1;
        if (m_Time>m_SkillTime && skillName.compare("null")<0) {
            m_Time=0.0f;
            //播放动画名称
            animateName=inputData.m_Owner->getActionFileMode()->SkillName1;
            auto event= BaseActionEvent::create();
            event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
            event->setEventArg(__String::create(animateName));
            event->setEventBodyState(GameEnum::BodyState::Skill);
            outputData.m_OutEvent.pushBack(event);
        }else{
            //播放动画名称
            animateName=inputData.m_Owner->getActionFileMode()->ActionAttackName1;
            auto event= BaseActionEvent::create();
            event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
            event->setEventArg(__String::create(animateName));
            event->setEventBodyState(GameEnum::BodyState::Attack);
            outputData.m_OutEvent.pushBack(event);
        }
        
        return k_BRS_Executing;
    }
    
    //判断是否动画播放完成
    auto state= inputData.m_Owner->getAnimateState(animateName);
    if (state==BaseActionObject::AnimateState::Finish) {
        return k_BRS_Finish;
    }
    
    return k_BRS_Executing;
}


#pragma mark - 主体移动
/**
 *  主体移动
 */
void BevTreeNodeMove::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    //播放动画名称
    animateName=inputData.m_Owner->getActionFileMode()->ActionRunName;
}

//主体死亡
BevRunningStatus BevTreeNodeMove::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
    //判断是否攻击
    auto state=inputData.m_Owner->getBodyState();
    if (state==GameEnum::BodyState::Attack) {
        return k_BRS_Finish;
    }
    
    if (inputData.m_PlayerControl->getButtonState(AttackButtonType::btLeft)) {
        outputData.m_vVelocity=Vec2(-inputData.m_RunMoveSpeed,0);
        outputData.m_NextFacing=Vec2(-1,0);
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btRight)) {
        outputData.m_vVelocity=Vec2(inputData.m_RunMoveSpeed,0);
        outputData.m_NextFacing=Vec2(1,0);
    }
    
    if (inputData.m_OwnerState !=GameEnum::BodyState::Run) {
        auto event=BaseActionEvent::create();
        event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
        event->setEventArg(__String::create(animateName));
        event->setEventBodyState(GameEnum::BodyState::Run);
        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }
    
    return k_BRS_Executing;
}

#pragma mark - 主体技能
/**
 *  主体技能
 */
void BevTreeNodeSkill::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    //播放动画名称
    if (inputData.m_PlayerControl->getButtonState(AttackButtonType::btAttackA)) {
        animateName=inputData.m_Owner->getActionFileMode()->SkillName1;
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btAttackB))
    {
        animateName=inputData.m_Owner->getActionFileMode()->SkillName2;
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btAttackC))
    {
        animateName=inputData.m_Owner->getActionFileMode()->SkillName3;
    }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btAttackD))
    {
        animateName=inputData.m_Owner->getActionFileMode()->SkillName4;
    }
}

//主体技能
BevRunningStatus BevTreeNodeSkill::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
    outputData.m_vVelocity=Vec2::ZERO;
    
    if (inputData.m_IsSkillMove) {
        if (inputData.m_PlayerControl->getButtonState(AttackButtonType::btLeft)) {
            outputData.m_vVelocity=Vec2(-inputData.m_RunMoveSpeed,0);
            outputData.m_NextFacing=Vec2(-1,0);
        }else if(inputData.m_PlayerControl->getButtonState(AttackButtonType::btRight)) {
            outputData.m_vVelocity=Vec2(inputData.m_RunMoveSpeed,0);
            outputData.m_NextFacing=Vec2(1,0);
        }
    }    
    
    if (inputData.m_OwnerState !=GameEnum::BodyState::Skill) {
        auto event= BaseActionEvent::create();
        event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
        event->setEventArg(__String::create(animateName));
        event->setEventBodyState(GameEnum::BodyState::Skill);
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

#pragma mark - 主体待机
/**
 *  主体待机
 */
void BevTreeNodeIdle::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    //播放动画名称
    animateName=inputData.m_Owner->getActionFileMode()->ActionIdle;
    waitTime=0.0f;
}

//主体死亡
BevRunningStatus BevTreeNodeIdle::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
    outputData.m_vVelocity=Vec2::ZERO;
    outputData.m_NextFacing=inputData.m_CurrentFacing;
    
    float ft=inputData.m_TimeStep;
    waitTime+=ft;
    if (waitTime > idleTime) {
        return k_BRS_Finish;
    }
    
    //判断是否动画播放完成
    if (inputData.m_OwnerState!=GameEnum::BodyState::Idle) {
        auto event= BaseActionEvent::create();
        event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
        event->setEventArg(__String::create(animateName));
        event->setEventBodyState(GameEnum::BodyState::Idle);
        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }
    return k_BRS_Executing;
}

#pragma mark - 主体跟随
/**
 *  主体跟随
 */
void BevTreeNodeFollow::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    animateName=inputData.m_Owner->getActionFileMode()->ActionRunName;
}

//主体死亡
BevRunningStatus BevTreeNodeFollow::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
    Vec2 targetPoint2D = inputData.m_CurrPosition2D;//.m_TargetPosition2D;
    Vec2 curPosition2D=inputData.m_MainHeroPosition2D;
    Vec2 dir = targetPoint2D - curPosition2D;
    
    if(fabsf(dir.x) < 200)
    {
        return k_BRS_Finish;
    }
    else
    {
        //判断是否动画播放完成
        if (inputData.m_OwnerState!=GameEnum::BodyState::Run) {
            auto event= BaseActionEvent::create();
            event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
            event->setEventArg(__String::create(animateName));
            event->setEventBodyState(GameEnum::BodyState::Run);
            outputData.m_OutEvent.pushBack(event);
        }
        
        if (dir.x > 0) {
            outputData.m_NextFacing=Vec2(-1,0);
        }else{
            outputData.m_NextFacing=Vec2(1,0);
        }
        Vec2 subPos2D=outputData.m_NextFacing * inputData.m_RunMoveSpeed;
        Vec2 nextPos2D = curPosition2D + subPos2D;
        outputData.m_NextPosition=nextPos2D;
        outputData.m_vVelocity=subPos2D;
    }
    
    return k_BRS_Executing;
}


#pragma mark - 主体转向对面
/**
 *  主体转向对面
 */
void BevTreeNodeFace::doEnter(const BevNodeInputParam& input)
{
    //const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
}

BevRunningStatus BevTreeNodeFace::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D=inputData.m_CurrPosition2D;
    Vec2 dir = targetPoint2D - curPosition2D;
    
    if (dir.x > 0) {
        outputData.m_NextFacing=Vec2(1,0);
    }else{
        outputData.m_NextFacing=Vec2(-1,0);
    }
    
    return k_BRS_Finish;;
};

#pragma mark - 主体追逐
/**
 *  主体追逐
 */
void BevTreeNodeCatch::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    animateName=inputData.m_Owner->getActionFileMode()->ActionRunName;
    currCatchTime=0.0f;
    
    auto enemy=(EnemyBase*)inputData.m_Owner;
    auto time=PointFromString(enemy->getEnemyModel()->CatchTime);
    maxCatchTime=APTools::getRandFloat(time.x, time.y);
}
BevRunningStatus BevTreeNodeCatch::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
    currCatchTime += inputData.m_TimeStep;
    if (currCatchTime > maxCatchTime) {
        return k_BRS_Finish;
    }
    
    //判断是否动画播放完成
    if (inputData.m_OwnerState!=GameEnum::BodyState::Run) {
        auto event= BaseActionEvent::create();
        event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
        event->setEventArg(__String::create(animateName));
        event->setEventBodyState(GameEnum::BodyState::Run);

        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }
    
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D=inputData.m_CurrPosition2D;
    Vec2 dir = targetPoint2D - curPosition2D;
    
    if(fabsf(dir.x) < inputData.m_iAttackDist) {
        return k_BRS_Finish;
    }else{
        if (dir.x > 0) {
            outputData.m_NextFacing=Vec2(1,0);
        }else{
            outputData.m_NextFacing=Vec2(-1,0);
        }
        Vec2 subPos2D=outputData.m_NextFacing * inputData.m_RunMoveSpeed;
        Vec2 nextPos2D = curPosition2D + subPos2D;
        outputData.m_NextPosition =nextPos2D;
    }
    
    return k_BRS_Executing;
};

#pragma mark - 主体离开对象
void BevTreeNodeLeave::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    animateName=inputData.m_Owner->getActionFileMode()->ActionRunName;
}
BevRunningStatus BevTreeNodeLeave::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    //float timeStep = inputData.m_TimeStep;
    
    //判断是否动画播放完成
    if (inputData.m_OwnerState!=GameEnum::BodyState::Run) {
        auto event= BaseActionEvent::create();
        event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
        event->setEventArg(__String::create(animateName));
        event->setEventBodyState(GameEnum::BodyState::Run);

        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Executing;
    }
    
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D=inputData.m_CurrPosition2D;
    int iAttMinDis=inputData.m_iAttackDistMin;
    
    Vec2 dir = targetPoint2D - curPosition2D;
    
    //EnemyBase* eBase=(EnemyBase*)inputData.m_Owner;
    //EnemyModel* emodel=eBase->getEnemyModel();
    
    if(fabsf(dir.x)  > iAttMinDis)
    {
        return k_BRS_Finish;
    }
    else
    {
        if (dir.x > 0) {
            outputData.m_NextFacing=Vec2(-1,0);
        }else
        {
            outputData.m_NextFacing=Vec2(1,0);
        }
        Vec2 subPos2D=outputData.m_NextFacing * inputData.m_RunMoveSpeed;
        Vec2 nextPos2D =curPosition2D +subPos2D;
        outputData.m_NextPosition=nextPos2D;
    }
    
    return k_BRS_Executing;
};

#pragma mark - 移动到目标
void BevTreeNodeMoveToTarget::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    animateName=inputData.m_Owner->getActionFileMode()->ActionRunName;
}

BevRunningStatus BevTreeNodeMoveToTarget::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    
    Vec2 targetPoint2D=inputData.m_TargetPosition2D;
    Vec2 curPosition2D=inputData.m_CurrPosition2D;
    Vec2 dir = targetPoint2D - curPosition2D;
    
    if(fabsf(dir.x) < inputData.m_iAttackDist)
    {
        return k_BRS_Finish;
    }
    else
    {
        //判断是否动画播放完成
        if (inputData.m_OwnerState!=GameEnum::BodyState::Run) {
            auto event= BaseActionEvent::create();
            event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
            event->setEventArg(__String::create(animateName));
            event->setEventBodyState(GameEnum::BodyState::Run);
            outputData.m_OutEvent.pushBack(event);
        }
        
        if (dir.x > 0) {
            outputData.m_NextFacing=Vec2(1,0);
        }else{
            outputData.m_NextFacing=Vec2(-1,0);
        }
        Vec2 subPos2D=outputData.m_NextFacing * inputData.m_RunMoveSpeed;
        Vec2 nextPos2D = curPosition2D + subPos2D;
        outputData.m_NextPosition =nextPos2D;
        outputData.m_vVelocity=subPos2D;
    }
    
    return k_BRS_Executing;
};

#pragma mark - 敌兵被击
//敌兵被击
void BevTreeNodeEnemyBeAttack::doEnter(const BevNodeInputParam& input)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    m_BeAttackFlyPower=inputData.m_BeAttackFlyPower;
    m_Ground=inputData.m_CurrPosition2D;
    
    Vec2 targetPoint2D=inputData.m_TargetPosition2D;
    Vec2 curPosition2D=inputData.m_CurrPosition2D;
    Vec2 dir = targetPoint2D - curPosition2D;
    if (dir.x > 0) {
        m_BeAttackFlyPower=-(m_BeAttackFlyPower);
    }
    //不能打出界
    float width=curPosition2D.x + m_BeAttackFlyPower;
    float mapWidth=inputData.m_MapMoveWidth;
    if (width < 0) {
        float x=abs(width);
        m_BeAttackFlyPower+=x;
    }
    if (width > mapWidth) {
        float x=mapWidth - curPosition2D.x;
        m_BeAttackFlyPower=x;
    }
    inputData.m_Owner->runAction(Sequence::create(MoveBy::create(0.05, Vec2(m_BeAttackFlyPower, 0)), NULL));
    
    /*
    auto currPos=inputData.m_CurrPosition2D;
    Vec2 m_Direction=Vec2(300,300);        //矢量（方向）
    float m_AttPower=300;                  //力量
    float fAngle=APTools::getAntiAngle(currPos, currPos + m_Direction);
    float radian=CC_DEGREES_TO_RADIANS(fAngle);
    float x=cosf(radian);
    float y=sinf(radian);
    
    m_Power=m_AttPower * x / y;
     */
}

BevRunningStatus BevTreeNodeEnemyBeAttack::doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    BTNodeOutputData& outputData = output.getRealDataType<BTNodeOutputData>();
    outputData.m_NextPosition=Vec2::ZERO;
    /*
    float ft=inputData.m_TimeStep;
    m_ExecuteTime+=ft;
    float m_Acceleration=200 * m_ExecuteTime;
    auto currPos=inputData.m_CurrPosition2D;
    
    float m_Mass=5;                     //质量
    float speed=m_Power / m_Mass;
    Vec2 offset=Vec2(speed * ft + m_Acceleration, speed * ft + m_Acceleration);
    
    if (currPos.y>580) {
        m_IsUp=false;
    }
    if (!m_IsUp) {
        offset.y*=-1;
    }
    
    auto newPos=currPos + offset;
    outputData.m_NextPosition=newPos;
    
    if (newPos.y<=m_Ground.y) {
        outputData.m_NextPosition.y=m_Ground.y;
        //播放动画名称
        animateName=inputData.m_Owner->getActionFileMode()->ActionIdle;
        auto event= BaseActionEvent::create();
        event->setBaseActionEvent(GameEnum::BaseActionEventType::PlayAnimate);
        event->setEventArg(__String::create(animateName));
        event->setEventBodyState(GameEnum::BodyState::Idle);
        outputData.m_OutEvent.pushBack(event);
        return k_BRS_Finish;
    }
    
    log("------currPos[%f,%f]newPos[%f,%f]offset[%f,%f]",currPos.x,currPos.y,newPos.x,newPos.y,offset.x,offset.y);
    */
    return k_BRS_Executing;
};

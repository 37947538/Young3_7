//
//  BaseActionObject.cpp
//  Zombie3_4
//
//  Created by jl on 15/6/25.
//
//
#include "BaseActionObject.h"
#include "ActionFileModel.h"
#include "ActionFileModelBLL.h"
#include "SoundBLL.h"
#include "GameBLL.h"
#include "GameLayer.h"

#define kScale 1.0

//基础动作对象
BaseActionObject::~BaseActionObject()
{
    delete m_steeringBehavior;
    delete m_InputData;
    delete m_BevOutData;
    delete m_ActionFileModel;
}

//基础动作对象
BaseActionObject::BaseActionObject()
{
    m_ActionFileModel=new ActionFileModel();
    m_OrderID=-1;
    m_BodyState=GameEnum::BodyState::None;
    m_InputData= new BTNodeInputData();
    m_BevOutData= new BTNodeOutputData();
    m_steeringBehavior=new SteeringBehaviors(this);
    m_dMaxForce=0;                          //实体产生的供以自己动力的最大力
    m_dAddSpeed=0;                          //实体产生的供以自己动力的速度
    m_dMaxSpeed=0;                          //实体的最大速度
    m_dMaxTurnRate=0;                       //旋转的最大速率(弧度每秒)
    m_BeAttackFlyPower=0.0;
}

//加载动作文件
void BaseActionObject::loadActionFile(int fid)
{
    fid--;
    //获取骨骼模型
    auto amb= ActionFileModelBLL::create(kModelWritablePath);
    CCASSERT(fid >=0 && fid <amb->getModelSize(), "BaseActionObject::loadActionFile index error!");
    ActionFileModel *afm=&(amb->modelData[fid]);
    memcpy(m_ActionFileModel, afm, sizeof(ActionFileModel));
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo(m_ActionFileModel->ArmFilePath);
    m_Armature=Armature::create(m_ActionFileModel->ArmName);
    m_Armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(BaseActionObject::movementEvent, this));
    m_Armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BaseActionObject::frameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    m_Armature->setScale(kScale);
    this->addChild(m_Armature);
}

void BaseActionObject::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType==MovementEventType::COMPLETE || movementType==MovementEventType::LOOP_COMPLETE) {
        animateFinish(movementID);
    }
}

//动画播放完成
void BaseActionObject::animateFinish(const std::string& name)
{
    auto iter= m_animateStates.find(name);
    if (iter!=m_animateStates.end()) {
        iter->second=BaseActionObject::AnimateState::Finish;
        lastPlayAnimateName=name;
    }
    m_BodyState=GameEnum::BodyState::None;
}

//切换状态
void BaseActionObject::changeState(GameEnum::BodyState bs,const std::string& animateName)
{
    setBodyState(bs);
    playAnimate(animateName);
}

void BaseActionObject::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    //颤屏
    if (frameEventName.compare("shake1")==0) {
        GameBLL::instance()->shake(1);
    }else if(frameEventName.compare("shake2")==0)
    {
        GameBLL::instance()->shake(2);
    }else if(frameEventName.compare("shake3")==0)
    {
        GameBLL::instance()->shake(3);
    }else if(frameEventName.compare("shake4")==0)
    {
        GameBLL::instance()->shake(4);
    }
}

//获取播放播放动画状态
BaseActionObject::AnimateState BaseActionObject::getAnimateState(const std::string& animateName)
{
    AnimateState state=AnimateState::Static;
    auto iter=m_animateStates.find(animateName);
    if (iter!=m_animateStates.end()) {
        state=iter->second;
    }
    return state;
}

//播放动画
void BaseActionObject::playAnimate(const std::string& animateName)
{
    if (animateName=="null") {
        return;
    }
    auto iter=m_animateStates.find(animateName);
    if (iter==m_animateStates.end()) {
        m_animateStates.insert(std::make_pair(animateName, BaseActionObject::AnimateState::Runing));
    }else{
        iter->second=BaseActionObject::AnimateState::Runing;
    }
    
    //停止当前播放的动画
    std::string currPlayName=m_Armature->getAnimation()->getCurrentMovementID();
    if (currPlayName != animateName) {
        auto currAnimateIter=m_animateStates.find(currPlayName);
        if (currAnimateIter!=m_animateStates.end()) {
            currAnimateIter->second=BaseActionObject::AnimateState::Finish;
            lastPlayAnimateName=currPlayName;
        }
    }
    m_Armature->getAnimation()->play(animateName);
}

//每侦更新位置
void BaseActionObject::updatePosition(float ft)
{
    //计算操控行为的合力
    Vec2 steeringForce= m_steeringBehavior->calculate(ft);
    //加速度=力 / 质量
    Vec2 acceleration = steeringForce/m_dMass;
    //计算新位置
    auto currPos=getPosition()+ m_vVelocity + acceleration;
    //设置新位置
    setPosition(currPos);
    
    if (m_vVelocity.lengthSquared() > 0.0000001 ) {
        m_vHeading=m_vVelocity;
        m_vHeading.normalize();
        m_vSide=m_vHeading.getPerp();
    }
}

//被攻击
void BaseActionObject::beAttack(AttackObject *att)
{
    if (m_BodyState==GameEnum::BodyState::Die) {
        return;
    }
}

//待机闲置
void BaseActionObject::idleAnimate()
{
    changeState(GameEnum::BodyState::Idle, m_ActionFileModel->ActionIdle);
}

//跑动动画
void BaseActionObject::runAnimate()
{
    changeState(GameEnum::BodyState::Run, m_ActionFileModel->ActionRunName);
}

//死亡
void BaseActionObject::dieAnimate()
{
    changeState(GameEnum::BodyState::Die, m_ActionFileModel->ActionDie);
}

//设置骨骼方向
void BaseActionObject::setFacing(Vec2 facing)
{
    m_vHeading=facing;
    if (facing.x < 0) {
        m_Armature->setScaleX(-kScale);
    }else{
        m_Armature->setScaleX(kScale);
    }
}

//获取对象方向
bool BaseActionObject::getFacing()
{
    return m_Armature->getScaleX()==kScale;
}

//设置对象方向 sp:速度 p:力量(距离)
void BaseActionObject::addForce(float sp, float f)
{
    m_dAddSpeed=sp;
    m_dMaxForce+=f;
}

//设置对象加力 t:时间 f:力量(距离)
void BaseActionObject::addForceTime(float t,float f)
{
    m_dAddSpeed=f/t;
    m_dMaxForce=f;
}

//
//  HeroKnight.cpp
//  Zombie3_4
//  骑士英雄
//  Created by liuye on 15/9/9.
//
//

#include "HeroKnight.h"
#include "GameBLL.h"
#include "AttackObject.h"
#include "SoundBLL.h"
#include "SkillBLL.h"
#include "GameBLL.h"
#include "GameLayer.h"

//英雄基础类
HeroKnight::~HeroKnight()
{
    
}

//英雄基础类
HeroKnight::HeroKnight()
{
    //装载相应技能
    auto skillMode=new SkillBLL();
    skillMode->getHeroSkill(this, skills, 4);
    delete skillMode;
}

//普通攻击
std::string HeroKnight::commonAttack()
{
    m_vVelocity*=0.1;
    
    Vec2 diff=Vec2::ZERO;
    
    auto m_Armature=getArmature();
    std::string strAnimateName= m_Armature->getAnimation()->getCurrentMovementID();
    
    std::string strPlayName="";
    if (getAnimateState(getActionFileMode()->ActionAttackName1)==BaseActionObject::AnimateState::Runing) {
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.96) return getActionFileMode()->ActionAttackName1;
        strPlayName=getActionFileMode()->ActionAttackName2;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName2)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.94) return getActionFileMode()->ActionAttackName2;
        strPlayName=getActionFileMode()->ActionAttackName3;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName3)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.65) return getActionFileMode()->ActionAttackName3;
        strPlayName=getActionFileMode()->ActionAttackName4;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName4)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.99) return getActionFileMode()->ActionAttackName4;
        strPlayName=getActionFileMode()->ActionAttackName1;
    }else{
        strPlayName=getActionFileMode()->ActionAttackName1;
    }
    //log("strPlayName:%s",strPlayName.c_str());
    playAnimate(strPlayName);
    m_BodyState=GameEnum::BodyState::Attack;
    return strPlayName;
}

//播放动画
void HeroKnight::playAnimate(const std::string& animateName)
{
    HeroBase::playAnimate(animateName);
    if(animateName==m_ActionFileModel->SkillName1)
    {
        SoundBLL::getInstance()->playEffect(kHeroKnightSkill_1);
    }else if(animateName==m_ActionFileModel->SkillName2)
    {
        SoundBLL::getInstance()->playEffect(kHeroKnightSkill_2);
    }else if(animateName==m_ActionFileModel->SkillName3)
    {
        SoundBLL::getInstance()->playEffect(kHeroKnightSkill_3);
    }else if(animateName==m_ActionFileModel->SkillName4)
    {
        SoundBLL::getInstance()->playEffect(kHeroKnightSkill_4);
    }
}

AttackObject* HeroKnight::createAttackObject()
{
    std::string strAttID=getArmature()->getAnimation()->getCurrentMovementID();
    auto actionMode=getActionFileMode();
    //创建攻击对象
    int attack=getHeroModel()->Attack;
    auto att=AttackObject::create();
    att->setAttackObject(this);
    //默认是普通攻击距离
    float attDist=getHeroModel()->AttackDist;
    if (strAttID==actionMode->ActionAttackName1) {
        att->setRepelPower(20);
    }else if (strAttID==actionMode->ActionAttackName2) {
        att->setRepelPower(10);
    }else if (strAttID==actionMode->ActionAttackName3) {
        att->setRepelPower(35);
    }
    //技能攻击距离
    if (strAttID==actionMode->SkillName1){
        attDist=skills[0].AttackDist;
        //加血
        int addHp=skills[0].CurrAttack + attack / 4;
        HeroBase::addHp(addHp);
        
        return nullptr;
    }else if (strAttID==actionMode->SkillName2){
        attack=skills[1].CurrAttack + attack / 4;
        att->setRepelPower(180);
        attDist=skills[1].AttackDist;
    }else if (strAttID==actionMode->SkillName3){
        attack=skills[2].CurrAttack + attack / 4;
        att->setRepelPower(290);
        attDist=skills[2].AttackDist;
    }else if (strAttID==actionMode->SkillName4){
        attack=skills[3].CurrAttack + attack / 4;
        attDist=skills[3].AttackDist;
    }
    att->setAttack(attack);
    //攻击范围
    Vec2 pos=this->getPosition();
    
    float attStartPos=getPositionX();
    if (!getFacing()) {
        attStartPos-=attDist;
    }
    
    Rect attRect=Rect(attStartPos,getPositionY(),attDist, 200);
    att->setAttRange(attRect);
    
    return att;
}

//技能A动画
void HeroKnight::skillA()
{
    
}
//技能B动画
void HeroKnight::skillB()
{
    
}
//技能C动画
void HeroKnight::skillC()
{
    
}
//技能D动画
void HeroKnight::skillD()
{
    
}

void HeroKnight::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    HeroBase::movementEvent(armature, movementType, movementID);
    
    //移除英雄
    if (movementType==MovementEventType::COMPLETE || movementType==MovementEventType::LOOP_COMPLETE) {
        
    }
}

//事件回调
void HeroKnight::frameEvent(Bone *bone, const std::string& fn, int oi, int ci)
{
    HeroBase::frameEvent(bone, fn, oi, ci);
    
    if (fn.compare("move2")==0) {
        addForceTime(0.1,25);
    }else if (fn.compare("move3")==0) {
        addForceTime(0.1,25);
    }else if (fn.compare("move4")==0) {
        addForceTime(0.2,70);
    } if (fn.compare("move5")==0) { //技能移动
        addForceTime(0.1,170);
    }else if (fn.compare(m_ActionFileModel->FrameEventDownName)==0) {   //击倒 down
        //创建攻击对象
        auto att=createAttackObject();
        if (att) {
            //是否被击倒
            att->setIsHitDown(true);
            attackEvent(att);
        }
    }else if (fn.compare(m_ActionFileModel->FrameEventName)==0) {  //fire
        //创建攻击对象
        auto att=createAttackObject();
        if (att) {
            attackEvent(att);
        }
    }
}

//获取怪的状态数据
BTNodeInputData* HeroKnight::readBevNodeInputData()
{
    m_InputData=HeroBase::readBevNodeInputData();
    if (getAnimateState(getActionFileMode()->SkillName2)==AnimateState::Runing) {
        m_InputData->m_IsSkillMove=true;
    }else{
        m_InputData->m_IsSkillMove=false;
    }
    
    return m_InputData;
}
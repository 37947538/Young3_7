//
//  HeroAssassin.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/25.
//
//

#include "HeroAssassin.h"
#include "GameBLL.h"
#include "AttackObject.h"
#include "SoundBLL.h"
#include "SkillBLL.h"
#include "GameBLL.h"
#include "GameLayer.h"

//英雄基础类
HeroAssassin::~HeroAssassin()
{
    
}

//英雄基础类
HeroAssassin::HeroAssassin()
{
    //装载相应技能
    auto skillMode=new SkillBLL();
    skillMode->getHeroSkill(this, skills, 4);
    delete skillMode;
}

//普通攻击
std::string HeroAssassin::commonAttack()
{
    m_vVelocity*=0.1;
    
    Vec2 diff=Vec2::ZERO;
    
    auto m_Armature=getArmature();
    auto animate=m_Armature->getAnimation();
    auto str=animate->getCurrentMovementID();
    //log("str:%s",str.c_str());
    std::string strAnimateName= m_Armature->getAnimation()->getCurrentMovementID();

    std::string strPlayName="";
    if (getAnimateState(getActionFileMode()->ActionAttackName1)==BaseActionObject::AnimateState::Runing) {
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.9) return getActionFileMode()->ActionAttackName1;
        strPlayName=getActionFileMode()->ActionAttackName2;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName2)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.9) return getActionFileMode()->ActionAttackName2;
        strPlayName=getActionFileMode()->ActionAttackName3;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName3)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.9) return getActionFileMode()->ActionAttackName3;
        strPlayName=getActionFileMode()->ActionAttackName4;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName4)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.90) return getActionFileMode()->ActionAttackName4;
        strPlayName=getActionFileMode()->ActionAttackName5;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName5)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.99) return getActionFileMode()->ActionAttackName5;
        strPlayName=getActionFileMode()->ActionAttackName1;
    }else{
        strPlayName=getActionFileMode()->ActionAttackName1;
    }
    //log("strPlayName:%s",strPlayName.c_str());
    playAnimate(strPlayName);
    m_BodyState=GameEnum::BodyState::Attack;
    return strPlayName;
}
AttackObject* HeroAssassin::createAttackObject()
{
    std::string strAttID=getArmature()->getAnimation()->getCurrentMovementID();
    auto actionMode=getActionFileMode();
    
    //创建攻击对象
    int attack=getHeroModel()->Attack;
    auto att=AttackObject::create();
    att->setAttackObject(this);
    
    if (strAttID==actionMode->ActionAttackName1) {
        att->setRepelPower(25);
    }else if (strAttID==actionMode->ActionAttackName2) {
        att->setRepelPower(25);
    }else if (strAttID==actionMode->ActionAttackName3) {
        att->setRepelPower(100);
    }else if (strAttID==actionMode->ActionAttackName4) {
        att->setRepelPower(25);
    }else if (strAttID==actionMode->ActionAttackName5) {
        att->setRepelPower(35);
    }
    
    if (strAttID==actionMode->ActionAttackName1 || strAttID==actionMode->ActionAttackName2 || strAttID==actionMode->ActionAttackName3 || strAttID==actionMode->ActionAttackName4 || strAttID==actionMode->ActionAttackName5)
    {
        float attDist=getHeroModel()->AttackDist;
        float attStartPosX=getPositionX();
        if (!getFacing()) {
            attStartPosX-=attDist;
        }
        
        Rect attRect=Rect(attStartPosX, getPositionY(), attDist, 100);
        att->setAttRange(attRect);
    }
    if (strAttID==actionMode->SkillName1){
        attack=skills[0].CurrAttack + attack / 4;
        att->setRepelPower(20);
        float attDist=skills[0].AttackDist;
        float attStartPosX=getPositionX();
        if (!getFacing()) {
            attStartPosX-=attDist;
        }
        
        Rect attRect=Rect(attStartPosX, getPositionY(), attDist, 100);
        att->setAttRange(attRect);
    }else if (strAttID==actionMode->SkillName2){
        attack=skills[1].CurrAttack + attack / 4;
        att->setRepelPower(20);
        float attDist=skills[1].AttackDist;
        float attStartPosX=getPositionX() - (attDist / 2);
        Rect attRect=Rect(attStartPosX, getPositionY(), attDist, 100);
        att->setAttRange(attRect);
    }else if (strAttID==actionMode->SkillName3){
        attack=skills[2].CurrAttack + attack / 4;
        att->setRepelPower(255);
        float attDist=skills[2].AttackDist;
        float attStartPosX=getPositionX() - (attDist / 2);
        Rect attRect=Rect(attStartPosX, getPositionY(), attDist, 100);
        att->setAttRange(attRect);
    }else if (strAttID==actionMode->SkillName4){
        attack=skills[3].CurrAttack + attack / 4;
        att->setRepelPower(10);
        float attDist=skills[3].AttackDist;
        float attStartPosX=getPositionX();
        if (!getFacing()) {
            attStartPosX-=attDist;
        }
        Rect attRect=Rect(attStartPosX, getPositionY(), attDist, 100);
        att->setAttRange(attRect);
    }
    att->setAttack(attack);
    
    return att;
}
//技能A动画
void HeroAssassin::skillA()
{
    
}
//技能B动画
void HeroAssassin::skillB()
{
    
}
//技能C动画
void HeroAssassin::skillC()
{
    
}
//技能D动画
void HeroAssassin::skillD()
{
    
}
void HeroAssassin::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    HeroBase::movementEvent(armature, movementType, movementID);
    
    if (movementType==MovementEventType::COMPLETE || movementType==MovementEventType::LOOP_COMPLETE) {
        if(movementID==getActionFileMode()->SkillName4){
            if (getMainHero()) {
                setShadowVisible(true);
            }else{
                setHpBarVisible(true);
            }
        }else if (movementID==getActionFileMode()->SkillName1){
            if (getMainHero()) {
                GameBLL::instance()->setViewScreeCenter();
            }            
        }
    }
}
//事件回调
void HeroAssassin::frameEvent(Bone *bone, const std::string& fn, int oi, int ci)
{
    HeroBase::frameEvent(bone, fn, oi, ci);
    
    if (fn.compare("move1")==0) {
        addForceTime(0.1,25);
    }else if (fn.compare("move2")==0) {
        addForceTime(0.1,35);
    }else if (fn.compare("move3")==0) {
        addForceTime(0.1,100);
    }else if (fn.compare("move4")==0) {
        addForceTime(0.3,500);
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

//播放动画
void HeroAssassin::playAnimate(const std::string& animateName)
{
    HeroBase::playAnimate(animateName);
    if (animateName==m_ActionFileModel->ActionAttackName1) {
        SoundBLL::getInstance()->playEffect("sound/h1/A1.mp3");
    }else if (animateName==m_ActionFileModel->ActionAttackName2){
        SoundBLL::getInstance()->playEffect("sound/h1/A2.mp3");
    }else if (animateName==m_ActionFileModel->ActionAttackName3){
        SoundBLL::getInstance()->playEffect("sound/h1/A3.mp3");
    }else if (animateName==m_ActionFileModel->ActionAttackName4){
        SoundBLL::getInstance()->playEffect("sound/h1/A4.mp3");
    }else if(animateName==m_ActionFileModel->ActionRunName)
    {
        static int i=0;
        if (i%2==0) {
            SoundBLL::getInstance()->playEffect("sound/h3/step1.mp3");
        }else
        {
            SoundBLL::getInstance()->playEffect("sound/h3/step2.mp3");
        }
        i++;
    }else if(animateName==m_ActionFileModel->ActionBeAttack1)
    {
        SoundBLL::getInstance()->playEffect("sound/h3/Q.mp3");
    }else if(animateName==m_ActionFileModel->ActionDie)
    {
        SoundBLL::getInstance()->playEffect("sound/h3/Die.mp3");
    }else if(animateName==m_ActionFileModel->SkillName1)
    {
        SoundBLL::getInstance()->playEffect(kHeroAssassinSkill_1);
    }else if(animateName==m_ActionFileModel->SkillName2)
    {
        SoundBLL::getInstance()->playEffect(kHeroAssassinSkill_2);
    }else if(animateName==m_ActionFileModel->SkillName3)
    {
        SoundBLL::getInstance()->playEffect(kHeroAssassinSkill_3);
    }else if(animateName==m_ActionFileModel->SkillName4)
    {
        SoundBLL::getInstance()->playEffect(kHeroAssassinSkill_4);
        if (getMainHero()) {
            setShadowVisible(false);
        }else{
            setHpBarVisible(false);
        }
    }
}

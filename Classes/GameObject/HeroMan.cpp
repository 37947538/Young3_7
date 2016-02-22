//
//  HeroMan.cpp
//  Zombie3_4
//  战士
//  Created by jl on 15/8/17.
//
//

#include "HeroMan.h"
#include "GameBLL.h"
#include "AttackObject.h"
#include "SoundBLL.h"
#include "SkillBLL.h"
#include "GameBLL.h"
#include "GameLayer.h"

//英雄基础类
HeroMan::~HeroMan()
{
    
}

//英雄基础类
HeroMan::HeroMan()
{
    //装载相应技能
    auto skillMode=new SkillBLL();
    skillMode->getHeroSkill(this, skills, 4);
    delete skillMode;
}

//普通攻击
std::string HeroMan::commonAttack()
{
    m_vVelocity*=0.1;
    
    Vec2 diff=Vec2::ZERO;

    auto m_Armature=getArmature();
    std::string strAnimateName=m_Armature->getAnimation()->getCurrentMovementID();
    
    std::string strPlayName="";
    if (getAnimateState(getActionFileMode()->ActionAttackName1)==BaseActionObject::AnimateState::Runing) {
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.6) return getActionFileMode()->ActionAttackName1;
        strPlayName=getActionFileMode()->ActionAttackName2;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName2)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.4) return getActionFileMode()->ActionAttackName2;
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
void HeroMan::playAnimate(const std::string& animateName)
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
            SoundBLL::getInstance()->playEffect("sound/h1/step1.mp3");
        }else
        {
            SoundBLL::getInstance()->playEffect("sound/h1/step2.mp3");
        }
        i++;
    }else if(animateName==m_ActionFileModel->ActionBeAttack1)
    {
        SoundBLL::getInstance()->playEffect("sound/h1/Q.mp3");
    }else if(animateName==m_ActionFileModel->ActionDie)
    {
        SoundBLL::getInstance()->playEffect("sound/h1/Die.mp3");
    }else if(animateName==m_ActionFileModel->SkillName1)
    {
        SoundBLL::getInstance()->playEffect(kHeroManSkill_1);
    }else if(animateName==m_ActionFileModel->SkillName2)
    {
        SoundBLL::getInstance()->playEffect(kHeroManSkill_2);
    }else if(animateName==m_ActionFileModel->SkillName3)
    {
        SoundBLL::getInstance()->playEffect(kHeroManSkill_3);
    }else if(animateName==m_ActionFileModel->SkillName4)
    {
        SoundBLL::getInstance()->playEffect(kHeroManSkill_4);
    }
}

AttackObject* HeroMan::createAttackObject()
{
    std::string strAttID=getArmature()->getAnimation()->getCurrentMovementID();
    auto actionMode=getActionFileMode();
    //攻击力
    int attack=getHeroModel()->Attack;
    //创建攻击对象
    auto att=AttackObject::create();
    att->setAttackObject(this);
    //默认是普通攻击距离
    float attDist=getHeroModel()->AttackDist;
    if (strAttID==actionMode->ActionAttackName2) {
        att->setRepelPower(25.0);
    }else if (strAttID==actionMode->ActionAttackName3) {
        att->setRepelPower(70.0);
    }else if (strAttID==actionMode->ActionAttackName4) {
        att->setRepelPower(25.0);
    }
    //技能攻击距离
    if (strAttID==actionMode->SkillName1){
        attack=skills[0].CurrAttack + attack / 4;
        attDist=skills[0].AttackDist;
    }else if (strAttID==actionMode->SkillName2){
        attack=skills[1].CurrAttack + attack / 4;
        att->setRepelPower(175.0);
        attDist=skills[1].AttackDist;
    }else if (strAttID==actionMode->SkillName3){
        attack=skills[2].CurrAttack + attack / 4;
        att->setRepelPower(180.0);
        attDist=skills[2].AttackDist;
    }else if (strAttID==actionMode->SkillName4){
        attack=skills[3].CurrAttack + attack / 4;
        att->setRepelPower(120.0);
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
void HeroMan::skillA()
{
    
}
//技能B动画
void HeroMan::skillB()
{
    
}
//技能C动画
void HeroMan::skillC()
{
    
}
//技能D动画
void HeroMan::skillD()
{
    
}

void HeroMan::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    HeroBase::movementEvent(armature, movementType, movementID);
    
    //移除英雄
    if (movementType==MovementEventType::COMPLETE || movementType==MovementEventType::LOOP_COMPLETE) {
        
    }
}

//事件回调
void HeroMan::frameEvent(Bone *bone, const std::string& fn, int oi, int ci)
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
        /*
        auto n=bone->getBoneData()->name;
        auto attRect=bone->getDisplayManager()->getBoundingBox();
        log("-----------name[%s]rect[%f,%f,%f,%f]",n.c_str(),attRect.origin.x,attRect.origin.y,attRect.size.width,attRect.size.height);
        attRect.origin.x+=getPosition().x;
        attRect.origin.y+=getPosition().y;
        log("+++++++++++name[%s]rect[%f,%f,%f,%f]",n.c_str(),attRect.origin.x,attRect.origin.y,attRect.size.width,attRect.size.height);
         */
        //创建攻击对象
        auto att=createAttackObject();
        if (att) {
            attackEvent(att);
        }
    }
}

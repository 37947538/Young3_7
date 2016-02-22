//
//  HeroBow.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/17.
//
//

#include "HeroBow.h"
#include "GameBLL.h"
#include "BulletObject.h"
#include "SoundBLL.h"
#include "SkillBLL.h"
#include "BulletBLL.h"

#define kShootPosY      100   //正常射击位置
#define kDownShootPosY   71   //蹲下射击
#define kFinishShootPosY 82   //最后一下射击位置

//英雄基础类
HeroBow::~HeroBow()
{
    
}

//英雄基础类
HeroBow::HeroBow()
{
    //装载相应技能
    auto skillMode=new SkillBLL();
    skillMode->getHeroSkill(this, skills, 4);
    delete skillMode;
}
//普通攻击
std::string HeroBow::commonAttack()
{
    m_vVelocity*=0.1;
    
    Vec2 diff=Vec2::ZERO;
    
    auto m_Armature=getArmature();
    std::string strAnimateName= m_Armature->getAnimation()->getCurrentMovementID();
    
    std::string strPlayName="";
    if (getAnimateState(getActionFileMode()->ActionAttackName1)==BaseActionObject::AnimateState::Runing) {
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.6) return getActionFileMode()->ActionAttackName1;
        strPlayName=getActionFileMode()->ActionAttackName2;
        vShootPos.y=kDownShootPosY;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName2)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.6) return getActionFileMode()->ActionAttackName2;
        strPlayName=getActionFileMode()->ActionAttackName3;
        vShootPos.y=kShootPosY;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName3)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.6) return getActionFileMode()->ActionAttackName3;
        strPlayName=getActionFileMode()->ActionAttackName4;
        vShootPos.y=kFinishShootPosY;
    }else if(getAnimateState(getActionFileMode()->ActionAttackName4)==BaseActionObject::AnimateState::Runing){
        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
        if (currPercent < 0.99) return getActionFileMode()->ActionAttackName4;
        strPlayName=getActionFileMode()->ActionAttackName1;
        vShootPos.y=kShootPosY;
    }else{
        strPlayName=getActionFileMode()->ActionAttackName1;
        vShootPos.y=kShootPosY;
    }
    playAnimate(strPlayName);
    m_BodyState=GameEnum::BodyState::Attack;
    return strPlayName;
}
//播放动画
void HeroBow::playAnimate(const std::string& animateName)
{
    HeroBase::playAnimate(animateName);
    
    if (animateName.compare(getActionFileMode()->ActionAttackName1)==0){
        vShootPos.y=kShootPosY;
    }else if(animateName.compare(getActionFileMode()->ActionAttackName2)==0){
        vShootPos.y=kDownShootPosY;
    }else if(animateName.compare(getActionFileMode()->ActionAttackName3)==0){
        vShootPos.y=kShootPosY;
    }else if(animateName.compare(getActionFileMode()->ActionAttackName4)==0){
        vShootPos.y=kFinishShootPosY;
    }else{
        vShootPos.y=kShootPosY;
    }
    
    if (animateName==m_ActionFileModel->ActionAttackName1) {
        SoundBLL::getInstance()->playEffect("sound/h2/A1.mp3");
    }else if (animateName==m_ActionFileModel->ActionAttackName2){
        SoundBLL::getInstance()->playEffect("sound/h2/A1.mp3");
    }else if (animateName==m_ActionFileModel->ActionAttackName3){
        SoundBLL::getInstance()->playEffect("sound/h2/A1.mp3");
    }else if (animateName==m_ActionFileModel->ActionAttackName4){
        SoundBLL::getInstance()->playEffect("sound/h2/A4.mp3");
    }else if(animateName==m_ActionFileModel->ActionRunName)
    {
        static int i=0;
        if (i%2==0) {
            SoundBLL::getInstance()->playEffect("sound/h2/step1.mp3");
        }else
        {
            SoundBLL::getInstance()->playEffect("sound/h2/step2.mp3");
        }
        i++;
    }else if(animateName==m_ActionFileModel->ActionBeAttack1)
    {
        SoundBLL::getInstance()->playEffect("sound/h2/Q.mp3");
    }else if(animateName==m_ActionFileModel->ActionDie)
    {
        SoundBLL::getInstance()->playEffect("sound/h2/Die.mp3");
    }else if(animateName==m_ActionFileModel->SkillName1)
    {
        SoundBLL::getInstance()->playEffect(kHeroBowSkill_1);
    }else if(animateName==m_ActionFileModel->SkillName2)
    {
        SoundBLL::getInstance()->playEffect(kHeroBowSkill_2);
    }else if(animateName==m_ActionFileModel->SkillName3)
    {
        SoundBLL::getInstance()->playEffect(kHeroBowSkill_3);
    }else if(animateName==m_ActionFileModel->SkillName4)
    {
        SoundBLL::getInstance()->playEffect(kHeroBowSkill_4);
    }
}

AttackObject* HeroBow::createAttackObject()
{
    std::string strAttID=getArmature()->getAnimation()->getCurrentMovementID();
    auto actionMode=getActionFileMode();
    //获取方向
    bool facing=getFacing();
    float attackDist=getHeroModel()->AttackDist;      //攻击距离

    //创建子弹
    auto bullet=BulletObject::create();
    bullet->setAttackType(1);
    bullet->setAttackObject(this);
    
    if (strAttID==actionMode->ActionAttackName1 || strAttID==actionMode->ActionAttackName2 || strAttID==actionMode->ActionAttackName3 || strAttID==actionMode->ActionAttackName4)
    {
        bullet->setRepelPower(8.0);
        float bulletX=GameBLL::instance()->getMaxMapWidth();
        if(!facing){
            bulletX*=-1;
        }
        auto b=Sprite::createWithSpriteFrameName("v_arrow_1.png");
        b->setFlippedX(!facing);
        bullet->setSprite(b);
        bullet->setPosition(getPosition()+vShootPos);
        bullet->setTargetPos(getPosition()+Vec2(bulletX,vShootPos.y), 3000);
        bullet->setAttack(getHeroModel()->Attack);
        BulletBLL::getInstance()->addBullet(bullet);
    }
    //技能1
    if (strAttID==actionMode->SkillName1) {
        bullet->setPenetrateAttack(true);
        bullet->setRepelPower(32);
        attackDist=skills[0].AttackDist;
        
        float width=1280.0;
        float rota=21.24;   //旋转角度
        if(!facing){
            attackDist*=-1;
            rota*=-1;
            width*=-1;
        }
        auto bulletStartPos=getPosition() + Vec2(0, 255);
        auto b=Sprite::createWithSpriteFrameName("v_arrow_2.png");
        b->setFlippedX(!facing);
        bullet->setSprite(b);
        bullet->setPosition(bulletStartPos);
        //bullet->setTargetPos(pos+Vec2(attackDist,0), 2000);
        bullet->setIsDone(true);
        bullet->setRotation(rota);
        int attack=skills[0].CurrAttack + getHeroModel()->Attack / 4;
        bullet->setAttack(attack);
        BulletBLL::getInstance()->addBullet(bullet);
        
        auto call=CallFunc::create(CC_CALLBACK_0(HeroBow::bulletCallback, this, bullet));
        ccBezierConfig bc;
        bc.endPosition=Vec2(bulletStartPos.x + width, bulletStartPos.y);
        
        if(!facing){
            bc.controlPoint_1 = Vec2(bulletStartPos.x - width * 0.2, bulletStartPos.y - 300);
            bc.controlPoint_2 = Vec2(bc.endPosition.x + width * 0.2, bulletStartPos.y - 300);
        }else{
            bc.controlPoint_1 = Vec2(bulletStartPos.x + width * 0.2, bulletStartPos.y - 300);
            bc.controlPoint_2 = Vec2(bc.endPosition.x - width * 0.2, bulletStartPos.y - 300);
        }
        //子弹动作
        auto bez=BezierTo::create(0.5, bc);
        auto seq=Sequence::create(bez,call, NULL);
        bullet->runAction(APRotateWithAction::create(seq));
        
    }else if (strAttID==actionMode->SkillName2){
        float bAngle=345;
        if(!facing){
            bAngle=215;
        }
        auto bulletPos=getPosition() + Vec2(0, 272);
        int attack=skills[1].CurrAttack + getHeroModel()->Attack / 4;
        for (int i=0; i<3; i++) {
            auto targetPos=APTools::getRoundPoint(bulletPos, bAngle - (i * 10), 1700);
            float rotation=APTools::getAngle(bulletPos, targetPos);
            auto b=Sprite::createWithSpriteFrameName("v_arrow_3.png");
            b->setFlippedX(!facing);
            
            //创建子弹
            auto newbullet=BulletObject::create();
            newbullet->setRepelPower(8.0);
            newbullet->setAttackType(1);
            newbullet->setPenetrateAttack(true);
            newbullet->setAttackObject(this);
            newbullet->setSprite(b);
            newbullet->setPosition(bulletPos);
            newbullet->setTargetPos(targetPos, 2000);
            newbullet->setRotation(rotation);
            newbullet->setAttack(attack);
            BulletBLL::getInstance()->addBullet(newbullet);

        }
    }else if (strAttID==actionMode->SkillName3){
        attackDist=skills[2].AttackDist;
        //创建攻击对象
        int attack=skills[2].CurrAttack + getHeroModel()->Attack / 4;
        auto att=AttackObject::create();
        att->setAttack(attack);
        att->setRepelPower(280);
        att->setAttackObject(this);
        //是否被击倒
        att->setIsHitDown(true);
        //攻击范围
        Vec2 pos=this->getPosition();
        float attStartPosX=getPositionX();
        if (!facing) {
            attStartPosX-=attackDist;
        }
        
        Rect attRect=Rect(attStartPosX,getPositionY(),attackDist, 100);
        att->setAttRange(attRect);
        return att;
        
    }else if (strAttID==actionMode->SkillName4){
        attackDist=skills[3].AttackDist;
        //创建攻击对象
        int attack=skills[3].CurrAttack + getHeroModel()->Attack / 4;
        auto att=AttackObject::create();
        att->setAttack(attack);
        att->setRepelPower(120);
        att->setAttackObject(this);
        //是否被击倒
        att->setIsHitDown(false);
        //攻击范围
        Vec2 pos=this->getPosition();
        auto worldPos=this->getParent()->convertToWorldSpace(pos);
        float attDist=1280-worldPos.x;
        float attStartPosX=pos.x;
        if (!facing) {
            attDist=worldPos.x;
            attStartPosX-=attDist;
        }
        
        Rect attRect=Rect(attStartPosX,getPositionY(),attDist, 100);
        att->setAttRange(attRect);
        
        return att;
    }
    
    return nullptr;
}

//技能A动画
void HeroBow::skillA()
{
    if (getMainHero()) {
        GameBLL::instance()->setViewScreeCenter();
    }    
}
//技能B动画
void HeroBow::skillB()
{
    
}
//技能C动画
void HeroBow::skillC()
{
    
}
//技能D动画
void HeroBow::skillD()
{
    
}
//事件回调
void HeroBow::frameEvent(Bone *bone, const std::string& fn, int oi, int ci)
{
    HeroBase::frameEvent(bone, fn, oi, ci);
    
    if (fn.compare("move1")==0) {
        addForceTime(0.2,-150);
    }else if (fn.compare("move2")==0) {
        addForceTime(0.2,-70);
    }else if (fn.compare("move3")==0) {
        //addForceTime(0.1,25);
    }else if (fn.compare("move4")==0) {
        addForceTime(0.15,-70);
    } if (fn.compare("move5")==0) { //技能移动
        //addForceTime(0.1,170);
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

void HeroBow::bulletCallback(Ref* sender)
{
    auto bullet=(BulletObject*)sender;
    bullet->executeCallback();
}
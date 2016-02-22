/**
 k_ClassDes
 */

#include "EnemyBase.h"
#include "EnemyModel.h"
#include "EnemyAI.h"
#include "APShader.h"
#include "EnemyBevTreeData.h"
#include "GameBLL.h"
#include "GameLayer.h"
#include "APScatterAction.h"
#include "APTools.h"
#include "EffectBLL.h"
#include "SoundBLL.h"
#include "UpgradeSystem.h"

#define kAttackSoundPath(i) __String::createWithFormat("sound/enemy_%d_attack.mp3",i)
#define kBeAttackSoundPath(i) __String::createWithFormat("sound/enemy_%d_beattack.mp3",i)

//敌兵
EnemyBase::~EnemyBase()
{
    delete m_EnemyModel;
    delete m_EnemyAI;
}

//敌兵
EnemyBase::EnemyBase()
{
    m_EnemyAI=new EnemyAI(this);
    m_EnemyModel=new EnemyModel();
}

void EnemyBase::update(float ft)
{
    if (m_BodyState==GameEnum::BodyState::Die) {
        return;
    }
    
    m_EnemyAI->update(ft);
}

//敌兵数据
void EnemyBase::loadData(EnemyModel* arg1)
{
    memcpy(m_EnemyModel,arg1,sizeof(EnemyModel));
    loadActionFile(arg1->ActionFileModelID);
    //敌兵的方向
    m_vHeading=Vec2(1,0);
    m_dMaxSpeed=m_EnemyModel->SpeedValue;
    
    //敌兵数值计算
    UpgradeSystem::setEnemyLv(m_EnemyModel->LV - 1, m_EnemyModel);
    
    //获取血条高度
    hpPos=PointFromString(m_EnemyModel->HpPosition);
    //血条
    m_HealthBar=HealthBarCompoment::create("imgs/xuetiao_beijing.png", "imgs/guaiwu_xuetiao.png", "imgs/guaiwu_xuetiao_2.png");
    m_HealthBar->setPosition(hpPos);
    //m_HealthBar->setVisible(false);
    getArmature()->addChild(m_HealthBar,100);
    
    getArmature()->getAnimation()->setSpeedScale(1+CCRANDOM_0_1());

    //加载阴影
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("guge/anxt_effect_10.plist");
    m_Shadow=Sprite::createWithSpriteFrameName("n_shadow_1.png");
    m_Shadow->setPosition(Vec2(0,-10));
    this->addChild(m_Shadow);
    
    auto hpSize=m_HealthBar->getContentSize();
    m_HealthBar->setScaleX(m_EnemyModel->HpBarWidth / hpSize.width);
    
    m_EnemyAI->createBevTree();
    
    //随机攻击距离
    m_InputData->m_iAttackDist=getEnemyModel()->AttackDist-(CCRANDOM_0_1()*30+20);
    //设置品质特效
    setQualityEffect();
    //敌兵信息
    showEnemyInfo();
}

//放在游戏中
void EnemyBase::puton(Vec2 pos)
{
    setPosition(pos);
    m_BevOutData->m_NextPosition=pos;
}

//怪被攻击
void EnemyBase::beAttack(AttackObject *att)
{
    if (m_BodyState==GameEnum::BodyState::Die) {
        return;
    }
    
    //被攻击声音
    SoundBLL::getInstance()->playEffect(kBeAttackSoundPath(m_EnemyModel->EnemyID)->getCString());
    
    //颤屏
    GameBLL::instance()->shake(0.3, 8, 8);
    
    m_BeAttackFlyPower=att->getRepelPower();
    //BOSS霸体－待机、走路、的时候才播放被攻击动画
    bool isPaBody=false;
    if (m_BodyState==GameEnum::BodyState::Attack && m_EnemyModel->EnemyType==2) {
        isPaBody=true;
    }
    if (!isPaBody) {
        //播放攻击动画
        if (att->getIsHitDown()) {
            //已经是被击倒
            if (m_BodyState!=GameEnum::BodyState::Down) {
                changeState(GameEnum::BodyState::Down, m_ActionFileModel->ActionBeAttackDown);
            }
        }else{
            //被击倒状态不播放其他被击动画
            if (m_BodyState!=GameEnum::BodyState::Down) {
                std::string animateName=m_ActionFileModel->ActionBeAttack1;
                
                if (CCRANDOM_0_1() > 0.5 && m_EnemyModel->EnemyQuality==0) {
                    animateName=m_ActionFileModel->ActionBeAttack2;
                }
                changeState(GameEnum::BodyState::BeAttack, animateName);
            }
        }
    }
    
    //改变阴影
    onShaderChange(GameEnum::EnemyEvent::EventChangeShaderBeAttackShader);
    //特效
    EffectBLL::getInstance()->addEnemyEffect(this,att);    
    //扣血
    subBlood(att->getAttack());
}

void EnemyBase::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    BaseActionObject::movementEvent(armature, movementType, movementID);
    if (movementType==MovementEventType::COMPLETE || movementType==MovementEventType::LOOP_COMPLETE) {
       
    }
}

void EnemyBase::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    //攻击判定
    if (frameEventName.compare(m_ActionFileModel->FrameEventName)==0) {
        //被攻击声音
        SoundBLL::getInstance()->playEffect(kAttackSoundPath(m_EnemyModel->EnemyID)->getCString());
        
        auto attackObj=createAttackObject();
        if (attackObj) {
            GameBLL::instance()->attackForEnemy(attackObj);
        }
    }else if (frameEventName.compare(m_ActionFileModel->FrameEventDownName)==0) {
        //被攻击声音
        SoundBLL::getInstance()->playEffect(kAttackSoundPath(m_EnemyModel->EnemyID)->getCString());
        
        auto attackObj=createAttackObject();
        if (attackObj) {
            attackObj->setIsHitDown(true);
            GameBLL::instance()->attackForEnemy(attackObj);
        }
    }
    //移动
    auto loc = frameEventName.find("move{");
    if(loc != std::string::npos){
        std::string posString=frameEventName.substr(loc+4, frameEventName.length());
        auto pos=PointFromString(posString);
        //addForceTime(pos.x,pos.y);
    }
}

AttackObject* EnemyBase::createAttackObject()
{
    //创建攻击对象
    auto att=AttackObject::create();
    att->setAttackObject(this);
    
    //是否被击倒
    att->setIsHitDown(false);
    
    //攻击范围
    Vec2 pos=this->getPosition();
    float attDist=getEnemyModel()->AttackDist;
    float attStartPos=getPositionX();
    if (!getFacing()) {
        attStartPos-=attDist;
    }
    
    Rect attRect=Rect(attStartPos,getPositionY(),attDist, 100);
    att->setAttRange(attRect);
    
    return att;
}

//动画播放完成
void EnemyBase::animateFinish(const std::string& name)
{
    BaseActionObject::animateFinish(name);
    
    if (name==getActionFileMode()->ActionDie) {
        m_BodyState=GameEnum::BodyState::Die;
        getArmature()->getAnimation()->stop();
        GameBLL::instance()->removeEnemy(this);
    }
}

//扣血值
void EnemyBase::subBlood(int iBeAttack)
{
    //log("Enemy::subHp(%f,%d,%d)",subHp,m_State,m_EnemyModel->CurrHP);
    if (m_BodyState==GameEnum::BodyState::Die) {
        return;
    }
    
    int enemyDef=m_EnemyModel->ArmorValue;
    //伤害 = 攻击方攻击力*(1-（挨打方防御力*0.05/（0.05*挨打方防御力+1））)+攻击方攻击力*0.025
    int attackResult=iBeAttack * (1 - (enemyDef * 0.05 / (0.05 * enemyDef + 1))) + iBeAttack * 0.025;
    int randAttack=attackResult * APTools::getRandFloat(-0.1, 0.1);
    attackResult+=randAttack;
    m_EnemyModel->CurrHp-=attackResult;
    
    float percent=getHpPercent();
    m_HealthBar->setHpPercentage(percent);
    
    if (m_EnemyModel->CurrHp > 0) {
        //m_HealthBar->stopAllActions();
        //m_HealthBar->runAction(Sequence::create(Show::create(),DelayTime::create(3.0),Hide::create(), NULL));
        
        //播放掉血数字
        int orderZ=getLocalZOrder();
        Vec2 vPos=getPosition();
        auto ggl=GameBLL::instance()->m_GameLayer;
        ggl->subCurrHp(vPos,20,attackResult,orderZ);
    }
    if (m_EnemyModel->CurrHp <= 0) {
        die();
    }
}

//获取hp百分比
float EnemyBase::getHpPercent()
{
    float percent=((float)m_EnemyModel->CurrHp / (float)m_EnemyModel->MaxHp) * 100.0;
    percent = percent < 0.0f ? 0.0f : percent;
    return percent;
}

//怪死亡
void EnemyBase::die()
{
    changeState(GameEnum::BodyState::Die, getActionFileMode()->ActionDie);
    m_HealthBar->setVisible(false);
    GameBLL::instance()->enemyWillDie(this);
    
    EffectBLL::getInstance()->addEffect(this, "effect_22", Vec2(0, 0));
    //获得所有骨骼，也就是编辑器中的layer
    auto& map = m_Armature->getBoneDic();
    for (auto& entry : map){
        auto bone = entry.second;
        if (bone){
            float height = APTools::getRandFloat(300,550);
            auto apscatt = APScatterAction::create(height, 300, 400, 0.2);
            auto seq = Sequence::create(apscatt, Blink::create(1, 16), NULL);
            bone->runAction(seq);
        }
    }
}

//获取怪的状态数据
BTNodeInputData* EnemyBase::readBevNodeInputData()
{
    Vec2 currPos=getPosition();
    Vec2 targePos=getPosition();
    if(GameBLL::instance()->vectorHero.size() > 0)
    {
        targePos=GameBLL::instance()->vectorHero.at(0)->getPosition();
        float minDistance=currPos.distance(targePos);
        for (auto &hero : GameBLL::instance()->vectorHero) {
            auto heroPos=hero->getPosition();
            float currDistance=currPos.distance(heroPos);
            if (currDistance<minDistance) {
                targePos=heroPos;
                minDistance=currDistance;
            }
        }
    }
    m_InputData->m_IsMainHero=false;
    m_InputData->m_PlayerControl=nullptr;
    m_InputData->m_Owner=this;
    m_InputData->m_OwnerState=m_BodyState;
    m_InputData->m_RunMoveSpeed=getEnemyModel()->SpeedValue;
    m_InputData->m_CurrPosition2D=currPos;
    m_InputData->m_TargetPosition2D=targePos;
    m_InputData->m_BeAttackFlyPower=m_BeAttackFlyPower;
    m_InputData->m_MapMoveWidth=GameBLL::instance()->m_GameLayer->getMapMoveWidth();
    
    return m_InputData;
}

//更新英雄输出数据
void EnemyBase::updateAIOutData(BTNodeOutputData *data)
{
    m_vVelocity=data->m_vVelocity;
    setFacing(data->m_NextFacing);
    m_InputData->m_CurrentFacing=data->m_NextFacing;
    
    if (data->m_NextPosition!=Vec2::ZERO) {
        setPosition(data->m_NextPosition);
    }
    
    while (!data->m_OutEvent.empty()) {
        auto event=data->m_OutEvent.front();
        switch (event->getBaseActionEvent()) {
            case GameEnum::BaseActionEventType::PlayAnimate:                    //播放动画
            {
                auto animateName=(__String*)event->getEventArg();
                changeState(event->getEventBodyState(), animateName->getCString());
            }break;
            case GameEnum::BaseActionEventType::BeAttack:                       //被攻击
            {
                auto hero=(HeroBase*)event->getEventArg();
                //subBlood(hero);
            }break;
            case GameEnum::BaseActionEventType::ChangeStateIdle:                //切换空闲状态
            {
                idleAnimate();
            }break;
            case GameEnum::BaseActionEventType::ChangeShaderBeAttackShader:    //切换被打特效
            {
                onShaderChange(GameEnum::EnemyEvent::EventChangeShaderBeAttackShader);
            }break;
             default:
                  break;
            }
            //销毁事件
            data->m_OutEvent.eraseObject(event);
    }
}

//被击倒
void EnemyBase::beAttackKnowAnimate()
{
    m_Armature->getAnimation()->play(m_ActionFileModel->ActionBeAttackDown);
}

//切换shader状态
void EnemyBase::onShaderChange(GameEnum::EnemyEvent newState)
{
    auto callShaderFunc=[=]()
    {
        APShader::addShaderArmature(m_Armature, "shader/gold.fsh");
    };
    auto callShader=CallFunc::create(callShaderFunc);
    auto normalShaderFunc=[=]()
    {
        APShader::addShaderArmature(m_Armature, "shader/reset.fsh");
    };
    auto normalShader=CallFunc::create(normalShaderFunc);
    
    auto seq=Sequence::create(callShader,DelayTime::create(0.1),normalShader, NULL);
    m_Armature->runAction(seq);
}

//获取碰撞矩形
APOBB* EnemyBase::getOBB()
{
    float fWidht=62;
    float fHeight=hpPos.y;
    Vec2 pos=this->getPosition();
    auto rect=Rect(pos.x-fWidht*0.5, pos.y, fWidht, fHeight);
    
    Vec2 pt = Vec2(rect.origin.x,rect.origin.y);
    m_obb->setVertex(0, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x+rect.size.width,rect.origin.y);
    m_obb->setVertex(1, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height);
    m_obb->setVertex(2, pt.x, pt.y);
    
    pt = Vec2(rect.origin.x,rect.origin.y+rect.size.height);
    m_obb->setVertex(3, pt.x, pt.y);
    //获取obb
    return m_obb;
}

//设置品质特效
void EnemyBase::setQualityEffect()
{
    auto effectSprite=Sprite::createWithSpriteFrameName("effect_9_1.png");
    effectSprite->setLocalZOrder(kGameTopZ);
    effectSprite->setPosition(aprateccp(m_Shadow, 0.5, 0.87));
    
    if (m_EnemyModel->EnemyQuality==1) {
        effectSprite->setColor(Color3B(160, 63, 205));
        m_Shadow->addChild(effectSprite);
    }else if (m_EnemyModel->EnemyQuality==2){
        effectSprite->setColor(Color3B(238, 0, 0));
        m_Shadow->addChild(effectSprite);
    }
}
//设置血条显示隐藏
void EnemyBase::setHpBarVisible(bool bVisible)
{
    m_HealthBar->setVisible(bVisible);
}
//设置阴影显示隐藏
void EnemyBase::setShadowVisible(bool bVisible)
{
    m_Shadow->setVisible(bVisible);
}
//显示敌兵信息
void EnemyBase::showEnemyInfo()
{
    if (kIsPayTest) {
        return;
    }
    //敌兵信息-等级，攻击力，血量，经验
    auto pos=m_HealthBar->getPosition();
    //攻击力
    auto atkLabel=Label::create();
    atkLabel->setString(__String::createWithFormat("攻击力:%d",m_EnemyModel->Attack)->getCString());
    atkLabel->setColor(Color3B::RED);
    atkLabel->setSystemFontSize(20);
    atkLabel->setAnchorPoint(Vec2(0, 0.5));
    atkLabel->setPosition(pos+Vec2(-50, 20));
    this->addChild(atkLabel);
    //血量
    auto hpLabel=Label::create();
    hpLabel->setString(__String::createWithFormat("血量:%d",m_EnemyModel->CurrHp)->getCString());
    hpLabel->setColor(Color3B::RED);
    hpLabel->setSystemFontSize(20);
    hpLabel->setAnchorPoint(Vec2(0, 0.5));
    hpLabel->setPosition(pos+Vec2(-50, 40));
    this->addChild(hpLabel);
    //经验
    auto expLabel=Label::create();
    expLabel->setString(__String::createWithFormat("经验:%d",m_EnemyModel->DropExp)->getCString());
    expLabel->setColor(Color3B::RED);
    expLabel->setSystemFontSize(20);
    expLabel->setAnchorPoint(Vec2(0, 0.5));
    expLabel->setPosition(pos+Vec2(-50, 60));
    this->addChild(expLabel);
    //等级
    auto lvLabel=Label::create();
    lvLabel->setString(__String::createWithFormat("等级:%d",m_EnemyModel->LV)->getCString());
    lvLabel->setColor(Color3B::RED);
    lvLabel->setSystemFontSize(20);
    lvLabel->setAnchorPoint(Vec2(0, 0.5));
    lvLabel->setPosition(pos+Vec2(-50, 80));
    this->addChild(lvLabel);
}

/**
 k_ClassDes
 */

#include "HeroBase.h"
#include "GameBLL.h"
#include "GameLayer.h"
#include "StateMachine.h"
#include "HeroStateIdle.h"
#include "HeroStateRun.h"
#include "HeroStateAttack.h"
#include "ShaderEffectOutline.h"
#include "ShaderEffectSprite.h"
#include "SoundBLL.h"
#include "APShader.h"
#include "EnemyBase.h"
#include "APArmSpeedAction.h"
#include "APDirectorSpeedAction.h"
#include "APVec2.h"
#include "HeroStateSkill.h"
#include "EffectBLL.h"
#include "DropObject.h"
#include "EquipmentLocalBLL.h"
#include "GameLayer.h"
#include "APTools.h"
#include "SkillBLL.h"
#include "HeroAI.h"
#include "HeroBevTreeHeader.h"
#include "EnemyModel.h"
#include "GameUILayer.h"
#include "UpgradeSystem.h"

#define kTagShader  202

//稀构函数
HeroBase::~HeroBase()
{
    delete heroAI;
    delete m_HeroModel;
    delete [] skills;
}

//英雄基础类
HeroBase::HeroBase()
{
    heroAI=new HeroAI(this);
    m_InputData->m_PlayerControl=nullptr;
    skills=new SkillModel[4];
    m_HeroModel=new HeroModel();
    m_vVelocity=Vec2::ZERO;
    m_vHeading = Vec2(1,0);                 //初始化方向
    m_isMainHero=false;
    m_dMass=1.0f;                           //英雄质量
}

#pragma mark - 加载模型
//加载数据模型
void HeroBase::loadData(HeroModel* arg1)
{
    memcpy(m_HeroModel,arg1,sizeof(HeroModel));
    //加载动作文件
    loadActionFile(m_HeroModel->ActionFileModelID);
    //计算英雄数据
    UpgradeSystem::calculationHeroData(m_HeroModel);
    //计算英雄战力
    UpgradeSystem::calculationHeroPower(m_HeroModel, skills);
    
    //血条
    auto hpPos=PointFromString(m_HeroModel->HpPosition);
    m_HealthBar=HealthBarCompoment::create("imgs/xuetiao_beijing.png", "imgs/hero_xuetiao.png", "imgs/hero_xuetiao_2.png");
    m_HealthBar->setPosition(hpPos);
    m_HealthBar->setVisible(true);
    getArmature()->addChild(m_HealthBar,100);
    
    //加载阴影
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("guge/anxt_effect_10.plist");
    m_Shadow=Sprite::createWithSpriteFrameName("n_shadow_1.png");
    m_Shadow->setPosition(Vec2(0,-10));
    this->addChild(m_Shadow);
    
    auto hpSize=m_HealthBar->getContentSize();
    m_HealthBar->setScaleX(m_HeroModel->HpBarWidth / hpSize.width);
    
    heroAI->createBevTree();
}

//设置主英雄
void HeroBase::setMainHero(bool isMainHero)
{
    m_Shadow->removeChildByTag(kTagShader);
    if (isMainHero) {
        ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_effect_1.csb");
        auto m_Effect2=Armature::create("anxt_effect_1");
        m_Effect2->setColor(Color3B(25, 219, 44));
        m_Effect2->setPosition(aprateccp(m_Shadow, 0.5, 0.5));
        m_Shadow->addChild(m_Effect2);
        m_Effect2->getAnimation()->play("effect_9");
        m_Effect2->setTag(kTagShader);
    }
    m_HealthBar->setVisible(!isMainHero);
    m_isMainHero=isMainHero;
}

//获取数据模型
HeroModel* HeroBase::getHeroModel()
{
   return m_HeroModel;
}

//攻击事件
void HeroBase::attackEvent(AttackObject* ao)
{
    GameBLL::instance()->attackForHero(this,ao);
}

//普通攻击
std::string HeroBase::commonAttack()
{
    return "null";
}

//被攻击
void HeroBase::beAttack(int subHp)
{
    log("HeroBase::beAttack");
    //特效逻辑
    EffectBLL::getInstance()->addHeroEffect(this);
}

//每贞更新动画
void HeroBase::update(float ft)
{
    if (m_BodyState==GameEnum::BodyState::Die) {
        return ;
    }
    //AI更新
    heroAI->update(ft);
    
    //更新位置
    updatePosition(ft);
    
    //更新阴影
    updateShadow(ft);
    
    //技能时间更新
    for (int i=0; i< 4; i++) {
        if(skills[i].CurrCDTime > 0)
        {
            skills[i].CurrCDTime-=ft;
        }
        if(skills[i].CurrCDTime < 0)
        {
            skills[i].CurrCDTime=0.0;
        }
    }
}

//掉血
void HeroBase::subHp(float sub)
{
    
}

//获取英雄碰撞矩形
APOBB* HeroBase::getOBB()
{
    float fWidht=62;
    float fHeight=160;
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

void HeroBase::frameEvent(Bone *bone, const std::string& fn, int oi, int ci)
{
    BaseActionObject::frameEvent(bone, fn, oi, ci);
    
}

//减速效果
void HeroBase::animateSpeed(float ft)
{
    auto seq=Sequence::create(APArmSpeedAction::create(0.5*CCRANDOM_0_1(), 0.5*CCRANDOM_0_1()),APArmSpeedAction::create(0.5*CCRANDOM_0_1(), 1), NULL);
    getArmature()->runAction(seq);
}

//更新阴影大小
void HeroBase::updateShadow(float ft)
{
    //float percent=getArmature()->getAnimation()->getCurrentPercent();
    //m_Shadow->setScale(1+percent);
}

//获取掉落物品
void HeroBase::getDropObject(DropObject* dobj)
{
    if (dobj->getType()==DropObject::DropType::Gold) {
        GameBLL::instance()->addMoney(10);
        GameBLL::instance()->m_GameLayer->addCoinTips(getPosition(), 10, 10, 10);
        EffectBLL::getInstance()->addEffect(this, "effect_4", Vec2(0, 0));
    } else if (dobj->getType()==DropObject::DropType::Equip) {
        auto obj=(DropEquip*)dobj;
        int weaponIndex=obj->getWeaponIndex();
        
        auto elocalBll=EquipmentLocalBLL::create();
        elocalBll->addEquip(weaponIndex + 1);
        GameBLL::instance()->m_GameLayer->addEquiptips(getPosition(), (DropEquip*)dobj);
        GameBLL::instance()->m_WeaponIndexVector.push_back(weaponIndex);
    }
}

#pragma mark - BevTree
//获取怪的状态数据
BTNodeInputData* HeroBase::readBevNodeInputData()
{
    Vec2 targePos=getPosition();
    Vec2 currPos=getPosition();
    if(GameBLL::instance()->vectorEnemy.size() > 0)
    {
        auto randEnemy=GameBLL::instance()->vectorEnemy.front();
        if (randEnemy->getBodyState()!=GameEnum::BodyState::Die) {
            targePos=randEnemy->getPosition();
        }
        float minDistance=currPos.distance(targePos);
        minDistance=minDistance<=0 ? m_HeroModel->AttackDist : minDistance;
        for (auto &enemy : GameBLL::instance()->vectorEnemy) {
            if (enemy->getEnemyModel()->CurrHp > 0){
                auto ePos=enemy->getPosition();
                float currDistance=currPos.distance(ePos);
                if (currDistance<minDistance) {
                    targePos=ePos;
                    minDistance=currDistance;
                }
            }
        }
    }
    m_InputData->m_IsMainHero=m_isMainHero;
    m_InputData->m_PlayerControl=nullptr;
    if (m_isMainHero) {
        m_InputData->m_PlayerControl=(IUIControl*)GameBLL::instance();
        targePos=GameBLL::instance()->m_MainHero->getPosition();
    }
    m_InputData->m_Owner=this;
    m_InputData->m_OwnerState=m_BodyState;
    m_InputData->m_RunMoveSpeed=getHeroModel()->RunMoveSpeed;
    m_InputData->m_TargetPosition2D=targePos;
    m_InputData->m_CurrPosition2D=currPos;
    m_InputData->m_MainHeroPosition2D=GameBLL::instance()->m_MainHero->getPosition();
    m_InputData->m_iAttackDist=getHeroModel()->AttackDist;
    m_InputData->m_CurrentFacing=m_vHeading;
    
    return m_InputData;
}

//播放动画
void HeroBase::playAnimate(const std::string& animateName)
{
    BaseActionObject::playAnimate(animateName);
    
    if (animateName==m_ActionFileModel->SkillName1) {
        skills[0].CurrCDTime=skills[0].CdTime;
        skillA();
    }else if(animateName==m_ActionFileModel->SkillName2){
        skills[1].CurrCDTime=skills[1].CdTime;
        skillB();
    }else if(animateName==m_ActionFileModel->SkillName3){
        skills[2].CurrCDTime=skills[2].CdTime;
        skillC();
    }else if(animateName==m_ActionFileModel->SkillName4){
        skills[3].CurrCDTime=skills[3].CdTime;
        skillD();
    }
}

//更新英雄输出数据
void HeroBase::updateAIOutData(BTNodeOutputData *data)
{
    //处理技能按钮reset
    if (m_InputData->m_PlayerControl) {
        m_InputData->m_PlayerControl->resetSkillButton();
    }
    m_vVelocity=data->m_vVelocity;
    setFacing(data->m_NextFacing);
    m_InputData->m_CurrentFacing=data->m_NextFacing;
   
    while (!data->m_OutEvent.empty()) {
        BaseActionEvent* event=data->m_OutEvent.front();
        data->m_OutEvent.eraseObject(event);
        
        switch (event->getBaseActionEvent()) {
            case GameEnum::BaseActionEventType::PlayAnimate:                    //播放动画
            {
                std::string animateName=((__String*)event->getEventArg())->getCString();
                changeState(event->getEventBodyState(), animateName);
            }break;
            case GameEnum::BaseActionEventType::BeAttack:                       //被攻击
            {
                //auto hero=(HeroBase*)event->getEventArg();
                //subBlood(hero);
            }break;
            case GameEnum::BaseActionEventType::ChangeStateIdle:                //切换空闲状态
            {
                idleAnimate();
                //m_CurrState=GameEnum::EnemyState::Idle;
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

//获取hp百分比
float HeroBase::getHpPercent()
{
    float percent=((float)m_HeroModel->CurrHp / (float)m_HeroModel->MaxHp) * 100.0;
    percent = percent < 0.0f ? 0.0f : percent;
    return percent;
}

//设置英雄位置
void HeroBase::setInitPosition(const Vec2 &position)
{
    setPosition(position);
    //设置默认位置
    m_BevOutData->m_NextPosition=position;
}

//被攻击
void HeroBase::beAttack(AttackObject *att)
{
    //死亡、被打、不切入被击
    if (m_BodyState==GameEnum::BodyState::Die ||
        m_BodyState==GameEnum::BodyState::BeAttack)
    {
        return;
    }
    
    //待机、走路、的时候才播放被攻击动画
    if (m_BodyState==GameEnum::BodyState::Idle || m_BodyState==GameEnum::BodyState::Run) {
        //播放攻击动画
        if (att->getIsHitDown() || m_BodyState==GameEnum::BodyState::Down) {
            changeState(GameEnum::BodyState::Down, m_ActionFileModel->ActionBeAttackDown);
        }else{
            std::string animateName=m_ActionFileModel->ActionBeAttack1;
            changeState(GameEnum::BodyState::BeAttack, animateName);
        }
    }
    //改变阴影
    onShaderChange(GameEnum::EnemyEvent::EventChangeShaderBeAttackShader);
    //特效
    EffectBLL::getInstance()->addHeroEffect(this);
    //计算掉血
    subBlood((EnemyBase*)att->getAttackObject());
}

//扣血值
void HeroBase::subBlood(EnemyBase *enemy)
{
    //log("Enemy::subHp(%f,%d,%d)",subHp,m_State,m_EnemyModel->CurrHP);
    if (m_BodyState==GameEnum::BodyState::Die) {
        return;
    }
    
    int def=m_HeroModel->Def;
    //伤害 = 攻击方攻击力*(1-（挨打方防御力*0.05/（0.05*挨打方防御力+1））)+攻击方攻击力*0.025
    auto enemyModel=enemy->getEnemyModel();
    int attack=enemyModel->Attack;
    int attackResult=attack * (1 - (def * 0.05 / (0.05 * def + 1))) + attack * 0.025;
    int randAttack=attackResult * APTools::getRandFloat(-0.1, 0.1);
    attackResult+=randAttack;
    m_HeroModel->CurrHp-=attackResult;
    
    float percent=getHpPercent();
    m_HealthBar->setHpPercentage(percent);
    
    if (m_isMainHero) {
        GameBLL::instance()->m_GameUILayer->updateHeroState(this);
    }
    if (m_HeroModel->CurrHp > 0) {
        //播放掉血数字
        int orderZ=getLocalZOrder();
        Vec2 vPos=getPosition();
        auto ggl=GameBLL::instance()->m_GameLayer;
        ggl->subCurrHp(vPos,20,attackResult,orderZ);
    }
    
    if (m_HeroModel->CurrHp <= 0) {
        die();
    }
}

//怪死亡
void HeroBase::die()
{
    changeState(GameEnum::BodyState::Die, getActionFileMode()->ActionDie);
    GameBLL::instance()->heroWillDie(this);
}

//动画播放完成
void HeroBase::animateFinish(const std::string& name)
{
    BaseActionObject::animateFinish(name);
    
    if (name==getActionFileMode()->ActionDie) {
        m_BodyState=GameEnum::BodyState::Die;
        getArmature()->getAnimation()->stop();
        GameBLL::instance()->removeHero(this);
    }
}

//切换shader状态
void HeroBase::onShaderChange(GameEnum::EnemyEvent newState)
{
    auto callShaderFunc=[=]()
    {
        APShader::addShaderArmature(m_Armature, "shader/herored.fsh");
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

//给英雄加经验
void HeroBase::addExp(int exp)
{
    if(UpgradeSystem::addHeroExp(exp, m_HeroModel))
    {
        EffectBLL::getInstance()->addHeroEffectUp(this);
    }
}

//当前技能冷却时间
void HeroBase::skillCdTime(int skillID)
{
    
}

//加血
void HeroBase::addHp(int addHp)
{
    auto model=getHeroModel();
    int currHp=model->CurrHp + addHp;
    if (currHp > model->MaxHp) {
        currHp=model->MaxHp;
    }
    model->CurrHp=currHp;
    
    if (m_isMainHero) {
        GameBLL::instance()->m_GameUILayer->updateHeroState(this);
    }
    
    //播放加血数字
    Vec2 vPos=getPosition();
    auto ggl=GameBLL::instance()->m_GameLayer;
    ggl->addHpNumber(vPos,addHp);
}
//设置血条显示隐藏
void HeroBase::setHpBarVisible(bool bVisible)
{
    m_HealthBar->setVisible(bVisible);
}
//设置阴影显示隐藏
void HeroBase::setShadowVisible(bool bVisible)
{
    m_Shadow->setVisible(bVisible);
}
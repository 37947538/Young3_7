//
//  EffectBLL.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/29.
//
//

#include "EffectBLL.h"
#include "HeroBase.h"
#include "EnemyBase.h"

static EffectBLL* sharedEffectBLL = nullptr;

EffectBLL* EffectBLL::getInstance()
{
    if (!sharedEffectBLL) {
        sharedEffectBLL = new (std::nothrow) EffectBLL();
    }
    return sharedEffectBLL;
}

void EffectBLL::destroyInstance()
{
    if(sharedEffectBLL != nullptr)
    {
        //haredEffectBLL->releaseActions();
        CC_SAFE_DELETE(sharedEffectBLL);
    }
}

EffectBLL::~EffectBLL()
{
    
}
EffectBLL::EffectBLL()
{
    
}

//增加敌兵特效
void EffectBLL::addEnemyEffect(EnemyBase *eb,AttackObject *att)
{
    HeroBase *hb=(HeroBase*)att->getAttackObject();
    std::string strEffectName=hb->getHeroModel()->EffectTypeName;
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_effect_1.csb");
    auto m_Effect=Armature::create("anxt_effect_1");
    m_Effect->setUserObject(eb);
    
    m_Effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(EffectBLL::movementEvent, this));
    m_Effect->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(EffectBLL::frameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    eb->addChild(m_Effect);
    m_Effect->setPosition(Vec2(0,50));
    m_Effect->getAnimation()->play(strEffectName);
    m_Effect->setRotation(360*CCRANDOM_0_1());
    m_Effect->setScale(1.0+1.5*CCRANDOM_0_1());
    BlendFunc cbl = {GL_DST_ALPHA, GL_ONE};
    m_Effect->setBlendFunc(cbl);
}

//增加go
void EffectBLL::addShowGo(Layer *h)
{
    auto m_WinSize=Director::getInstance()->getWinSize();
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_effect_1.csb");
    auto m_Effect=Armature::create("anxt_effect_1");
    m_Effect->setUserObject(h);
    m_Effect->setPosition(Vec2(m_WinSize.width - 100,m_WinSize.height - 175));
    m_Effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(EffectBLL::movementEvent, this));
    m_Effect->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(EffectBLL::frameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    h->addChild(m_Effect);
    m_Effect->getAnimation()->play("effect_10");
}

//增加死亡
void EffectBLL::addDieEffect(Layer *h)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_effect_1.csb");
    
    auto m_Effect=Armature::create("anxt_effect_1");
    m_Effect->setUserObject(h);
    m_Effect->setPosition(apccp(0.5, 0.5));
    m_Effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(EffectBLL::movementEvent, this));
    m_Effect->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(EffectBLL::frameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    h->addChild(m_Effect);
    m_Effect->getAnimation()->play("effect_12");
}
//增加特效
void EffectBLL::addEffect(Node *h,const std::string& effName,Vec2 pos, bool isAutoRemove)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_effect_1.csb");
    
    auto m_Effect=Armature::create("anxt_effect_1");
    m_Effect->setLocalZOrder(kGameTopZ);
    m_Effect->setUserObject(h);
    m_Effect->setPosition(pos);
    if (isAutoRemove) {
        m_Effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(EffectBLL::movementEvent, this));
    }
    m_Effect->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(EffectBLL::frameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    h->addChild(m_Effect);
    m_Effect->getAnimation()->play(effName);
}

//增加英雄升级
void EffectBLL::addHeroEffectUp(HeroBase *hb)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_effect_1.csb");
    
    auto m_Effect=Armature::create("anxt_effect_1");
    m_Effect->setUserObject(hb);
    
    m_Effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(EffectBLL::movementEvent, this));
    m_Effect->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(EffectBLL::frameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    hb->addChild(m_Effect);
    m_Effect->setPosition(Vec2(0,0));
    m_Effect->getAnimation()->play("effect_11");
}

//增加英雄特效
void EffectBLL::addHeroEffect(HeroBase *hb)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_effect_1.csb");
    
    auto m_Effect=Armature::create("anxt_effect_1");
    m_Effect->setUserObject(hb);
    
    m_Effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(EffectBLL::movementEvent, this));
    m_Effect->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(EffectBLL::frameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    hb->addChild(m_Effect);
    m_Effect->setPosition(Vec2(0,50));
    m_Effect->getAnimation()->play("effect_1");
    m_Effect->setRotation(360*CCRANDOM_0_1());
    m_Effect->setScale(1.0+1.5*CCRANDOM_0_1());
    BlendFunc cbl = {GL_DST_ALPHA, GL_ONE};
    m_Effect->setBlendFunc(cbl);
    
    auto m_Effect2=Armature::create("anxt_effect_1");
    m_Effect2->setUserObject(hb);
    m_Effect2->setPosition(Vec2(0,60));
    m_Effect2->setRotation(360*CCRANDOM_0_1());
    m_Effect2->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(EffectBLL::movementEvent, this));
    m_Effect2->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(EffectBLL::frameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    hb->addChild(m_Effect2);
    m_Effect2->getAnimation()->play("effect_3");
}

void EffectBLL::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    //log("movementID:%s", movementID.c_str());
    if (movementType==MovementEventType::COMPLETE || movementType==MovementEventType::LOOP_COMPLETE) {
        armature->removeFromParentAndCleanup(true);
    }
}

void EffectBLL::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    
}

//
//  DayRewardLayer.cpp
//  Zombie3_4
//
//  Created by liuye on 15/10/20.
//
//

#include "DayRewardLayer.h"
#include "ButtonHelper.h"
#include "DayRewardBLL.h"
#include "EffectBLL.h"
#include "PopTipsLayer.h"

DayRewardLayer::~DayRewardLayer()
{
    
}
DayRewardLayer::DayRewardLayer()
{
    
}
bool DayRewardLayer::init()
{
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("DayRewardLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto closeButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (closeButton) {
        closeButton->addTouchEventListener(CC_CALLBACK_2(DayRewardLayer::closeButton_OnTouch, this));
    }
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_ui.csb");
    auto effect=Armature::create("anxt_ui");
    effect->getAnimation()->play("ui_4");
    
    int count=DayRewardBLL::getInstance()->getLoginDateCount();
    for (int i=1; i<=7; i++) {        
        auto btnName=__String::createWithFormat("Button_qiandao_%d",i);
        auto btn=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, btnName->getCString()));
        if (btn) {
            if (i<count) {
                btn->setBright(false);
            }else if (i==count) {
                if (DayRewardBLL::getInstance()->getIsDayReceive()) {
                    btn->setBright(false);
                }else{
                    btn->setTag(i);
                    btn->addTouchEventListener(CC_CALLBACK_2(DayRewardLayer::enterButton_OnTouch, this));
                
                    effect->setPosition(aprateccp(btn, 0.5, 0.5));
                    btn->addChild(effect);
                }
            }
        }
    }
    
    return true;
}
//关闭
void DayRewardLayer::closeButton_OnTouch(Ref* sender,Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    this->removeFromParentAndCleanup(true);
}
void DayRewardLayer::enterButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto btn=(Button*)sender;
    btn->setTouchEnabled(false);
    btn->setBright(false);
    btn->removeAllChildren();
    
    int iTag=btn->getTag();
    //发放今日奖励
    std::string msg=DayRewardBLL::getInstance()->putDayReward(iTag);
    
    PopTipsLayer::addTipLayer(this, msg);
    
    if (updateCalllback) {
        updateCalllback(this);
    }
}

void DayRewardLayer::onEnter()
{
    PopBase::onEnter();
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,NULL);
    m_RootNode->runAction(m_Sequence);
}
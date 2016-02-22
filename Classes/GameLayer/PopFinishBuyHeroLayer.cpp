//
//  PopFinishBuyHeroLayer.cpp
//  Zombie3_4
//
//  Created by liuye on 15/9/2.
//
//

#include "PopFinishBuyHeroLayer.h"
#include "ButtonHelper.h"
#include "HeroModelBLL.h"
#include "PopTipsLayer.h"
#include "PlayerBLL.h"
#include "APSystem.h"

PopFinishBuyHeroLayer::~PopFinishBuyHeroLayer()
{
    
}
PopFinishBuyHeroLayer::PopFinishBuyHeroLayer()
{
    m_HeroIndex=-1;
}
bool PopFinishBuyHeroLayer::init(){
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode=static_cast<Layout*>(CSLoader::createNode("FinishBuyHeroLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto closeButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_quxiao"));
    if (closeButton) {
        closeButton->addTouchEventListener(CC_CALLBACK_2(PopFinishBuyHeroLayer::closeButton_OnTouch, this));
    }
    auto enterButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_queding"));
    if (enterButton) {
        enterButton->addTouchEventListener(CC_CALLBACK_2(PopFinishBuyHeroLayer::enterButton_OnTouch, this));
    }
    m_GoldText=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "Text_zuanshishu"));
    if (m_GoldText) {
        m_GoldText->setString("");
    }
    
    m_HeroNameText=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "Text_ming"));
    if (m_HeroNameText) {
        m_HeroNameText->setString("");
    }
    
    return true;
}
void PopFinishBuyHeroLayer::closeButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    //this->removeFromParentAndCleanup(true);
    
    APSystem::getInstance()->sendEvent(APEventMainMap);
}
void PopFinishBuyHeroLayer::enterButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    if (m_HeroIndex<0) {
        PopTipsLayer::addTipLayer(this, "请选择要购买的英雄！");
        return;
    }
    
    auto bll=HeroModelBLL::create(kModelWritablePath);
    auto model=&bll->modelData[m_HeroIndex];
    int price=model->Price;
    
    auto pb=PlayerBLL::create();
    int diaCount=pb->getPlayerDia();
    diaCount=diaCount-price;
    if (diaCount>=0) {
        pb->addDia(-price);
        pb->setBuyHero(m_HeroIndex);
        
        if (enterCallback) {
            enterCallback(this);
        }
        //this->removeFromParentAndCleanup(true);
        m_RootNode->setVisible(false);
        PopTipsLayer::addTipLayer(this, "购买成功！");
        auto func=[&](){
            APSystem::getInstance()->sendEvent(APEventMainMap);
        };        
        this->runAction(Sequence::create(DelayTime::create(1.5),CallFunc::create(func), NULL));
    }else{
        PopTipsLayer::addTipLayer(this, "钻石不够！");
    }
}
void PopFinishBuyHeroLayer::onEnter(){
    PopBase::onEnter();
    
    auto call=CallFunc::create(CC_CALLBACK_0(PopFinishBuyHeroLayer::setDataView, this));
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    m_Sequence=Sequence::create(call,EaseElasticOut::create(MoveTo::create(0.8, basePoint)),NULL);
    m_RootNode->runAction(m_Sequence);
}
void PopFinishBuyHeroLayer::setDataView()
{
    auto bll=HeroModelBLL::create(kModelWritablePath);
    auto model=&bll->modelData[m_HeroIndex];
    if (model) {
        m_GoldText->setString(__String::createWithFormat("%d",model->Price)->getCString());
        m_HeroNameText->setString(model->HeroName);
    }
}

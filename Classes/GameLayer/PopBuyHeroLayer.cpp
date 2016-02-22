//
//  PopBuyHeroLayer.cpp
//  Zombie3_4
//
//  Created by liuye on 15/8/27.
//
//

#include "PopBuyHeroLayer.h"
#include "ButtonHelper.h"
#include "HeroModelBLL.h"
#include "PopTipsLayer.h"
#include "PlayerBLL.h"

PopBuyHeroLayer::~PopBuyHeroLayer()
{
    
}
PopBuyHeroLayer::PopBuyHeroLayer()
{
    m_HeroIndex=-1;
}
bool PopBuyHeroLayer::init(){
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode=static_cast<Layout*>(CSLoader::createNode("BuyHeroLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto closeButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_quxiao"));
    if (closeButton) {
        closeButton->addTouchEventListener(CC_CALLBACK_2(PopBuyHeroLayer::closeButton_OnTouch, this));
    }
    auto testButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_shiwan"));
    if (testButton) {
        testButton->addTouchEventListener(CC_CALLBACK_2(PopBuyHeroLayer::testButton_OnTouch, this));
    }
    auto enterButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_queding"));
    if (enterButton) {
        enterButton->addTouchEventListener(CC_CALLBACK_2(PopBuyHeroLayer::enterButton_OnTouch, this));
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
void PopBuyHeroLayer::closeButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectClose);
    this->removeFromParentAndCleanup(true);
}
void PopBuyHeroLayer::testButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    if (testCallback) {
        testCallback(this);
    }
}
void PopBuyHeroLayer::enterButton_OnTouch(Ref* sender, Widget::TouchEventType type)
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
        this->removeFromParentAndCleanup(true);
    }else{
        PopTipsLayer::addTipLayer(this, "钻石不够！");
    }
}
void PopBuyHeroLayer::onEnter(){
    PopBase::onEnter();
    
    auto call=CallFunc::create(CC_CALLBACK_0(PopBuyHeroLayer::setDataView, this));
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    m_Sequence=Sequence::create(call,EaseElasticOut::create(MoveTo::create(0.8, basePoint)),NULL);
    m_RootNode->runAction(m_Sequence);
}
void PopBuyHeroLayer::setDataView()
{
    auto bll=HeroModelBLL::create(kModelWritablePath);
    auto model=&bll->modelData[m_HeroIndex];
    if (model) {
        m_GoldText->setString(__String::createWithFormat("%d",model->Price)->getCString());
        m_HeroNameText->setString(model->HeroName);
    }
}

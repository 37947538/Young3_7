//
//  PopConfirmLayer.cpp
//  Zombie3_4
//
//  Created by liuye on 15/8/26.
//
//

#include "PopConfirmLayer.h"

bool PopConfirmLayer::init(){
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode=static_cast<Layout*>(CSLoader::createNode("ConfirmLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto closeButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_quxiao"));
    if (closeButton) {
        closeButton->addTouchEventListener(CC_CALLBACK_2(PopConfirmLayer::closeButton_OnTouch, this));
    }
    auto enterButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_queding"));
    if (enterButton) {
        enterButton->addTouchEventListener(CC_CALLBACK_2(PopConfirmLayer::enterButton_OnTouch, this));
    }
    m_GoldText=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "Text_jinbishu"));
    if (m_GoldText) {
        m_GoldText->setString("");
    }
    
    return true;
}
void PopConfirmLayer::setInfoString(const std::string& msg)
{
    m_GoldText->setString(msg);
}
void PopConfirmLayer::closeButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    this->removeFromParentAndCleanup(true);
}
void PopConfirmLayer::enterButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    if (enterCallback) {
        enterCallback(this);
    }
}
void PopConfirmLayer::onEnter(){
    PopBase::onEnter();
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,NULL);
    m_RootNode->runAction(m_Sequence);
}

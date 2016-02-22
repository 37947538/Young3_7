//
//  PopOverLayer.cpp
//  Zombie3_4
//
//  Created by liuye on 15/8/26.
//
//

#include "PopOverLayer.h"
#include "ButtonHelper.h"

PopOverLayer::~PopOverLayer()
{
    
}
PopOverLayer::PopOverLayer()
{
    m_TypeID=-1;
}
bool PopOverLayer::init(){
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("OverLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto restartButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_chonglai"));
    if (restartButton) {
        restartButton->setTag(1);
        restartButton->addTouchEventListener(CC_CALLBACK_2(PopOverLayer::enterButton_OnTouch, this));
    }
    auto returnButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_fanhui"));
    if (returnButton) {
        returnButton->setTag(2);
        returnButton->addTouchEventListener(CC_CALLBACK_2(PopOverLayer::enterButton_OnTouch, this));
    }
    auto reviveButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_fuhuo"));
    if (reviveButton) {
        reviveButton->setTag(3);
        reviveButton->addTouchEventListener(CC_CALLBACK_2(PopOverLayer::enterButton_OnTouch, this));
    }
    
    return true;
}
void PopOverLayer::enterButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto btn=(Button*)sender;
    btn->setTouchEnabled(false);
    
    int iTag=btn->getTag();
    setTypeID(iTag);
    
    if (enterCallback) {
        enterCallback(this);
    }
}
void PopOverLayer::onEnter()
{
    PopBase::onEnter();
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,NULL);
    m_RootNode->runAction(m_Sequence);
}
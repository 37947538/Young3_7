//
//  PopTipsLayer.cpp
//  Zombie3_4
//
//  Created by liuye on 15/8/14.
//
//

#include "PopTipsLayer.h"

//增加提示层
void PopTipsLayer::addTipLayer(Node *parent, const std::string& msg)
{
    auto layer=PopTipsLayer::create();
    layer->setInfoString(msg);
    parent->addChild(layer,kGameTopZ);
}

bool PopTipsLayer::init(){
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("GoldTipsNode.csb"));
    m_RootNode->setPosition(apccp(0.5, 0.5));
    m_RootNode->setScaleY(0.0);
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    m_TipsBg=dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_RootNode, "Image_kuang_buzu"));
    
    m_TipsText=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "Text_buzu"));
    if (m_TipsText) {
        m_TipsText->setString("");
    }
    
    return true;
}
void PopTipsLayer::setInfoString(const std::string& msg)
{
    m_TipsText->setString(msg);
}
void PopTipsLayer::onEnter(){
    PopBase::onEnter();
    
    auto func=[&](){
        this->removeFromParentAndCleanup(true);
    };
    
    auto seq=Sequence::create(EaseElasticOut::create(ScaleTo::create(0.5, 1.0)),DelayTime::create(0.5),CallFunc::create(func),NULL);
    m_RootNode->runAction(seq);
}

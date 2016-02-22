//
//  ShopLayer.cpp
//  Zombie3_4
//
//  Created by yuankang on 15/7/27.
//
//

#include "ShopLayer.h"
#include "PlayerBLL.h"
#include "ButtonHelper.h"

static int GoldCountItems[]{20000,50000,120000,400000};
static int DiaCountItems[]{10,50,120,400};

bool ShopLayer::init(){
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("ShopLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto close = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (close) {
        close->addTouchEventListener(CC_CALLBACK_2(ShopLayer::Button_Close_BtnOnTouch, this));
    }
    
    for (int i=0; i<4; i++) {
        auto goldButtonName=__String::createWithFormat("Button_buy_jinbi_%d",i+1);
        auto buyGoldButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, goldButtonName->getCString()));
        if (buyGoldButton) {
            buyGoldButton->setTag(i);
            buyGoldButton->addTouchEventListener(CC_CALLBACK_2(ShopLayer::Button_BuyGold_BtnOnTouch, this));
        }
        auto diaButtonName=__String::createWithFormat("Button_buy_zuanshi_%d",i+1);
        auto buyDiaButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, diaButtonName->getCString()));
        if (buyDiaButton) {
            buyDiaButton->setTag(i);
            buyDiaButton->addTouchEventListener(CC_CALLBACK_2(ShopLayer::Button_BuyDia_BtnOnTouch, this));
        }
    }
    
    return true;
}
void ShopLayer::onEnter()
{
    PopBase::onEnter();
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,NULL);
    m_RootNode->runAction(m_Sequence);
}
//关闭
void ShopLayer::Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectClose);

    removeFromParentAndCleanup(true);
}
//购买金币
void ShopLayer::Button_BuyGold_BtnOnTouch(Ref* sender,Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto btn=(Button*)sender;
    int iTag=btn->getTag();
    
    int goldCount=GoldCountItems[iTag];
    auto pb=PlayerBLL::create();
    pb->addGold(goldCount);
    
    if (updateCallback) {
        updateCallback(this);
    }
}
//购买钻石
void ShopLayer::Button_BuyDia_BtnOnTouch(Ref* sender,Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto btn=(Button*)sender;
    int iTag=btn->getTag();
    
    int diaCount=DiaCountItems[iTag];
    auto pb=PlayerBLL::create();
    pb->addDia(diaCount);
    
    if (updateCallback) {
        updateCallback(this);
    }
}
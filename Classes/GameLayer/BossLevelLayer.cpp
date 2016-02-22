//
//  BossLevelLayer.cpp
//  Zombie3_4
//
//  Created by liuye on 15/9/10.
//
//

#include "BossLevelLayer.h"
#include "PlayerBLL.h"
#include "ButtonHelper.h"
#include "LevelBLL.h"
#include "APSystem.h"

bool BossLevelLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("LevelBossLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto pb=PlayerBLL::create();
    int iOpenLevelID=pb->getOpenLevelID(true);
    for (int i=0; i<5; i++) {
        auto btnName=__String::createWithFormat("Button_guanka_%d",i+1);
        auto btn=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, btnName->getCString()));
        if (btn) {
            btn->setTag(i);
            btn->addTouchEventListener(CC_CALLBACK_2(BossLevelLayer::LevelButton_OnTouch, this));
            
            if (i>iOpenLevelID) {
                btn->setTouchEnabled(false);
                auto img=ImageView::create("imgs/tb_xiaoguan_suo.png");
                img->setPosition(aprateccp(btn, 0.5, 0.5));
                img->setLocalZOrder(200);
                btn->addChild(img);
            }
        }
    }
    
    auto Button_Close=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (Button_Close) {
        Button_Close->addTouchEventListener(CC_CALLBACK_2(BossLevelLayer::Button_Close_BtnOnTouch, this));
    }
    
    return true;
}

void BossLevelLayer::Button_Close_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    this->removeFromParentAndCleanup(true);
}

void BossLevelLayer::LevelButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender,type);
    if (type==Widget::TouchEventType::ENDED){
        SoundBLL::getInstance()->playEffect(kButtonSound);
        auto btn=(Button*)sender;
        int iLevelIndex=btn->getTag();
        
        LevelBLL::instance()->setIsBossLevel(true);
        LevelBLL::instance()->setPlayerSelecLevelID(iLevelIndex);
        APSystem::getInstance()->sendEvent(APEventChoosePeople);
    }
}
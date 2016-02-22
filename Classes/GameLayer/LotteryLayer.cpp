//
//  LotteryLayer.cpp
//  Zombie3_4
//
//  Created by yuankang on 15/7/27.
//
//

#include "LotteryLayer.h"
#include "MainMapScene.h"
#include "LotteryResultLayer.h"
#include "PlayerBLL.h"
#include "PopTipsLayer.h"
#include "ButtonHelper.h"

using namespace cocostudio::timeline;

Scene* LotteryLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = LotteryLayer::create();
    scene->addChild(layer);
    return scene;
}

bool LotteryLayer::init()
{
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("LotteryLayer.csb"));
    this->addChild(m_RootNode);
    
    ActionTimeline* action = CSLoader::createTimeline("LotteryLayer.csb");
    action->gotoFrameAndPlay(0);
    m_RootNode->runAction(action);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto close = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (close) {
        close->addTouchEventListener(CC_CALLBACK_2(LotteryLayer::Button_Close_BtnOnTouch, this));
    }
    
    for (int i=1; i<=4; i++) {
        auto btnName=__String::createWithFormat("Button_choujiang_%d",i);
        auto luckButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, btnName->getCString()));
        if (luckButton) {
            luckButton->setTag(i);
            luckButton->addTouchEventListener(CC_CALLBACK_2(LotteryLayer::Button_Luck_BtnOnTouch, this));
        }
    }
    
    return true;
}
//弹出效果
void LotteryLayer::onEnter(){
    PopBase::onEnter();
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,NULL);
    m_RootNode->runAction(m_Sequence);
}
//关闭
void LotteryLayer::Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectClose);
    
    removeFromParentAndCleanup(true);
}
void LotteryLayer::Button_Luck_BtnOnTouch(Ref* sender,Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    bool isViewResult=false;
    
    auto pb=PlayerBLL::create();
    int gold=pb->getPlayerGold();
    int dia=pb->getPlayerDia();
    
    auto btn=(Button*)sender;
    int iTag=btn->getTag();
    switch (iTag) {
        case 1:
        {
            int count=30000;
            if (gold-count>=0) {                
                pb->addGold(-count);
                isViewResult=true;
            }else{
                PopTipsLayer::addTipLayer(this, "金币不足！");
            }
        }break;
        case 2:
        {
            int count=200000;
            if (gold-count>=0) {
                pb->addGold(-count);
                isViewResult=true;
            }else{
                PopTipsLayer::addTipLayer(this, "金币不足！");
            }
        }break;
        case 3:
        {
            int count=30;
            if (dia-count>=0) {
                pb->addDia(-count);
                isViewResult=true;
            }else{
                PopTipsLayer::addTipLayer(this, "钻石不足！");
            }
        }break;
        case 4:
        {
            int count=200;
            if (dia-count>=0) {
                pb->addDia(-count);
                isViewResult=true;
            }else{
                PopTipsLayer::addTipLayer(this, "钻石不足！");
            }
        }break;
        default:
            break;
    }
    
    if (isViewResult) {
        if (updateCallback) {
            updateCallback(this);
        }
        auto pop=LotteryResultLayer::create();
        pop->setTypeID(iTag);
        this->addChild(pop);
    }    
}
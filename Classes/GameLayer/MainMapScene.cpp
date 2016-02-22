#include "MainMapScene.h"
#include "APSystem.h"
#include "EquipLayer.h"
#include "EquipUpgradeLayer.h"
#include "SkillUpgradeLayer.h"
#include "LotteryLayer.h"
#include "ShopLayer.h"
#include "PlayerBLL.h"
#include "LoadingScene.h"
#include "LevelLayer.h"
#include "ButtonHelper.h"
#include "BossLevelLayer.h"
#include "UpgradeSystem.h"
#include "GameObjectFactory.h"
#include "HeroBase.h"
#include "DayRewardLayer.h"

using namespace cocostudio::timeline;

Scene* MainMapScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMapScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MainMapScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto seq=Sequence::create(RotateBy::create(1, 10), NULL);
    auto replay=RepeatForever::create(seq);
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("MainMapScene.csb"));
    this->addChild(m_RootNode);
    
    ActionTimeline* action = CSLoader::createTimeline("MainMapScene.csb");
    action->gotoFrameAndPlay(0);
    m_RootNode->runAction(action);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    //总战斗力
    m_SumPower=dynamic_cast<TextBMFont*>(Helper::seekWidgetByName(m_RootNode, "BitmapFontLabel_zhanli"));
    
    for (int i=1; i<=3; i++) {
        auto imgName=__String::createWithFormat("Image_yuan_%d",i);
        auto img=dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_RootNode, imgName->getCString()));
        if (img) {
            img->runAction(replay->clone());
        }
    }
    for (int i=1; i<=2; i++) {
        auto btnName=__String::createWithFormat("Button_tianjia_%d", i);
        auto btn=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, btnName->getCString()));
        if (btn) {
            btn->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_Shop_BtnOnTouch, this));
        }
    }
    auto Button_guanka_3=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_guanka_3"));
    if (Button_guanka_3) {
        Button_guanka_3->setTag(3);
        Button_guanka_3->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_play_BtnOnTouch, this));
    }
    auto Button_guanka_2=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_guanka_2"));
    if (Button_guanka_2) {
        Button_guanka_2->setTag(2);
        Button_guanka_2->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_play_BtnOnTouch, this));
    }
    auto Button_guanka_1=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_guanka_1"));
    if (Button_guanka_1) {
        Button_guanka_1->setTag(1);
        Button_guanka_1->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_play_BtnOnTouch, this));
    }
    
    auto Button_DayReward=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_gongneng_6"));
    if (Button_DayReward) {
        Button_DayReward->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_DayReward_BtnOnTouch, this));
    }
    auto Button_Equip=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_gongneng_1"));
    if (Button_Equip) {
        Button_Equip->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_Equip_BtnOnTouch, this));
    }
    auto Button_EquipUpgrade=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_gongneng_2"));
    if (Button_EquipUpgrade) {
        Button_EquipUpgrade->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_EquipUpgrade_BtnOnTouch, this));
    }
    auto Button_SkillUpgrade=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_gongneng_3"));
    if (Button_SkillUpgrade) {
        Button_SkillUpgrade->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_SkillUpgrade_BtnOnTouch, this));
    }
    auto Button_Lottery=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_gongneng_4"));
    if (Button_Lottery) {
        Button_Lottery->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_Lottery_BtnOnTouch, this));
    }
    auto Button_Shop=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_gongneng_5"));
    if (Button_Shop) {
        Button_Shop->addTouchEventListener(CC_CALLBACK_2(MainMapScene::Button_Shop_BtnOnTouch, this));
    }
    
    tCoin=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_jinbishuliang"));
    tDiamond=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_zuanshishu"));
    
    updateLabel();
    
    SoundBLL::getInstance()->playbackground(kStartMusic);
    
    return true;
}

//按钮信息发送器
void MainMapScene::Button_play_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto btn=static_cast<Button*>(sender);
    int iTag=btn->getTag();
    
    if (iTag==3) {
        auto level=BossLevelLayer::create();
        this->addChild(level);
    }else{
        auto level=LevelLayer::create();
        this->addChild(level);
    }
}

//签到
void MainMapScene::Button_DayReward_BtnOnTouch(Ref* sender,Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    auto lay=DayRewardLayer::create();
    lay->updateCalllback=CC_CALLBACK_0(MainMapScene::updateLabel, this);
    this->addChild(lay);
}

//装备
void MainMapScene::Button_Equip_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    auto lay = EquipLayer::create();
    lay->updateCalllback=CC_CALLBACK_0(MainMapScene::updateLabel, this);
    lay->closeBtnCallback=CC_CALLBACK_0(MainMapScene::updateLabel, this);
    this->addChild(lay);
}

//装备强化
void MainMapScene::Button_EquipUpgrade_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto lay = EquipUpgradeLayer::create();
    lay->updateCalllback=CC_CALLBACK_0(MainMapScene::updateLabel, this);
    lay->closeBtnCallback=CC_CALLBACK_0(MainMapScene::updateLabel, this);
    this->addChild(lay);
}

//技能强化
void MainMapScene::Button_SkillUpgrade_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto lay = SkillUpgradeLayer::create();
    addChild(lay);
    
    lay->closeBtnCallback=CC_CALLBACK_0(MainMapScene::updateLabel, this);
}
//抽奖
void MainMapScene::Button_Lottery_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto lay = LotteryLayer::create();
    addChild(lay);
    
    lay->updateCallback=CC_CALLBACK_0(MainMapScene::updateLabel, this);
}
//商店
void MainMapScene::Button_Shop_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto lay = ShopLayer::create();
    lay->updateCallback=CC_CALLBACK_0(MainMapScene::updateLabel, this);
    this->addChild(lay);
}
//更新数量
void MainMapScene::updateLabel()
{
    float time=0.8;
    
    auto playerbll = PlayerBLL::create();
    
    int currGold=std::atoi(tCoin->getString().c_str());
    if (currGold>0) {
        auto labelAction=APDynamicLabel::create(time, currGold, playerbll->getPlayerGold());
        tCoin->runAction(labelAction);
    }else{
        tCoin->setString(StringUtils::format("%d",playerbll->getPlayerGold()));
    }
    
    int currDia=std::atoi(tDiamond->getString().c_str());
    if (currDia>0) {
        auto labelAction=APDynamicLabel::create(time, currDia, playerbll->getPlayerDia());
        tDiamond->runAction(labelAction);
    }else{
        tDiamond->setString(StringUtils::format("%d",playerbll->getPlayerDia()));
    }
    
    if (m_SumPower) {
        int currPower=std::atoi(m_SumPower->getString().c_str());
        int power=0;
        auto pb=PlayerBLL::create();
        for (int i=0; i<HeroModel_MaxData; i++) {
            if (pb->getIsBuyHero(i)) {
                auto hero=GameObjectFactory::getHero(i);
                power+=hero->getHeroModel()->CurrPower;
            }
        }
        if (currPower>0) {
            auto labelAction=APDynamicLabel::create(time, currPower, power);
            m_SumPower->runAction(labelAction);
        }else{
            m_SumPower->setString(StringUtils::format("%d",power));
        }
    }
}
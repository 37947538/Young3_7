//
//  GameUILayer.cpp
//  hero3_2
//
//  Created by liuye on 14-8-21.
//
//

#include "GameUILayer.h"
#include "APLibHeader.h"
#include "HudLayer.h"
#include "APSystem.h"
#include "GameBLL.h"
#include "APMessage.h"
#include "HeroStateIdle.h"
#include "HeroBase.h"
#include "APGameTools.h"
#include "ButtonHelper.h"
#include "SkillModel.h"
#include "IUIControl.h"

using namespace cocostudio::timeline;

GameUILayer::~GameUILayer()
{
    
}

bool GameUILayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    m_BatterNumberLabel = static_cast<Layout*>(CSLoader::createNode("ComboLayer.csb"));
    this->addChild(m_BatterNumberLabel);
    m_BatterNumberLabel->setVisible(false);
    linkNumb= (ui::TextBMFont*)m_BatterNumberLabel->getChildByTag(20);
    linkNumb->setString("0");

    m_RootNode = static_cast<Layout*>(CSLoader::createNode("GameUILayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    //英雄头像
    heroImg=dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(m_RootNode, "Image_1"));
    m_LvLabel=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "t_LV"));
    
    auto changeHeroBtn=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_qiehuan"));
    if (changeHeroBtn) {
        changeHeroBtn->addTouchEventListener(CC_CALLBACK_2(GameUILayer::Button_QieHuan_BtnOnTouch, this));
        //如果不存在辅助英雄就不显示切换英雄按钮
        if (GameBLL::instance()->vectorHero.size() < 2) {
            changeHeroBtn->setVisible(false);
        }
    }
    
    for (int i=0; i<4; i++) {
        auto btnName=__String::createWithFormat("Button_attack_%d", i+1);
        auto btn=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, btnName->getCString()));
        if (btn) {
            btn->setTag(i);
            btn->addTouchEventListener(CC_CALLBACK_2(GameUILayer::skillAttack_ButtonOnTouch, this));
            uiSkills.pushBack(btn);
        }
    }
    auto Button_Pause=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Pause"));
    if (Button_Pause) {
        Button_Pause->addTouchEventListener(CC_CALLBACK_2(GameUILayer::Button_Pause_BtnOnTouch, this));
    }
    m_LeftButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_left"));
    if (m_LeftButton) {
        m_LeftButton->setTouchEnabled(false);
    }
    m_RightButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_right"));
    if (m_RightButton) {
        m_RightButton->setTouchEnabled(false);
    }
    Button_Attack=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Attack"));
    if (Button_Attack) {
        Button_Attack->addTouchEventListener(CC_CALLBACK_2(GameUILayer::Button_Attack_BtnOnTouch, this));
    }

    //暂停按钮
    m_PauseButton=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Pause"));
    m_PauseButton->setTouchEnabled(true);
    m_PauseButton->addTouchEventListener(CC_CALLBACK_2(GameUILayer::pauseButtonOnTouch, this));
    //m_PauseButton->setPosition(apccp(0.9, 0.9));
    this->addChild(m_PauseButton);
    
    //连击文字图片
    m_BatterTitle=Sprite::create("font/lianji_hit_1.png");
    m_BatterTitle->setPosition(apccp(0.15f, 0.6f));
    m_BatterTitle->setScale(0.7f);
    m_BatterTitle->setVisible(false);
    this->addChild(m_BatterTitle,kGameTopZ);
    //hit
    auto hitSpr=Sprite::create("font/lianji_hit.png");
    hitSpr->setPosition(aprateccp(m_BatterTitle, 0.1, 0.5));
    m_BatterTitle->addChild(hitSpr);
    
    //GO提示
    auto imgGO = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(m_RootNode, "img_GO"));
    if (imgGO) {
        imgGO->setVisible(false);
        addChild(imgGO);
    }
    
    //连击进度条
    m_LoadProgress=ProgressTimer::create(Sprite::create("imgs/jiazaiditiao.png"));              //创建一个进程条
    m_LoadProgress->setAnchorPoint(Vec2(1.0,0.5));                                              //设置锚点
    m_LoadProgress->setBarChangeRate(Point(1,0));                                               //设置进程条的变化速率
    m_LoadProgress->setType(ProgressTimer::Type::BAR);                                          //设置进程条的类型
    m_LoadProgress->setMidpoint(Point(1,0));                                                    //设置进度的运动方向
    m_LoadProgress->setPosition(apccp(0.95, 0.6));                                              //设置位置
    m_LoadProgress->setPercentage(100.0f);                                                      //设置初始值
    m_LoadProgress->setVisible(false);
    this->addChild(m_LoadProgress,kGameTopZ);

    m_HpBar=dynamic_cast<ui::LoadingBar*>(Helper::seekWidgetByName(m_RootNode,"HealthBar"));
    m_ExpBar=dynamic_cast<ui::LoadingBar*>(Helper::seekWidgetByName(m_RootNode,"ManaBar"));
    //添加血条内数字
    curhp = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode,"currHP"));
    curhp->setContentSize(Size(300, 130));
    maxhp = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode,"maxHP"));
    curexp = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode,"currExp"));
    maxexp = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode,"maxExp"));

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameUILayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameUILayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameUILayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameUILayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool GameUILayer::onTouchBegan(Touch *touch, Event * event)
{
    auto pos=touch->getLocation();
    updateDirection(pos, Widget::TouchEventType::BEGAN);
    
    return true;
}

void GameUILayer::onTouchMoved(Touch *touch, Event * event)
{
    auto pos=touch->getLocation();
    updateDirection(pos, Widget::TouchEventType::MOVED);
}

void GameUILayer::onTouchCancelled(Touch *touch, Event * event)
{
    auto pos=touch->getLocation();
    updateDirection(pos, Widget::TouchEventType::CANCELED);
}

void GameUILayer::onTouchEnded(Touch *touch, Event * event)
{
    auto pos=touch->getLocation();
    updateDirection(pos, Widget::TouchEventType::ENDED);
}

void GameUILayer::updateDirection(const Vec2 &pos, Widget::TouchEventType type)
{
    if (type==Widget::TouchEventType::BEGAN || type==Widget::TouchEventType::MOVED) {
        auto leftBtnRect=m_LeftButton->getBoundingBox();
        auto leftBtnWorldPos=m_RootNode->convertToWorldSpace(m_LeftButton->getPosition());
        leftBtnRect.origin.x=leftBtnWorldPos.x - leftBtnRect.size.width * 0.5;
        leftBtnRect.origin.y=leftBtnWorldPos.y - leftBtnRect.size.height * 0.5;
        if (leftBtnRect.containsPoint(pos)) {
            Button_right_BtnOnTouch(m_RightButton, Widget::TouchEventType::ENDED);
            Button_left_BtnOnTouch(m_LeftButton, type);
        }
        
        auto rightBtnRect=m_RightButton->getBoundingBox();
        auto rightBtnWorldPos=m_RootNode->convertToWorldSpace(m_RightButton->getPosition());
        rightBtnRect.origin.x=rightBtnWorldPos.x - rightBtnRect.size.width * 0.5;
        rightBtnRect.origin.y=rightBtnWorldPos.y - rightBtnRect.size.height * 0.5;
        if (rightBtnRect.containsPoint(pos)) {
            Button_left_BtnOnTouch(m_LeftButton, Widget::TouchEventType::ENDED);
            Button_right_BtnOnTouch(m_RightButton, type);
        }
    }else{
        if (GameBLL::instance()->getButtonState(AttackButtonType::btLeft)){
            Button_left_BtnOnTouch(m_LeftButton, type);
        }
        if (GameBLL::instance()->getButtonState(AttackButtonType::btRight)){
            Button_right_BtnOnTouch(m_RightButton, type);
        }
    }
}

//切换
void GameUILayer::Button_QieHuan_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    GameBLL::instance()->changeHero();
    
    for (int i=0; i<4; i++) {
        auto btn=uiSkills.at(i);
        btn->removeAllChildren();
        setSkillButtonTouchEnabled(btn);
        
        auto skillModel=&GameBLL::instance()->m_MainHero->skills[i];
        float cdTime=skillModel->CurrCDTime;
        if (cdTime>0.0) {
            float percent=100 - (cdTime / skillModel->CdTime) * 100;
            setButtonProgressTimer(btn,cdTime,percent);
        }
    }
}

//技能攻击
void GameUILayer::skillAttack_ButtonOnTouch(Ref* sender,Widget::TouchEventType type)
{
    if (type==Widget::TouchEventType::BEGAN) {
        auto state=GameBLL::instance()->m_MainHero->getBodyState();
        if (state==GameEnum::BodyState::Idle || state==GameEnum::BodyState::Run) {
            
            auto btn=static_cast<Button*>(sender);
            int iTag=btn->getTag();
            
            auto attackType=AttackButtonType::btAttackNone;
            if (iTag==0) {
                attackType=AttackButtonType::btAttackA;
            }else if (iTag==1) {
                attackType=AttackButtonType::btAttackB;
            }else if (iTag==2){
                attackType=AttackButtonType::btAttackC;
            }else if (iTag==3){
                attackType=AttackButtonType::btAttackD;
            }
            
            ButtonHelper::buttonRed(sender, type);
            GameBLL::instance()->setUITouch(attackType, type);
            setButtonProgressTimer(btn);
        }
    }
}

//攻击A
void GameUILayer::Button_attack_1_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    GameBLL::instance()->setUITouch(AttackButtonType::btAttackA, type);

    if (type==Widget::TouchEventType::BEGAN) {
        auto state=GameBLL::instance()->m_MainHero->getBodyState();
        if (state==GameEnum::BodyState::Idle || state==GameEnum::BodyState::Run){
            auto btn=(Button*)sender;
            setButtonProgressTimer(btn);
        }
    }
}
//攻击B
void GameUILayer::Button_attack_2_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    GameBLL::instance()->setUITouch(AttackButtonType::btAttackB, type);

    if (type==Widget::TouchEventType::BEGAN) {
        if (GameBLL::instance()->m_MainHero->getBodyState()!=GameEnum::BodyState::Skill){
            auto btn=(Button*)sender;
            setButtonProgressTimer(btn);
        }
    }
}
//攻击C
void GameUILayer::Button_attack_3_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    GameBLL::instance()->setUITouch(AttackButtonType::btAttackC, type);

    if (type==Widget::TouchEventType::BEGAN) {
        if (GameBLL::instance()->m_MainHero->getBodyState()!=GameEnum::BodyState::Skill){
            auto btn=(Button*)sender;
            setButtonProgressTimer(btn);
        }
    }
}
//攻击D
void GameUILayer::Button_attack_4_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    GameBLL::instance()->setUITouch(AttackButtonType::btAttackD, type);

    if (type==Widget::TouchEventType::BEGAN) {
        if (GameBLL::instance()->m_MainHero->getBodyState()!=GameEnum::BodyState::Skill){
            auto btn=(Button*)sender;
            setButtonProgressTimer(btn);
        }
    }
}
//普通攻击
void GameUILayer::Button_Attack_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    GameBLL::instance()->setUITouch(AttackButtonType::btAttack, type);
}
//暂停按钮
void GameUILayer::Button_Pause_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
}
//左移动按钮
void GameUILayer::Button_left_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    GameBLL::instance()->setUITouch(AttackButtonType::btLeft, type);
}
//右移动按钮
void GameUILayer::Button_right_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    GameBLL::instance()->setUITouch(AttackButtonType::btRight, type);
}
//消息响应函数
bool GameUILayer::handleMessage(const APMessage& msg)
{
    //游戏胜利消息
    if (msg.Msg==kMessageTypeGameWin) {
        runWinArmature();
    }
    return true;
}
//暂停按钮事件
void GameUILayer::pauseButtonOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender, type);
    if (type==Widget::TouchEventType::ENDED) {
        GameBLL::instance()->gamePause();
    }
}
//恢复游戏
void GameUILayer::resumeGame(Ref *sender)
{
    /*
    auto layer=static_cast<PopPauseLayer*>(sender);
    if (layer) {
        layer->removeFromParentAndCleanup(true);
        //发送恢复游戏消息
        kMessageManager->DispatchMsg(0.0f, m_ID, kGameBLLID, kMessageTypeResumeGame, this);
    }*/
}
//重新游戏
void GameUILayer::restartGame(Ref *sender)
{
    auto layer=static_cast<APPopLayer*>(sender);
    if (layer) {
        layer->removeFromParentAndCleanup(true);
        //发送重新游戏消息
        //kMessageManager->DispatchMsg(0.0f, m_ID, kGameBLLID, kMessageTypeRestartGame, this);
    }
}
//运行开始动画
void GameUILayer::runStartArmature()
{
    auto func=[&](){
        //播放声音
        //SoundBLL::getInstance()->playEffect(kStartGameArmSound);
        //m_StartArmature->getAnimation()->play("kaishizhandou");
    };
    auto call=CallFunc::create(func);
    this->runAction(Sequence::create(DelayTime::create(1.5),call, NULL));
}
//运行胜利动画
void GameUILayer::runWinArmature()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("data/guge/win_donghua.ExportJson");
    auto arm=Armature::create("win_donghua");
    arm->getAnimation()->play("win");
    arm->setPosition(apccp(0.5, 0.5));
    arm->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(GameUILayer::movementCallback, this));
    this->addChild(arm);
}
void GameUILayer::movementCallback(Armature *armature, MovementEventType type, const std::string& movementID)
{
    if (type == COMPLETE){
        armature->removeFromParentAndCleanup(true);
        if (movementID.compare("win")==0) {
            //auto layer=PopWinLayer::create();
            //this->addChild(layer, kGameTopZ);
        }
    }
}
//设置警告提示
void GameUILayer::setWarningTips(const Vec2 &pos, float time)
{
    m_TipsIcon->setVisible(true);
    m_TipsIcon->setPosition(pos);
    m_TipsIcon->stopAllActions();
    //晃动动画
    auto seq=Sequence::create(RotateTo::create(0.3, 45),RotateTo::create(0.3, -45), NULL);
    m_TipsIcon->runAction(RepeatForever::create(seq));
    //定时移除
    m_TipsIcon->runAction(Sequence::create(DelayTime::create(time),Hide::create(), NULL));
}
//设置连击提示
void GameUILayer::setBatterTips(int number)
{
    auto callback=[&]()
    {
        GameBLL::instance()->resetComboCount();
        m_BatterNumberLabel->setVisible(false);
        m_BatterNumberLabel->stopAllActions();
    };
    m_BatterNumberLabel->stopAllActions();
    m_BatterNumberLabel->setVisible(true);    
    auto text=StringUtils::format("*%d",number);
    linkNumb->setString(text);
    ActionTimeline* action = CSLoader::createTimeline("ComboLayer.csb");
    action->gotoFrameAndPlay(0,true);
    action->setLastFrameCallFunc(callback);
    m_BatterNumberLabel->runAction(action);
}
//设置全部按钮显示状态
void GameUILayer::setAllButtonVisible(bool bVisible)
{
    m_PauseButton->setVisible(bVisible);
    m_HudLayer->setVisible(bVisible);
}
//设置技能按钮显示状态(count隐藏技能按钮数量)
void GameUILayer::setSkillButtonVisible(bool bVisible, int count)
{
    m_HudLayer->setSkillButtonVisible(bVisible, count);
}
//获得英雄状态
void GameUILayer::updateHeroState(HeroBase* hero, bool isRunAction)
{
    auto hm = hero->getHeroModel();
    
    auto lvString=__String::createWithFormat("%d",hm->LV);
    m_LvLabel->setString(lvString->getCString());
    
    updateUIHPNum(hm->CurrHp, hm->MaxHp, isRunAction);
    updateUIEXPNum(hm->CurrExp, hm->NextExp, isRunAction);
}
//更新头像
void GameUILayer::updateHeroImg(HeroBase* hero)
{
    heroImg->loadTexture(hero->getHeroModel()->ImgFile);
    Button_Attack->loadTextureNormal(hero->getHeroModel()->CommonAttackImg);
    Button_Attack->loadTexturePressed(hero->getHeroModel()->CommonAttackImg);
    for (int i=0; i<4; i++) {
        uiSkills.at(i)->loadTextureNormal(hero->skills[i].IconPath);
        uiSkills.at(i)->loadTexturePressed(hero->skills[i].IconPath);
        uiSkills.at(i)->loadTextureDisabled(hero->skills[i].IconPath);
    }
}
//更新UI数值显示
void GameUILayer::updateUIHPNum(int n_hp,int n_maxhp, bool isRunAction)
{
    auto currHpStr=__String::createWithFormat("%d",n_hp < 0 ? 0 : n_hp);
    auto maxHpStr=__String::createWithFormat("%d",n_maxhp);
    
    curhp->setString(currHpStr->getCString());
    maxhp->setString(maxHpStr->getCString());
    
    float toPercent=((float)n_hp / (float)n_maxhp) * 100.0;
    if (isRunAction) {
        m_HpBar->stopAllActions();
        float currPercent=m_HpBar->getPercent();
        m_HpBar->runAction(APLoadingBarFromTo::create(0.1, currPercent, toPercent));
    }else{
        m_HpBar->setPercent(toPercent);
    }
}
//更新UI数值显示
void GameUILayer::updateUIEXPNum(int n_exp,int n_maxexp, bool isRunAction)
{
    auto currExpStr=__String::createWithFormat("%d",n_exp);
    auto maxExpStr=__String::createWithFormat("%d",n_maxexp);
    curexp->setString(currExpStr->getCString());
    maxexp->setString(maxExpStr->getCString());
    
    float toPercent=((float)n_exp / (float)n_maxexp) * 100.0;
    if (isRunAction) {
        m_ExpBar->stopAllActions();
        float currPercent=m_ExpBar->getPercent();
        m_ExpBar->runAction(APLoadingBarFromTo::create(0.1, currPercent, toPercent));
    }else{
        m_ExpBar->setPercent(toPercent);
    }
}

//设置技能按钮冷却时间
void GameUILayer::setButtonProgressTimer(Button* sender, float cdTime, float percent)
{
    sender->setTouchEnabled(false);
    sender->setBright(false);
    sender->setColor(Color3B::RED);
    
    int iTag=sender->getTag();
    
    auto skillModel=&GameBLL::instance()->m_MainHero->skills[iTag];
    if (cdTime==0.0) {
        cdTime=skillModel->CdTime;
    }    
    
    auto spr=Sprite::create(skillModel->IconPath);
    auto progress=ProgressTimer::create(spr);
    progress->setType(ProgressTimer::Type::RADIAL);
    progress->setPosition(aprateccp(sender, 0.5, 0.5));
    progress->setPercentage(percent);
    progress->setLocalZOrder(0);
    sender->addChild(progress);
    //显示剩余时间
    auto timeLabel=Label::create();
    timeLabel->setSystemFontSize(24);
    timeLabel->setTextColor(Color4B::GREEN);
    timeLabel->setPosition(aprateccp(progress, 0.5, 0.5));
    progress->addChild(timeLabel);
    
    auto call=CallFunc::create(CC_CALLBACK_0(GameUILayer::setSkillButtonTouchEnabled, this, sender));
    //执行动画
    auto action=Sequence::create(APProgressTo::create(cdTime, 100, timeLabel),call,RemoveSelf::create(),NULL);
    progress->runAction(action);
}
//设置技能按钮Touch
void GameUILayer::setSkillButtonTouchEnabled(Button* sender)
{
    sender->setTouchEnabled(true);
    sender->setBright(true);
    sender->setColor(Color3B::WHITE);
}
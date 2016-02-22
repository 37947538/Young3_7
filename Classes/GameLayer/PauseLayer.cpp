#include "PauseLayer.h"
#include "APSystem.h"
#include "GameBLL.h"
#include "GameStatePause.h"

Scene* PauseLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = PauseLayer::create();
    scene->addChild(layer);
    return scene;
}
// on "init" you need to initialize your instance
bool PauseLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("PauseLayer.csb"));
    this->addChild(m_RootNode);
    
    auto effectBtn=dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_RootNode, "CheckBox_yinxiao"));
    if (effectBtn) {
        effectBtn->addEventListener(CC_CALLBACK_2(PauseLayer::effectButtonOnTouch, this));
    }
    auto musicBtn=dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_RootNode, "CheckBox_yinyue"));
    if (musicBtn) {
        musicBtn->addEventListener(CC_CALLBACK_2(PauseLayer::musicButtonOnTouch, this));
    }
    auto Button_Resume=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_RESUME"));
    if (Button_Resume) {
        Button_Resume->addTouchEventListener(CC_CALLBACK_2(PauseLayer::Button_Resume_BtnOnTouch, this));
    }
    auto Button_QUIT=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_QUIT"));
    if (Button_QUIT) {
        Button_QUIT->addTouchEventListener(CC_CALLBACK_2(PauseLayer::Button_QUIT_BtnOnTouch, this));
    }
    
    //声音状态
    auto soundBLL=SoundBLL::getInstance();
    musicBtn->setSelected(soundBLL->isMusicMute());
    effectBtn->setSelected(soundBLL->isEffectMute());
    
    return true;
}
void PauseLayer::effectButtonOnTouch(Ref* sender,CheckBox::EventType type)
{
    //播放音效
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    auto box=(CheckBox*)sender;
    box->runAction(Sequence::create(ScaleTo::create(0.1, 0.8),ScaleTo::create(0.1, 1.2),ScaleTo::create(0.1, 1.0), NULL));
    //声音状态
    auto soundBLL=SoundBLL::getInstance();
    bool bEffect=soundBLL->isEffectMute();
    soundBLL->setEffectMute(!bEffect);
}
void PauseLayer::musicButtonOnTouch(Ref* sender,CheckBox::EventType type)
{
    //播放音效
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    auto box=(CheckBox*)sender;
    box->runAction(Sequence::create(ScaleTo::create(0.1, 0.8),ScaleTo::create(0.1, 1.2),ScaleTo::create(0.1, 1.0), NULL));
    //声音状态
    auto soundBLL=SoundBLL::getInstance();
    bool bSound=soundBLL->isMusicMute();
    soundBLL->setMusicMute(!bSound);
}
void PauseLayer::Button_Resume_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    GameBLL::instance()->getFSM()->backState();
    this->removeFromParentAndCleanup(true);
}

void PauseLayer::Button_QUIT_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    GameBLL::destory();
    APSystem::getInstance()->sendEvent(APEventMainMap);
}
void PauseLayer::onEnter()
{
    PopBase::onEnter();
    
    GameBLL::instance()->getFSM()->changeState(GameStatePause::instance());
}
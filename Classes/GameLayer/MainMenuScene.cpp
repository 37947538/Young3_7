//
//  MainMapScene.cpp
//  Zombie3_4
//
//  Created by jl on 15/6/3.
//
//

#include "MainMenuScene.h"
#include "APSystem.h"


Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}
// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("MainMenuScene.csb"));
    this->addChild(m_RootNode);
    
    auto Button_play=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_PLAY"));
    if (Button_play) {
        Button_play->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::Button_play_BtnOnTouch, this));
    }
    auto Button_quit=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_QUIT"));
    if (Button_quit) {
        Button_quit->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::Button_quit_BtnOnTouch, this));
    }
    return true;
}
//开始游戏
void MainMenuScene::Button_play_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    APSystem::getInstance()->sendEvent(APEventMainMap);
}
//退出
void MainMenuScene::Button_quit_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    Director::getInstance()->end();
}

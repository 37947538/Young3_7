//
//  APSystem.cpp
//  Cat3_4
//
//  Created by yuankang on 15/6/3.
//
//

#include "APSystem.h"
#include "MainMenuScene.h"
#include "MainMapScene.h"
#include "GameBLL.h"
#include "LevelModel.h"
#include "LevelModelBLL.h"
#include "EquipLayer.h"
#include "ChooseCharacterLayer.h"
#include "LoadingScene.h"
#include "LevelBLL.h"

static APSystem *_sharedAPSystem;

APSystem* APSystem::getInstance()
{
    if (nullptr == _sharedAPSystem)
    {
        _sharedAPSystem = new APSystem();
    }
    return _sharedAPSystem;
}

void APSystem::destroyInstance()
{
    CC_SAFE_DELETE(_sharedAPSystem);
}

APSystem::APSystem(void)
{
    
}

APSystem::~APSystem(void)
{
    
}

void APSystem::sendEvent(APEvent event, void* obj)
{
    switch (event) {
        case APEventLogo:               //加载封面场景
        {
            //auto logo=MainScene::createScene();
            //Director::getInstance()->replaceScene(logo);
        }break;
        case APEventChoosePeople:   //选择人物
        {
            auto chooseLayer=ChooseCharacterLayer::createScene();
            Director::getInstance()->replaceScene(chooseLayer);
        }break;
        case APEventGame:               //加载游戏场景
        {
            GameBLL::destory();
            //加载场景
            auto loadingScene=LoadingScene::createScene(obj);
            Director::getInstance()->replaceScene(loadingScene);
        }break;
        case APEventMainMap:            //加载大地图场景
        {
            GameBLL::destory();
            auto mainMap=MainMapScene::createScene();
            Director::getInstance()->replaceScene(mainMap);
        }break;
        case APEventMain:               //加载主界面场景
        {
            auto main=MainMenuScene::createScene();
            Director::getInstance()->replaceScene(main);
        }break;
        case APEventPrepare:            //加载准备场景
        {
            auto test=new LevelModel;
            auto gameScene=GameBLL::instance()->createGame(test);
            Director::getInstance()->replaceScene(gameScene);
            //auto prepare=prepareScene::createScene();
            //Director::getInstance()->replaceScene(prepare);
        }break;
        case APEventEquip:              //装备
        {
            auto gameScene=EquipLayer::createScene();
            Director::getInstance()->replaceScene(gameScene);
        }break;
        case APEventDevelop:            //改装界面
        {
            //auto develop=DevelopLayer::createScene();
            //Director::getInstance()->replaceScene(develop);
        }break;
        case APEventRestart:           //重新开始
        {
            int currID=LevelBLL::instance()->getPlayerSelecLevelID();
            std::vector<int> seleHero=LevelBLL::instance()->heroIDs;
            int isTry=LevelBLL::instance()->getIsTryGame();
            //等待释放资源
            GameBLL::destory();
            
            LevelBLL::instance()->setPlayerSelecLevelID(currID);
            LevelBLL::instance()->setIsTryGame(isTry);
            LevelBLL::instance()->heroIDs=seleHero;
            //加载场景
            auto loadingScene=LoadingScene::createScene(obj);
            Director::getInstance()->replaceScene(loadingScene);
        }break;
        default:
            break;
    }
}


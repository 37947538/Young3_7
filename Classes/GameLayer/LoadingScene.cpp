#include "LoadingScene.h"
#include "APSystem.h"
#include "LevelBLL.h"
#include "LevelModelBLL.h"
#include "GameBLL.h"
#include "EnemyModelBLL.h"
#include "ActionFileModelBLL.h"

LoadingScene* LoadingScene::create(void* obj)
{
    LoadingScene *pRet = new(std::nothrow) LoadingScene();
    if (pRet && pRet->init(obj))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Scene* LoadingScene::createScene(void* obj){
    auto scene = Scene::create();
    auto layer = LoadingScene::create(obj);
    if (scene) {
        scene->addChild(layer);
        return scene;
    }
    return NULL;
}

bool LoadingScene::init(void* obj)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("LoadingScene.csb"));
    this->addChild(m_RootNode);
    
    m_LoadProgress=dynamic_cast<ui::LoadingBar*>(Helper::seekWidgetByName(m_RootNode,"LoadingBar_loding"));
    m_LoadProgress->setPercent(0);
    
    return true;
}

void LoadingScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    
    int seleID=LevelBLL::instance()->getPlayerSelecLevelID();
    //如果是测试
    if (LevelBLL::instance()->getIsTryGame()) {
        seleID=0;
        LevelBLL::instance()->setPlayerSelecLevelID(seleID);
    }
    LevelModelBLL *lmb=LevelModelBLL::create(kModelWritablePath);
    auto lm=&(lmb->modelData[seleID]);
    LevelBLL::instance()->parse(lm);
    
    auto enemyIndexs=LevelBLL::instance()->enemyIDs;
    totalNum=(int)enemyIndexs.size();
    std::set<int>::iterator set_iter=enemyIndexs.begin();
    for(;set_iter!=enemyIndexs.end();set_iter++) {
        int enemyIndex=*set_iter;
        
        EnemyModelBLL *emb=EnemyModelBLL::create(kModelWritablePath);
        auto pEnemyModel=&(emb->modelData[enemyIndex]);
        int iActionFileModelID=pEnemyModel->ActionFileModelID;
        
        auto amb=ActionFileModelBLL::create(kModelWritablePath);
        int iActionFileModeIndex=iActionFileModelID - 1;
        auto aModel=&amb->modelData[iActionFileModeIndex];
        m_ArmNameVector.push_back(aModel->ArmName);
    }
    
    addImg();
}

void LoadingScene::onEnter()
{
    Layer::onEnter();
    /*
    auto func=[&](){
        this->removeFromParentAndCleanup(true);
    };
    m_LoadProgress->runAction(Sequence::create(APLoadingBarFromTo::create(1.0, 0, 100),CallFunc::create(func), NULL));
     */
}
void LoadingScene::addImg()
{
    std::string arnName=m_ArmNameVector.at(currentNum);
    auto filePath=__String::createWithFormat("guge/%s0.png",arnName.c_str());
    auto textureCache=Director::getInstance()->getTextureCache();
    textureCache->addImageAsync(filePath->getCString(),CC_CALLBACK_1(LoadingScene::plistImageAsyncCallback, this));
}
void LoadingScene::plistImageAsyncCallback(Texture2D* texture)
{
    std::string arnName=m_ArmNameVector.at(currentNum);
    auto filePath=__String::createWithFormat("guge/%s0.plist",arnName.c_str());
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filePath->getCString(), texture);
    
    currentNum++;
    //计算进度条当前的百分比
    float newPercent = ((float)currentNum/(float)totalNum)*100.0f;
    m_LoadProgress->setPercent(newPercent);
    //如果当前加载的张数跟总数相等则进行场景跳转
    if (currentNum == totalNum) {
        auto func=[&](){
            int seleID=LevelBLL::instance()->getPlayerSelecLevelID();
            LevelModelBLL *lmb=LevelModelBLL::create(kModelWritablePath);
            auto lm=&(lmb->modelData[seleID]);
            
            auto gameScene=GameBLL::instance()->createGame(lm);
            Director::getInstance()->replaceScene(gameScene);
            GameBLL::instance()->gameStart();
        };
        
        this->runAction(Sequence::create(DelayTime::create(0.1),CallFunc::create(func), NULL));
    }else{
        addImg();
    }
}

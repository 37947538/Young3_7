/**
 k_ClassDes
 */

#include "GameBLL.h"
#include "GameUILayer.h"
#include "GameLayer.h"
#include "PauseLayer.h"
#include "EnemyBase.h"
#include "BTRenderableNode.h"
#include "EnemyAI.h"
#include "APDirectorSpeedAction.h"
#include "EnemyModel.h"
#include "RewardEquipBLL.h"
#include "PlayerBLL.h"
#include "AttackObject.h"
#include "LevelBLL.h"
#include "GameStateReadly.h"
#include "GameStateRun.h"
#include "WinLayer.h"
#include "GameObjectFactory.h"
#include "BulletObject.h"
#include "HeroBevTreeHeader.h"
#include "LoadingScene.h"
#include "PopOverLayer.h"
#include "APSystem.h"
#include "EffectBLL.h"
#include "UpgradeSystem.h"
#include "PopFinishBuyHeroLayer.h"
#include "BulletBLL.h"

static GameBLL *_sharedGameBLL=nullptr;

GameBLL* GameBLL::instance()
{
    if (nullptr == _sharedGameBLL)
    {
        _sharedGameBLL = new GameBLL();
    }
    return _sharedGameBLL;
}

void GameBLL::destory()
{
    if (_sharedGameBLL) {
        CC_SAFE_DELETE(_sharedGameBLL);
    }
}

//构造函数
GameBLL::~GameBLL()
{
    delete m_rewardEquipBll;
    delete m_LevelModel;
    delete m_pGameState;
    LevelBLL::instance()->destory();
    BulletBLL::getInstance()->destroyInstance();
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

//希构函数
GameBLL::GameBLL()
{
    m_WeaponIndexVector.clear();
    m_rewardEquipBll=new RewardEquipBLL();
    m_LevelModel=new LevelModel();
    m_pGameState=new StateMachine<GameBLL>(this);
    getFSM()->setCurrState(GameStateReadly::instance());
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

//创建游戏对象(LevelModel关卡模型)
Scene* GameBLL::createGame(LevelModel* arg1)
{
    //拷贝数据模型
    memcpy(m_LevelModel,arg1,sizeof(LevelModel));
    
    LevelBLL::instance()->parse(arg1);
    //TODO:
    auto scene=Scene::create();
    
    //增加游戏层
    m_GameLayer=new GameLayer();
    m_GameLayer->autorelease();
    scene->addChild(m_GameLayer);
    m_GameLayer->loadData(arg1);
    
    //选择上场英雄
    for (int i=0; i<LevelBLL::instance()->heroIDs.size(); i++) {
        auto hero=GameObjectFactory::getHero(LevelBLL::instance()->heroIDs.at(i));
        hero->setMainHero(false);
        addHero(hero);
        if (i==0) {
            m_MainHero=hero;
            m_MainHero->setMainHero(true);
        }
    }

    m_GameUILayer=GameUILayer::create();
    scene->addChild(m_GameUILayer);
    m_GameUILayer->updateHeroState(m_MainHero, false);
    m_GameUILayer->updateHeroImg(m_MainHero);
    
    return scene;
}

//切换英雄
void GameBLL::changeHero()
{
    if (vectorHero.size() == 1) {
        return;
    }
    
    //英雄已经死亡不能切换
    if (vectorHero.size() == 2) {
        if(vectorHero.at(1)->getBodyState()==GameEnum::BodyState::Die)
            return;
    }
    
    vectorHero.reverse();
    m_MainHero=vectorHero.at(0);
    vectorHero.at(0)->setMainHero(true);
    if (vectorHero.size() > 1) {
        vectorHero.at(1)->setMainHero(false);
    }
    
    m_GameLayer->setViewScreeCenter(m_MainHero->getPosition());
    m_GameUILayer->updateHeroState(m_MainHero, false);
    m_GameUILayer->updateHeroImg(m_MainHero);
}

//准备游戏
void GameBLL::gameReady()
{
   //TODO:
}

//游戏开始
void GameBLL::gameStart()
{
    getFSM()->changeState(GameStateRun::instance());
    //TODO:
}

//游戏暂停
void GameBLL::gamePause()
{
   //TODO:
    PauseLayer *pause=PauseLayer::create();
    pause->setLocalZOrder(kGameTopZ);
    m_GameUILayer->addChild(pause);
}

//游戏恢复
void GameBLL::gameResue()
{
   //TODO:
}

//游戏胜利
void GameBLL::gameWin()
{
    //试玩
    if (LevelBLL::instance()->getIsTryGame()) {
        int heroIndex=m_MainHero->getHeroModel()->HeroID - 1;
        auto pop=PopFinishBuyHeroLayer::create();
        pop->setHeroIndex(heroIndex);
        m_GameUILayer->addChild(pop);
    }else{
        //奖励钻石固定为1
        m_CurrLevelGetDia=1;
        //每关固定经验奖励 = (（关卡序号—1）^2+20)/*4
        int addExp=((m_LevelModel->LevelID - 1) * (m_LevelModel->LevelID - 1) + 20) * 4;
        //给英雄加经验
        for (auto &h : vectorHero) {
            h->addExp(addExp);
            m_CurrLevelGetExp+=addExp;
        }
        //每关固定金钱奖励 = 100+20*ROUNDDOWN(关卡号/5)+关卡号*5
        int gold=100 + 20 * (m_LevelModel->LevelID / 5) + m_LevelModel->LevelID * 5;
        m_CurrLevelGetGold+=gold;
        //保存的开启关卡ID从0开始,模型里的关卡ID是从1开始
        int openLevelID=m_LevelModel->LevelID;
        bool isBossLevel=LevelBLL::instance()->getIsBossLevel();
        auto pb=PlayerBLL::create();
        pb->addDia(m_CurrLevelGetDia);
        pb->addGold(gold);
        pb->setOpenLevelID(openLevelID,isBossLevel);
        
        auto win=WinLayer::create();
        m_GameUILayer->addChild(win);
    }
}

//游戏失败
void GameBLL::gameOver()
{
   //TODO:
    auto callback=[&](Ref *pSender)
    {
        auto popOver=(PopOverLayer*)pSender;
        if(popOver->getTypeID()==1)    //重新开始
        {
            APSystem::getInstance()->sendEvent(APEventRestart);
        }
        if(popOver->getTypeID()==2)     //返回大地图
        {
            GameBLL::destory();
            APSystem::getInstance()->sendEvent(APEventMainMap);
        }
        if(popOver->getTypeID()==3)     //复活
        {
            heroRelive();
            getFSM()->changeState(GameStateRun::instance());
            animateScale(Vec2::ZERO,1.0,0.01);
            popOver->removeFromParentAndCleanup(true);
        }
    };
    getFSM()->changeState(GameStateReadly::instance());
    
    auto overLayer=PopOverLayer::create();
    overLayer->enterCallback=callback;
    m_GameUILayer->addChild(overLayer);
}

//游戏重新开始
void GameBLL::gameRestart()
{
   //TODO:
}

//游戏主循环
void GameBLL::update(float arg1)
{
    getFSM()->updateTime(arg1);

    //防止出界
    if (m_MainHero) {
        if(m_MainHero->getPositionX() < 0)
        {
            m_MainHero->setPositionX(0);
        }
        float r=GameBLL::instance()->m_GameLayer->getMapMoveWidth();
        if (m_MainHero->getPositionX() > r) {
            m_MainHero->setPositionX(r);
        }
    }
}

//英雄攻击
void GameBLL::attackForHero(HeroBase* hb,AttackObject* a)
{
    m_GameLayer->getMapLayer()->drawOBB(a->getOBB());
    
    bool isDoubleHit=false; //是否连击
    Rect attRect=a->getAttRange();
    for (auto &e : vectorEnemy) {
        if (e->getBodyState()==GameEnum::BodyState::Die){
            continue;
        }
        if (e->getOBB()->isCollidWithAPOBB(a->getOBB())) {
            auto att=a->clone();
            e->beAttack(att);
            isDoubleHit=true;
        }
    }
    //连击
    if (isDoubleHit && hb==m_MainHero) {
        viewComboCount();
    }
}

//更新子弹业务
void GameBLL::updateBullets(float arg1)
{
    BulletBLL::getInstance()->update(arg1);
}

//敌兵攻击
void GameBLL::attackForEnemy(AttackObject* eb)
{
    Rect attRect=eb->getAttRange();
    for (auto &h : vectorHero) {
        Vec2 v=h->getPosition();
        if (v.x > attRect.origin.x && v.x < attRect.origin.x + attRect.size.width) {
            auto att=eb->clone();
            h->beAttack(att);
        }
    }
}

//增加英雄对象
void GameBLL::addHero(HeroBase* arg1)
{
    vectorHero.pushBack(arg1);
    arg1->setLocalZOrder(kGameTopZ);
    m_GameLayer->addGameObject(arg1);
}

//移除英雄
void GameBLL::removeHero(HeroBase* arg1)
{
    if (vectorHero.size()==1) {
        auto scaleCall=CallFunc::create(CC_CALLBACK_0(GameBLL::animateScale, this, m_MainHero->getPosition(), 1.0, 1.2));
        auto winCall=CallFunc::create(CC_CALLBACK_0(GameBLL::gameOver, this));
        auto speedCall=CallFunc::create(CC_CALLBACK_0(GameBLL::animateSpeed, this, 1.0));
        m_GameLayer->runAction(Sequence::create(scaleCall, speedCall, DelayTime::create(1.0), winCall, NULL));
        return;
    }
    vectorHero.eraseObject(arg1);
    arg1->removeFromParentAndCleanup(true);
}

//关卡碰撞检测-是否出怪
void GameBLL::updateLevelCollision(float arg1)
{
    static float dropTime=0;
    dropTime+=arg1;
    if (dropTime>0.5 && vectorEnemy.empty() && !LevelBLL::instance()->getEnemyGroup()->enemys.empty()) {
        dropTime=0.0;
        const Vec2 heroPos=m_MainHero->getPosition();
        Vector<EnemyGroup*> es;
        LevelBLL::instance()->getEnemyRect(heroPos, es);
        Vector<FiniteTimeAction*> arrayOfActions;
        for (auto &e : es) {
            auto call=CallFunc::create(CC_CALLBACK_0(GameBLL::addEnemyConfig, this, e->enemyRectString, e->mapRect));
            arrayOfActions.pushBack(call);
            arrayOfActions.pushBack(DelayTime::create(CCRANDOM_0_1()));
        }
        if (!arrayOfActions.empty()) {
            m_GameLayer->runAction(Sequence::create(arrayOfActions));
        }
    }
}

//增加敌兵通过配置文件
void GameBLL::addEnemyConfig(const std::string& sc, Rect mapRect)
{
    Rect enemyConfig=RectFromString(sc);
    int iEnemyNum=enemyConfig.size.width;           //敌兵数量
    
    Vector<FiniteTimeAction*> arrayOfActions;
    for (int i=0; i<iEnemyNum; i++) {
        auto call=CallFunc::create(CC_CALLBACK_0(GameBLL::readyAddEnemy, this, enemyConfig));
        arrayOfActions.pushBack(call);
        arrayOfActions.pushBack(DelayTime::create(CCRANDOM_0_1()));
    }
    if (!arrayOfActions.empty()) {
        m_GameLayer->runAction(Sequence::create(arrayOfActions));
    }
    //设置地图移动宽度
    m_GameLayer->setMapMoveWidth(mapRect.origin.x + mapRect.size.width);
}

//准备增加敌兵
void GameBLL::readyAddEnemy(const Rect& enemyConfig)
{
    auto heroPos=m_MainHero->getPosition();
    auto heroWorldPos=m_GameLayer->getMapLayer()->convertToWorldSpace(heroPos);
    
    int iEnemyID=enemyConfig.origin.x;              //敌兵ID
    int iEnemyLv=enemyConfig.origin.y;              //敌兵等级
    int iEnemyType=enemyConfig.size.height;         //出兵类型
    //增加敌兵
    EnemyBase *eb=GameObjectFactory::getEnemy(iEnemyID, iEnemyLv);
    
    //出兵坐标
    float xStart=heroPos.x - heroWorldPos.x;
    float xEnd=xStart + 1280;
    //默认掉落出兵
    float xRand=APTools::getRandFloat(xStart+100, xEnd-100);
    if (iEnemyType==2) {    //左侧出兵
        xRand=APTools::getRandFloat(xStart, xStart-400);
    }else if(iEnemyType==3){    //右侧出兵
        xRand=APTools::getRandFloat(xEnd, xEnd+400);
    }
    Vec2 enemyPos=Vec2(xRand,LevelBLL::instance()->getLevelHeight());
    eb->puton(enemyPos);
    //设置排序ID
    eb->setOrderID((int)vectorEnemy.size());
    this->addEnemy(eb);
    //出兵特效
    if (iEnemyType==1) {
        EffectBLL::getInstance()->addEffect(m_GameLayer->getMapLayer(), "effect_14", enemyPos);
        shake(0.3, 8, 8);;
    }
}

//增加敌兵
void GameBLL::addEnemy(EnemyBase* arg1)
{
    //TODO:
    m_GameLayer->addGameObject(arg1);
    vectorEnemy.pushBack(arg1);
    
    static bool isFirst=false;
    if (!isFirst) {
        isFirst=true;
    }
}

//移除敌人
void GameBLL::removeEnemy(EnemyBase* arg1)
{
    //TODO:
    m_GameLayer->removeGameObject(arg1);
    vectorEnemy.eraseObject(arg1);
    
    //重新排序
    for (int i=0; i<vectorEnemy.size(); i++) {
        vectorEnemy.at(i)->setOrderID(i);
    }
    
    if (vectorEnemy.size()<=0) {
        if (LevelBLL::instance()->getEnemyGroup()->enemys.empty()) {
            auto scaleCall=CallFunc::create(CC_CALLBACK_0(GameBLL::animateScale, this, m_MainHero->getPosition(), 1.0, 1.2));
            auto speedCall=CallFunc::create(CC_CALLBACK_0(GameBLL::animateSpeed, this, 1.0));
            auto winCall=CallFunc::create(CC_CALLBACK_0(GameBLL::gameWin, this));
            m_GameLayer->runAction(Sequence::create(scaleCall, speedCall, DelayTime::create(1.0), winCall, NULL));
        }else{
            //实现移动位置
            auto eRects=LevelBLL::instance()->getEnemyGroup()->enemys.at(0)->mapRect;
            float lastWidth=m_GameLayer->getMapMoveWidth();
            float newWidth=eRects.origin.x + eRects.size.width;
            if (lastWidth<newWidth) {
                //log("show go--------");
                EffectBLL::getInstance()->addShowGo(m_GameUILayer);
                
                m_GameLayer->setMapMoveWidth(newWidth);
            }
        }
    }
}

//怪将要死亡
void GameBLL::enemyWillDie(EnemyBase* eb)
{
    //试玩不掉装备
    if (!LevelBLL::instance()->getIsTryGame()) {
        //如果是BOSS关必掉一个装备
        if (LevelBLL::instance()->getIsBossLevel()) {
            m_rewardEquipBll->dropOneEquip(eb);
        }else{
            //随机掉落金币或装备
            m_rewardEquipBll->randDrop(eb);
        }
        //增加经验值
        int addExp=eb->getEnemyModel()->DropExp;
        //给英雄加经验
        for (auto &h : vectorHero) {
            h->addExp(addExp);
            m_CurrLevelGetExp+=addExp;
        }
    }
    
    m_GameUILayer->updateHeroState(m_MainHero);
    
    if (LevelBLL::instance()->getEnemyGroup()->enemys.empty()) {
        bool isAllDie=true;
        for (auto &e : vectorEnemy) {
            if (e->getBodyState()!=GameEnum::BodyState::Die) {
                isAllDie=false;
            }
        }
        if (isAllDie) {
            animateSpeed(0.4);
            animateScale(m_MainHero->getPosition(),1.5,0.5);
        }
    }
}

//英雄将要死亡
void GameBLL::heroWillDie(HeroBase* eb)
{
    if (vectorHero.size()==1) {
        //TODO:: 减速
        animateSpeed(0.4);
        animateScale(m_MainHero->getPosition(),1.5,0.5);
        EffectBLL::getInstance()->addDieEffect(m_GameLayer);
        return;
    }
    if (eb->getMainHero()) {
        changeHero();
    }
}

//增加钱
void GameBLL::addMoney(int i)
{
    Vec2 vPos=m_MainHero->getPosition();
    m_GameLayer->addCoinTips(vPos, 70, i, kGameTopZ);
    
    PlayerBLL *pb=PlayerBLL::create();
    pb->addGold(i);
    
    m_CurrLevelGetGold+=i;
}

//颤屏
void GameBLL::shake(int shakeLv)
{
    //m_GameLayer->shake(0.8, 10, 10+(shakeLv-1)*20);
    switch (shakeLv) {
        case 1:
        {
            m_GameLayer->shake(0.3, 5, 5);
        }break;
        case 2:
        {
            m_GameLayer->shake(0.5, 8, 8);
        }break;
        case 3:
        {
            m_GameLayer->shake(0.5, 12, 12);
        }break;
        default:
            break;
    }
}

//颤屏
void GameBLL::shake(float dt, float x, float y)
{
    m_GameLayer->shake(dt, x, y);
}

//减速
void GameBLL::animateSpeed(float ft)
{
    /*
    auto runOne=[&](float tm){
        log("%f",tm);
        auto _schedule = Director::getInstance()->getScheduler();
        _schedule->unschedule("xiaota", this);
        Director::getInstance()->getScheduler()->setTimeScale(1);
    };
    auto _schedule = Director::getInstance()->getScheduler();
    _schedule->schedule(runOne, this, ft, false, "xiaota");
    Director::getInstance()->getScheduler()->setTimeScale(0.4);
     */
    Director::getInstance()->getScheduler()->setTimeScale(ft);
}
//放大
void GameBLL::animateScale(Vec2 pos,float scale,float time)
{
    auto bg=m_GameLayer->getMapLayer();
    float bgScale=bg->getScale();
    auto bgSize=bg->getBoundingBox().size;
    auto anchorRote=Vec2((pos.x*bgScale)/bgSize.width,(pos.y*bgScale)/bgSize.height);
    bg->setAnchorPoint(anchorRote);
    bg->runAction(ScaleTo::create(time, scale));
}
//英雄复活
void GameBLL::heroRelive()
{
    //清空英雄，纪录位置
    Vec2 lastPos=Vec2::ZERO;
    for (auto &h : vectorHero) {
        lastPos=h->getPosition();
        h->removeFromParentAndCleanup(true);
    }
    vectorHero.clear();
    
    //选择上场英雄
    for (int i=0 ; i< LevelBLL::instance()->heroIDs.size(); i++) {
        auto hero=GameObjectFactory::getHero(LevelBLL::instance()->heroIDs.at(i));
        hero->setMainHero(false);
        addHero(hero);
        if (i==0) {
            m_MainHero=hero;
            m_MainHero->setMainHero(true);
        }
        hero->setPosition(lastPos);
    }
    
    m_GameUILayer->updateHeroState(m_MainHero);
}

//显示连击数
void GameBLL::viewComboCount()
{
    m_GameUILayer->setBatterTips(++nCombo);
}

//设置屏幕滚动中心点
void GameBLL::setViewScreeCenter()
{
    auto pos=m_MainHero->getPosition();
    m_GameLayer->setViewScreeCenter(pos);
}

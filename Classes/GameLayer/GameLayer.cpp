/**
 k_ClassDes
 */

#include "GameLayer.h"
#include "GameBLL.h"
#include "HeroBase.h"
#include "APShakeAction.h"
#include "APDynamicLabel.h"
#include "APTools.h"
#include "APScatterAction.h"
#include "EquipmentLocalBLL.h"
#include "LevelBLL.h"

#define kMoveLeftPosition   450.0f     //可以移动左边边界
#define kMoveRightPositon   550.0f     //可以移动的右边边界
#define kAPShakeActionTag   7788

using namespace cocostudio::timeline;

//构造函数
GameLayer::GameLayer()
{
    //CCArmature
    m_MapMoveWidth=1280;
}

//希构函数
GameLayer::~GameLayer()
{
    
}

//加载数据模型
void GameLayer::loadData(LevelModel* arg1)
{
    m_WinSize=Director::getInstance()->getWinSize();
    m_MapMoveWidth=m_WinSize.width;
    
    int bgWidth=LevelBLL::instance()->getLevelWidth(arg1);
    m_LevelModel=arg1;
    m_Background=LevelBLL::instance()->getLevelLayer(arg1, bgWidth, 800);
    this->addChild(m_Background);
}

//增加游戏对象
void GameLayer::addGameObject(Node* mObj)
{
    m_Background->addChild(mObj,mObj->getLocalZOrder()+10);
}

//删除游戏对象
void GameLayer::removeGameObject(Node* mObj)
{
    m_Background->removeChild(mObj, true);
}

//滚动屏幕
void GameLayer::scroolViewScree()
{
    //获取地图的坐标
    auto mapPosX=m_Background->getPositionX();

    auto hero=GameBLL::instance()->m_MainHero;
    auto heroPos=hero->getPosition();
    auto heroVector=hero->getVelocity();
    //求屏幕移动点
    auto mapPos=m_Background->getPosition();
    mapPos.x=-heroPos.x;
    
    //获取屏幕的对应点
    float screenX=heroPos.x + mapPosX;
    
    if ((screenX > kMoveRightPositon && heroVector.x > 0) || (screenX < kMoveLeftPosition && heroVector.x < 0)) {
        setMapPostion(Vec2(-heroVector.x,0));
    }
}

//设置屏幕滚动中心点
void GameLayer::setViewScreeCenter(const Vec2& center)
{
    auto mapPos=Vec2(-center.x+m_WinSize.width * 0.5,0);
    if (mapPos.x > 0) {
        mapPos.x=0;
    }
    if (mapPos.x < -m_MapMoveWidth+m_WinSize.width) {
        mapPos.x=-m_MapMoveWidth+m_WinSize.width;
    }
    m_Background->runAction(MoveTo::create(0.2, mapPos));
}

//设置地图位置
void GameLayer::setMapPostion(const Vec2& mapDiffPos)
{
    auto mapPos=m_Background->getPosition()+mapDiffPos;
    float startPos=0;    //起点坐标
    float endPos=-m_MapMoveWidth+m_WinSize.width;    //终点位置
    if (mapPos.x <=startPos && mapPos.x >= endPos) {
        m_Background->setPosition(mapPos);
    }
}

//获取地图矩形
Rect GameLayer::getMapRect() const
{
    return m_Background->getBoundingBox();
}

//获取数据模型
LevelModel* GameLayer::getLevelModel()
{
   return m_LevelModel;
}

//屏幕晃动
void GameLayer::shake(float dt, float x, float y)
{
    auto action=(APShakeAction*)this->getActionByTag(kAPShakeActionTag);
    if (!action) {
        action=APShakeAction::createWithStrength(dt, x, y);
        action->setTag(kAPShakeActionTag);
        this->runAction(action);
    }
}
//飘血数字
void GameLayer::subCurrHp(Vec2 vec,int delta,long demage,int zOrder)
{
    auto m_beattackLayer = static_cast<Layout*>(CSLoader::createNode("beattackLayer.csb"));
    m_beattackLayer->setZOrder(kGameTopZ+100);
    m_beattackLayer->setPosition(vec-Vec2(m_WinSize.width * 0.5 + CCRANDOM_0_1()*50*CCRANDOM_MINUS1_1(), 150));
    m_Background->addChild(m_beattackLayer);

    auto linkNumb=(ui::TextBMFont*)m_beattackLayer->getChildByTag(22);
    auto str=__String::createWithFormat("-%ld",demage);
    linkNumb->setString(str->getCString());
    linkNumb->setColor(Color3B(169, 0, 0));
    
    auto callback=[=](){
        m_beattackLayer->stopAllActions();
        m_beattackLayer->removeFromParentAndCleanup(true);
    };
    ActionTimeline* action = CSLoader::createTimeline("beattackLayer.csb");
    action->gotoFrameAndPlay(0,true);
    action->setLastFrameCallFunc(callback);
    m_beattackLayer->runAction(action);
}
//加血数字
void GameLayer::addHpNumber(Vec2 vec,int addHp)
{
    auto m_beattackLayer = static_cast<Layout*>(CSLoader::createNode("beattackLayer.csb"));
    m_beattackLayer->setZOrder(kGameTopZ+100);
    m_beattackLayer->setPosition(vec-Vec2(m_WinSize.width * 0.5, 200));
    m_Background->addChild(m_beattackLayer);
    
    auto linkNumb= (ui::TextBMFont*)m_beattackLayer->getChildByTag(22);
    auto str=__String::createWithFormat("+%d",addHp);
    linkNumb->setString(str->getCString());
    linkNumb->setColor(Color3B::GREEN);
    
    auto callback=[=](){
        m_beattackLayer->stopAllActions();
        m_beattackLayer->removeFromParentAndCleanup(true);
    };
    
    ActionTimeline* action = CSLoader::createTimeline("beattackLayer.csb");
    action->gotoFrameAndPlay(0,true);
    action->setLastFrameCallFunc(callback);
    m_beattackLayer->runAction(action);
}
void GameLayer::crops(Vec2 vec){
    float height = APTools::getRandFloat(200,350);
    //旋转物品 如金币
    for (int ncur=0; ncur<APTools::getRand(4, 20); ncur++) {
        auto spr = Sprite::create("imgs/jinbi_2.png");
        auto pos = vec;
        m_Background->addChild(spr);
        spr->setPosition(pos);
        auto apscatt = APScatterAction::create(height,0.2);
        auto blink = Blink::create(1, 2);
        auto blink2 = Blink::create(1, 3);
        auto sqe = Sequence::create(apscatt,DelayTime::create(3.5f),blink,blink2,RemoveSelf::create(), NULL);
        spr->runAction(sqe);
    }
    for (int ncur=0; ncur<APTools::getRand(0, 3); ncur++) {
        std::string w =StringUtils::format("imgs/weapon/knife_%d.png",APTools::getRand(1, 5));
        auto spr = Sprite::create(w);
        auto pos = vec;
        m_Background->addChild(spr);
        spr->setPosition(pos);
        auto apscatt = APScatterAction::create(height);
        auto blink = Blink::create(1, 4);
        auto blink2 = Blink::create(1, 5);
        auto sqe = Sequence::create(apscatt,DelayTime::create(4.5f),blink,blink2,RemoveSelf::create(), NULL);
        spr->runAction(sqe);
    }
}
//加钱提示
void GameLayer::addCoinTips(Vec2 vec,int delta,int icoin,int zOrder)
{
    auto str=__String::createWithFormat("coin%d",icoin);
    auto font=LabelBMFont::create(str->getCString(), "font/hit.fnt");
    font->setColor(Color3B(230,220,120));
    auto randx=APTools::getRand(-delta,delta);
    auto randy=APTools::getRand(-delta/2,delta/2);
    font->setPosition(vec+Vec2(randx, randy+200));
    //font->setScale(0.5);
    m_Background->addChild(font,zOrder);
    auto endAction=Spawn::create(FadeOut::create(0.15),ScaleBy::create(0.15, 0.1),NULL);
    auto seq=Sequence::create(MoveBy::create(0.15, Vec2(0, 50)),DelayTime::create(0.15f),endAction,RemoveSelf::create(), NULL);
    font->runAction(seq);
}
//加经验提示
void GameLayer::addExpTips(Vec2 vec,int delta,int iexp,int zOrder){
    auto str=__String::createWithFormat("+%d",iexp);
    auto font=LabelBMFont::create(str->getCString(), "font/hit.fnt");
    font->setColor(Color3B(235,214,180));
    auto randx=APTools::getRand(-delta,delta);
    auto randy=APTools::getRand(-delta/2,delta/2);
    font->setPosition(vec+Vec2(randx, randy+200));
    //font->setColor(Color3B::GRAY);
    //font->setScale(0.5);
    m_Background->addChild(font,zOrder);
    auto endAction=Spawn::create(FadeOut::create(0.25),ScaleBy::create(0.25, 0.1),NULL);
    auto seq=Sequence::create(MoveBy::create(0.25, Vec2(0, 50)),DelayTime::create(0.75f),endAction,RemoveSelf::create(), NULL);
    font->runAction(seq);
}
//拾取装备提示
void GameLayer::addEquiptips(Vec2 vec,DropEquip* equip)
{
    DropEquip* p = DropEquip::create(equip->getWeaponIndex());
    p=equip->clone();
    m_Background->addChild(p);
    p->setPosition(vec+Vec2(0, 230));
    auto endAction=Spawn::create(FadeOut::create(0.25),ScaleBy::create(0.25, 0.1),NULL);
    auto seq=Sequence::create(MoveBy::create(0.15, Vec2(0, 40)),DelayTime::create(0.25f),endAction,RemoveSelf::create(), NULL);
    p->runAction(seq);
}

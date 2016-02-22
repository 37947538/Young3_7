#include "ChooseCharacterLayer.h"
#include "APLibHeader.h"
#include "PlayerModel.h"
#include "PlayerModelBLL.h"
#include "APSystem.h"
#include "PlayerBLL.h"
#include "PopTipsLayer.h"
#include "PopBuyHeroLayer.h"
#include "ButtonHelper.h"
#include "LevelBLL.h"

using namespace cocostudio::timeline;

Scene* ChooseCharacterLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChooseCharacterLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

ChooseCharacterLayer::~ChooseCharacterLayer()
{
}

ChooseCharacterLayer::ChooseCharacterLayer()
{
}
// on "init" you need to initialize your instance
bool ChooseCharacterLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("ChooseCharacterLayer.csb"));
    
    this->addChild(m_RootNode);
    
    ActionTimeline* action = CSLoader::createTimeline("ChooseCharacterLayer.csb");
    action->gotoFrameAndPlay(0);
    m_RootNode->runAction(action);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto Button_fanhui=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_fanhui"));
    if (Button_fanhui) {
        Button_fanhui->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterLayer::Button_fanhui_BtnOnTouch, this));
    }
    auto Button_kaishi=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_kaishi"));
    if (Button_kaishi) {
        Button_kaishi->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterLayer::Button_kaishi_BtnOnTouch, this));
    }
    
    //加粒子
    Size winSize = Director::getInstance()->getWinSize();
    ParticleSystem *kaiping=ParticleSystemQuad::create("imgs/kaipian_lizi_2.plist");
    kaiping->setPosition(apccp(0.5, 0.3));
    this->addChild(kaiping,200);
    
    setDataView();
    
    return true;
}
void ChooseCharacterLayer::setDataView()
{
    auto pb=PlayerBLL::create();
    Vec2 pos[]={Vec2(220, 70), Vec2(65,90), Vec2(195,80), Vec2(80,55)};
    for (int i=0; i<4; i++) {
        auto btnName=__String::createWithFormat("Button_juese_%d",i+1);
        auto btn=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, btnName->getCString()));
        if (btn) {
            btn->removeAllChildren();
            btn->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterLayer::playerBtnOnTouch, this));
            btn->setTag(i);
            bool isBright=pb->getIsSelectHero(i);
            btn->setBright(!isBright);
            
            //英雄是否已购买
            bool isBuy=pb->getIsBuyHero(i);
            if (!isBuy) {
                auto lockImg=ImageView::create("imgs/suo_1.png");
                lockImg->setPosition(pos[i]);
                btn->addChild(lockImg);
            }
        }
    }
}
void ChooseCharacterLayer::playerBtnOnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    ui::Button *btn=(ui::Button*)sender;
    int iTag=btn->getTag();
    /*
    if (iTag>=3) {
        PopTipsLayer::addTipLayer(this, "即将开启，敬请期待！");
        return;
    }*/
    PlayerBLL *pb=PlayerBLL::create();
    //英雄是否已购买
    bool isBuy=pb->getIsBuyHero(iTag);
    if (isBuy) {
        bool isPlayBll=pb->getIsSelectHero(iTag);
        if (!isPlayBll) {
            int selectHeroCount=(int)pb->getSelectMainHero().size();
            if (selectHeroCount>=2) {
                PopTipsLayer::addTipLayer(this, "只能选择2位英雄！");
                return;
            }
            pb->setSelectHero(iTag);
        }else{
            pb->setUnSelectHero(iTag);
        }
        btn->setBright(isPlayBll);
    }else{
        auto pop=PopBuyHeroLayer::create();
        pop->setHeroIndex(iTag);
        pop->testCallback=CC_CALLBACK_1(ChooseCharacterLayer::testHero, this);
        pop->enterCallback=CC_CALLBACK_0(ChooseCharacterLayer::setDataView, this);
        this->addChild(pop);
    }
}
void ChooseCharacterLayer::testHero(Ref* sender)
{
    auto pop=(PopBuyHeroLayer*)sender;
    int heroIndex=pop->getHeroIndex();
    //TODO::试玩
    LevelBLL::instance()->setIsTryGame(true);
    LevelBLL::instance()->heroIDs.push_back(heroIndex);
    APSystem::getInstance()->sendEvent(APEventGame);
}
void ChooseCharacterLayer::Button_fanhui_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    APSystem::getInstance()->sendEvent(APEventMainMap);
}
void ChooseCharacterLayer::Button_kaishi_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    ButtonHelper::buttonRed(sender, type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    auto pb=PlayerBLL::create();
    int selectHeroCount=(int)pb->getSelectMainHero().size();
    if (selectHeroCount<=0) {
        PopTipsLayer::addTipLayer(this, "请选择英雄！");
        return;
    }
    
    auto seleHero=pb->getSelectMainHero();
    for (auto & s : seleHero) {
        int heroID=s->getValue();
        LevelBLL::instance()->heroIDs.push_back(heroID);
    }
    
    APSystem::getInstance()->sendEvent(APEventGame);
}

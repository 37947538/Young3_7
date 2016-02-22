#include "WinLayer.h"
#include "APSystem.h"
#include "LevelModelBLL.h"
#include "LevelBLL.h"
#include "GameBLL.h"
#include "WeaponBLL.h"

using namespace cocostudio::timeline;

Scene* WinLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = WinLayer::create();
    scene->addChild(layer);
    return scene;
}
WinLayer::WinLayer()
{
    
}
WinLayer::~WinLayer()
{

}
// on "init" you need to initialize your instance
bool WinLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("WinLayer.csb"));
    this->addChild(m_RootNode);
    
    ActionTimeline* action = CSLoader::createTimeline("WinLayer.csb");
    action->gotoFrameAndPlay(0, false);
    m_RootNode->runAction(action);
    
    auto expLabel=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "Text_jingyanzhhi"));
    if (expLabel) {
        auto expString=__String::createWithFormat("%d",GameBLL::instance()->m_CurrLevelGetExp);
        expLabel->setString(expString->getCString());
    }
    auto goldLabel=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "Text_jinbishu"));
    if (goldLabel) {
        auto goldString=__String::createWithFormat("%d",GameBLL::instance()->m_CurrLevelGetGold);
        goldLabel->setString(goldString->getCString());
    }
    auto diaLabel=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "Text_zuanshishu"));
    if (diaLabel) {
        auto diaString=__String::createWithFormat("%d",GameBLL::instance()->m_CurrLevelGetDia);
        diaLabel->setString(diaString->getCString());
    }
    
    m_ScrollView=dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_RootNode, "ScrollView_zhuangbei"));
    
    Button_jixu=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_jixu"));
    if (Button_jixu) {
        Button_jixu->addTouchEventListener(CC_CALLBACK_2(WinLayer::Button_jixu_BtnOnTouch, this));
    }
    Button_fanhui=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_fanhui"));
    if (Button_fanhui) {
        Button_fanhui->addTouchEventListener(CC_CALLBACK_2(WinLayer::Button_fanhui_BtnOnTouch, this));
    }
    
    setDataView();
    
    return true;
}
void WinLayer::setDataView()
{
    //如果是BOSS关卡
    if (LevelBLL::instance()->getIsBossLevel()) {
        Button_jixu->setVisible(false);
    }
    //计算起点
    Vec2 origPoint=Vec2(40,40);
    //偏移间距
    Vec2 diffV=Vec2(90,0);
    
    int count=(int)GameBLL::instance()->m_WeaponIndexVector.size();
    float maxWdith=origPoint.x + count * diffV.x;
    auto size=m_ScrollView->getInnerContainerSize();
    if (size.width<maxWdith) {
        size.width=maxWdith;
        m_ScrollView->setInnerContainerSize(size);
    }
    
    for (int i=0; i<count; i++) {
        int equipIndex=GameBLL::instance()->m_WeaponIndexVector.at(i);
        auto wBLL=WeaponBLL::create(kModelWritablePath);
        auto model=&wBLL->modelData[equipIndex];
        
        auto pos=origPoint + Vec2(i * diffV.x,0);
        auto bg=ImageView::create("imgs/wupinkuang_1.png");
        bg->setPosition(pos);
        m_ScrollView->addChild(bg);
        
        auto img=ImageView::create(model->ImgFile);
        img->setPosition(aprateccp(bg, 0.5, 0.5));
        bg->addChild(img);
    }
}
void WinLayer::Button_jixu_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    int nextLevelID=LevelBLL::instance()->getPlayerSelecLevelID() + 1;
    if (nextLevelID>LevelModel_MaxData) {
        nextLevelID=0;
    }
    bool isTryGame=LevelBLL::instance()->getIsTryGame();
    std::vector<int> hersid=LevelBLL::instance()->heroIDs;
    GameBLL::instance()->destory();
    LevelBLL::instance()->setIsTryGame(isTryGame);
    LevelBLL::instance()->setPlayerSelecLevelID(nextLevelID);
    LevelBLL::instance()->heroIDs=hersid;
    APSystem::getInstance()->sendEvent(APEventGame);
}
void WinLayer::Button_fanhui_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    APSystem::getInstance()->sendEvent(APEventMainMap);
}
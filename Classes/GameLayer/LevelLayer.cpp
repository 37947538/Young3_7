#include "LevelLayer.h"
#include "ButtonHelper.h"
#include "LevelBLL.h"
#include "APSystem.h"
#include "PlayerBLL.h"
#include "LevelModelBLL.h"

// on "init" you need to initialize your instance
bool LevelLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !PopBase::init() )
    {
        return false;
    }
    
    m_WinSize=Director::getInstance()->getWinSize();
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("LevelLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto sv=dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_RootNode, "ScrollView_guanka"));
    if (sv) {
        sv->setVisible(false);
    }
    
    m_ScrollView=APScrollView::create(Size(770, 270));
    m_ScrollView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
    m_ScrollView->setPosition(Vec2(255,220));
    m_ScrollView->setBounceable(false);
    m_ScrollView->setDelegate(this);
    m_RootNode->addChild(m_ScrollView);
    
    auto pb=PlayerBLL::create();
    int iOpenLevelID=pb->getOpenLevelID();
    //计算起点
    Vec2 origPoint=Vec2(73,135);
    m_MaxWorldID=(iOpenLevelID / 5) + 1;
    for (int i=0; i<m_MaxWorldID; i++) {
        for (int j=0; j<5; j++) {
            int index=i*5+j;
            int x=(index * 155) + origPoint.x;
            auto btn=Button::create("imgs/xiaoguan_1.png","imgs/xiaoguan_1.png");
            btn->setTag(index);
            btn->addTouchEventListener(CC_CALLBACK_2(LevelLayer::LevelButton_OnTouch, this));
            btn->setPosition(Vec2(x, origPoint.y));
            btn->setSwallowTouches(false);
            m_ScrollView->addChild(btn);
            
            if (index>iOpenLevelID) {
                btn->setTouchEnabled(false);
                auto img=ImageView::create("imgs/tb_xiaoguan_suo.png");
                img->setPosition(aprateccp(btn, 0.5, 0.5));
                img->setLocalZOrder(200);
                btn->addChild(img);
            }else if (index==iOpenLevelID){
                auto img=ImageView::create("imgs/xiaoguan_1_1.png");
                img->setPosition(aprateccp(btn, 0.5, 0.5));
                btn->addChild(img);
            }
            
            auto iconName=__String::create("imgs/tb_xiaoguan_1.png");
            if (j==3) {
                iconName=__String::create("imgs/tb_xiaoguan_2.png");
            }else if (j==4){
                iconName=__String::create("imgs/tb_xiaoguan_3.png");
            }
            auto icon=ImageView::create(iconName->getCString());
            icon->setPosition(aprateccp(btn, 0.5, 0.5));
            icon->setLocalZOrder(100);
            btn->addChild(icon);
        }
    }

    m_ScrollView->setContentSize(Size(m_MaxWorldID * 5 * 155, 640));
    //设置当前位置
    m_CurrPageIndex=m_MaxWorldID;
    Vec2 newPos=Vec2(-(m_CurrPageIndex-1)*775,0);
    m_ScrollView->setContentOffset(newPos,false);
    
    m_TitleLabel=dynamic_cast<Text*>(Helper::seekWidgetByName(m_RootNode, "Text_zhangjie_1"));
    if (m_TitleLabel) {
        m_TitleLabel->setString(__String::createWithFormat("第%d章",m_MaxWorldID)->getCString());
    }
    
    auto Button_Close=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (Button_Close) {
        Button_Close->addTouchEventListener(CC_CALLBACK_2(LevelLayer::Button_Close_BtnOnTouch, this));
    }
    Button_fanye_1=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_fanye_1"));
    if (Button_fanye_1) {
        Button_fanye_1->addTouchEventListener(CC_CALLBACK_2(LevelLayer::Button_fanye_1_BtnOnTouch, this));
    }
    Button_fanye_2=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_fanye_2"));
    if (Button_fanye_2) {
        Button_fanye_2->addTouchEventListener(CC_CALLBACK_2(LevelLayer::Button_fanye_2_BtnOnTouch, this));
    }
    
    setPageButtonVisible();
    
    return true;
}
void LevelLayer::LevelButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender,type);
    if (type==Widget::TouchEventType::ENDED && m_ScrollView->isTouchMoved()==false){
        SoundBLL::getInstance()->playEffect(kButtonSound);
        auto btn=(Button*)sender;
        int iLevelIndex=btn->getTag();
        if (iLevelIndex>=LevelModel_MaxData) {
            iLevelIndex=0;
        }
        LevelBLL::instance()->setPlayerSelecLevelID(iLevelIndex);
        APSystem::getInstance()->sendEvent(APEventChoosePeople);
    }
}
void LevelLayer::Button_Close_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    ButtonHelper::buttonRed(sender,type);
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectClose);
    this->removeFromParentAndCleanup(true);
}
void LevelLayer::Button_fanye_1_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    m_CurrPageIndex--;
    setPageShow();
}
void LevelLayer::Button_fanye_2_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    m_CurrPageIndex++;
    setPageShow();
}
void LevelLayer::setPageButtonVisible()
{
    //上一页按钮
    if (m_CurrPageIndex<=1) {
        Button_fanye_1->setVisible(false);
    }else{
        Button_fanye_1->setVisible(true);
    }
    //下一页按钮
    if (m_CurrPageIndex>=m_MaxWorldID) {
        Button_fanye_2->setVisible(false);
    }else{
        Button_fanye_2->setVisible(true);
    }
}
void LevelLayer::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
    //log("LevelLayer::scrollViewDidScroll()");
    if (view->isDragging()) {
        m_IsBeginDrag=true;
    }else{
        if (m_IsBeginDrag) {
            m_IsBeginDrag=false;
            APScrollView *apTab=(APScrollView*)view;
            float fDiff=apTab->startPos.x - apTab->endPos.x;
            if (std::abs(fDiff)>50){
                if (fDiff<0) {
                    m_CurrPageIndex--;
                }else if(fDiff>0){
                    m_CurrPageIndex++;
                }
            }
            //设置关卡不能出界
            if (m_CurrPageIndex<1) {
                m_CurrPageIndex=1;
            }
            if (m_CurrPageIndex>m_MaxWorldID) {
                m_CurrPageIndex=m_MaxWorldID;
            }
            setPageShow();
        }
    }
}
void LevelLayer::setPageShow()
{
    m_ScrollView->setTouchEnabled(false);
    Button_fanye_1->setTouchEnabled(false);
    Button_fanye_2->setTouchEnabled(false);
    int pageIndex=m_CurrPageIndex-1;
    //设置当前位置
    Vec2 newPos=Vec2(-pageIndex*775,0);
    m_ScrollView->setContentOffsetInDuration(newPos,0.4);
    
    auto func=[&](){
        setPageButtonVisible();
        if (m_TitleLabel) {
            m_TitleLabel->setString(__String::createWithFormat("第%d章",m_CurrPageIndex)->getCString());
        }
    };
    auto funcPageButton=[&](){
        m_ScrollView->setTouchEnabled(true);
        Button_fanye_1->setTouchEnabled(true);
        Button_fanye_2->setTouchEnabled(true);
    };
    auto seq=Sequence::create(DelayTime::create(0.3),CallFunc::create(func),DelayTime::create(0.1),CallFunc::create(funcPageButton), NULL);
    this->runAction(seq);
}
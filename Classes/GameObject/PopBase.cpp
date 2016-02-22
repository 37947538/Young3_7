//
//  PopBase.cpp
//  Tower3_4
//
//  Created by liuye on 15/5/13.
//
//

#include "PopBase.h"

bool PopBase::init()
{
    if (!Layer::init()) {
        return  false;
    }
    m_WinSize=Director::getInstance()->getWinSize();
    
    auto layerColor=LayerColor::create(kPopLayerColor);
    this->addChild(layerColor,-kGameTopZ);
    
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(PopBase::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
bool PopBase::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    return m_IsToptouch;
}
void PopBase::onEnter()
{
    Layer::onEnter();
}
void PopBase::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}
void PopBase::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void PopBase::onExit()
{
    Layer::onExit();
}
void PopBase::removeFromParentAndCleanup(bool cleanup)
{
    Layer::removeFromParentAndCleanup(cleanup);
}
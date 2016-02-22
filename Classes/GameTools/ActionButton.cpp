//
//  ActionButton.cpp
//  SuperHero
//
//  Created by liuye on 14-8-19.
//
//

#include "ActionButton.h"
#include "APDateHelper.h"

ActionButton::ActionButton()
{
	m_pSprite = NULL;
	m_pHudLayer = NULL;
}

ActionButton::~ActionButton()
{
    
}

bool ActionButton::init(const char *szImage)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());
        
		m_pSprite = Sprite::create(szImage);
		this->addChild(m_pSprite);
        
		initTouch();
        
		bRet = true;
	} while (0);
	return bRet;
}

void ActionButton::updateProjection(void)
{
	log("");
}

void ActionButton::click()
{
	if (IsCanClick() && m_pHudLayer)
	{
		m_pHudLayer->attackButtonClick(GetAttackType());
		beganAnimation();
	}
}

void ActionButton::clickUp()
{
	endedAnimation();
}

Rect ActionButton::GetRect()
{
    Size size = m_pSprite->getContentSize();
	return  Rect(-size.width/2, -size.height/2, size.width, size.height);
}

void ActionButton::onEnter()
{
    Node::onEnter();
}

void ActionButton::onExit()
{
    Node::onExit();
}

bool ActionButton::containsTouchLocation(Touch* touch)
{
	return GetRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool ActionButton::ccTouchBegan(Touch* touch, Event* event)
{
	//log("ActionButton::ccTouchBegan");
	// 区域判断
	if (!this->containsTouchLocation(touch))
		return false;
    
	// 播放点击动画
	click();
    
	return true;
}

void ActionButton::ccTouchMoved(Touch* touch, Event* event)
{
	//log("ActionButton::ccTouchMoved");
}

void ActionButton::ccTouchEnded(Touch* touch, Event* event)
{
	//log("ActionButton::ccTouchEnded");
	endedAnimation();
}

AttackButton::AttackButton()
{
	m_fDefaultScale = 0.35;
	m_fMaxScale = 0.5;
    
	m_pNormal = Sprite::create("imgs/AttackO.png");
	m_pNormal->retain();
    
    FiniteTimeAction *pScale = ScaleTo::create(0.1, m_fDefaultScale);
    FiniteTimeAction *pFadeIn = FadeIn::create(0.1);
	m_pInAction = Spawn::create(pScale, pFadeIn, NULL);
	m_pInAction->retain();
    
	pScale = ScaleTo::create(0.2f, m_fMaxScale);
    FiniteTimeAction *pFade = FadeOut::create(0.2);
	m_pOutAction = Spawn::create(pScale, pFade, NULL);
	m_pOutAction->retain();
    
	m_fClickTime = 0.0f;
}

AttackButton::~AttackButton()
{
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pInAction);
	CC_SAFE_RELEASE(m_pOutAction);
}

bool AttackButton::init(const char *szImage)
{
	bool bRet = ActionButton::init(szImage);
	if (m_pNormal)
		m_pNormal->setScale(m_fMaxScale);
	return bRet;
}

AttackButton* AttackButton::create(const char *szImage)
{
	AttackButton *pAttackButton = new AttackButton();
	if (pAttackButton && pAttackButton->init(szImage))
	{
		pAttackButton->autorelease();
		return pAttackButton;
	}
	else
	{
		delete pAttackButton;
		return NULL;
	}
}

void AttackButton::beganAnimation()
{
	removeChild(m_pNormal);
	addChild(m_pNormal);
	m_pNormal->runAction((Action*)m_pInAction->clone());
	/*
	timeval timeVal;
	gettimeofday(&timeVal, 0);
    unsigned long curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
	m_fClickTime = (float)curTime;
     */
    m_fClickTime = APDateHelper::getTimeFloat();
}

void AttackButton::endedAnimation()
{
	m_pNormal->stopAllActions();
	m_pNormal->runAction((Action*)m_pOutAction->clone());
}

bool AttackButton::IsCanClick()
{
    return true;
    /*
	timeval timeVal;
	gettimeofday(&timeVal, 0);
	unsigned long curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
     */
    float curTime = APDateHelper::getTimeFloat();
	return (curTime - m_fClickTime > 600);
}
AttackEffect::AttackEffect(float fTime)
{
    Sprite *pCold = Sprite::create("imgs/AttackFreeze.png");
	m_pNormal = ProgressTimer::create(pCold);
	m_pNormal->setType(ProgressTimer::Type::RADIAL);
	m_pNormal->setReverseDirection(true);
	m_pNormal->setScale(0.43);
	m_pNormal->retain();
    
    FiniteTimeAction *to = ProgressTo::create(0, 99.999);
    FiniteTimeAction *to1 = ProgressTo::create(fTime, 0);
    FiniteTimeAction *callback = CallFunc::create(CC_CALLBACK_0(AttackEffect::endColdTime, this));
	m_pInAction = Sequence::create(to, to1, callback, NULL);
	m_pInAction->retain();
	m_bCanClick = true;
}

AttackEffect::~AttackEffect()
{
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pInAction);
}

AttackEffect* AttackEffect::create(const char *szImage, float fTime)
{
	AttackEffect *pAttackEffect = new AttackEffect(fTime);
	if (pAttackEffect && pAttackEffect->init(szImage))
	{
		pAttackEffect->autorelease();
		return pAttackEffect;
	}
	else
	{
		delete pAttackEffect;
		return NULL;
	}
}

void AttackEffect::beganAnimation()
{
	removeChild(m_pNormal);
	addChild(m_pNormal);
	m_pNormal->runAction((Action*)m_pInAction->clone());
	m_bCanClick = false;
}

void AttackEffect::endedAnimation()
{
	
}

bool AttackEffect::IsCanClick()
{
	return m_bCanClick;
}

void AttackEffect::endColdTime()
{
	m_bCanClick = true;
}

void ActionButton::initTouch()
{
	log("initTouch");
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(ActionButton::ccTouchBegan,this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ActionButton::ccTouchMoved,this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ActionButton::ccTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
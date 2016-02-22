//
//  ActionButton.h
//  SuperHero
//
//  Created by liuye on 14-8-19.
//
//

#ifndef __SuperHero__ActionButton__
#define __SuperHero__ActionButton__

#include <iostream>
#include "GameHeader.h"
#include "HudLayer.h"

class ActionButton : public Node
{
public:
	ActionButton();
	virtual ~ActionButton();
    
	virtual bool init(const char *szImage);
	void click();
	void clickUp();
	virtual bool IsCanClick() { return true;}
    
	// get & set
    Rect GetRect();
	AttackButtonType GetAttackType() { return m_nAttackType;}
	
	void SetAttackType(AttackButtonType nAttackType) { m_nAttackType = nAttackType;}
	void SetHudLayer(HudLayer *pHudLayer) { m_pHudLayer = pHudLayer;}
    
	void initTouch();
	void updateProjection(void);
protected:
	virtual void onEnter();
	virtual void onExit();
    
	bool containsTouchLocation(Touch* touch);
	virtual bool ccTouchBegan(Touch* touch,  Event* event);
	virtual void ccTouchMoved(Touch* touch,  Event* event);
	virtual void ccTouchEnded(Touch* touch,  Event* event);
    
	virtual void beganAnimation() {}
	virtual void endedAnimation() {}
    
    Sprite              *m_pSprite;
	AttackButtonType	m_nAttackType;
	HudLayer            *m_pHudLayer;
};

// 攻击按钮
// 普通攻击按钮的效果，初始化设置图片素材
class AttackButton : public ActionButton
{
public:
	~AttackButton();
	virtual bool init(const char *szImage);
	static AttackButton* create(const char *szImage);
	virtual bool IsCanClick();
private:
	AttackButton();
    
	virtual void beganAnimation();
	virtual void endedAnimation();
    
    Sprite          *m_pNormal;
	float			m_fDefaultScale;
	float			m_fMaxScale;
    Action          *m_pInAction;
    Action          *m_pOutAction;
	float			m_fClickTime;
};

// 攻击特效
// 特效攻击有个冷却效果，不能在一定时间范围内连续攻击，使用一个 旋转的 Progress 来达到这样的效果
class AttackEffect : public ActionButton
{
public:
	~AttackEffect();
	static AttackEffect* create(const char *szImage, float fTime);
	virtual bool IsCanClick();
private:
	AttackEffect(float fTime);
    
	virtual void beganAnimation();
	virtual void endedAnimation();
	void endColdTime();
    
    ProgressTimer		*m_pNormal;
    Action              *m_pInAction;
	bool				m_bCanClick;
};

#endif /* defined(__SuperHero__ActionButton__) */

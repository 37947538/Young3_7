//
//  HudLayer.cpp
//  SuperHero
//
//  Created by liuye on 14-8-19.
//
//

#include "HudLayer.h"
#include "ActionButton.h"

HudLayer::~HudLayer()
{
    m_pGameUILayer=NULL;
}

HudLayer::HudLayer()
{
    m_szWinSize = Director::getInstance()->getWinSize();
	m_ptCenter = Vec2(m_szWinSize.width/2, m_szWinSize.height/2);
}
bool HudLayer::init()
{
	if (!Layer::init())
    {

        return false;
    }
    // 添加攻击按钮
    m_pAttackButton = AttackButton::create("imgs/Attack.png");
    m_pAttackButton->setPosition(Vec2(m_szWinSize.width - 80, 80));
    m_pAttackButton->SetHudLayer(this);
    m_pAttackButton->SetAttackType(btAttack);
    this->addChild(m_pAttackButton);
    
    // 其他攻击
    m_pAttackButtonA = AttackEffect::create("imgs/AttackA.png", 3.0);
    m_pAttackButtonA->setPosition(Vec2(m_szWinSize.width - 220, 90));
    m_pAttackButtonA->SetHudLayer(this);
    m_pAttackButtonA->SetAttackType(btAttackA);
    this->addChild(m_pAttackButtonA);
    
    m_pAttackButtonB = AttackEffect::create("imgs/AttackB.png", 2.0);
    m_pAttackButtonB->setPosition(Vec2(m_szWinSize.width - 140, 210));
    m_pAttackButtonB->SetHudLayer(this);
    m_pAttackButtonB->SetAttackType(btAttackB);
    this->addChild(m_pAttackButtonB);
    
	return true;
}

void HudLayer::attackButtonClick(AttackButtonType nAttackType)
{
	log("attackButtonClick %d",nAttackType);
	if (m_pGameUILayer){
		//m_pGameUILayer->attackButtonClick(nAttackType);
    }
}

void HudLayer::keyAttack(AttackButtonType nButtonType)
{
	if (nButtonType == btAttack && m_pAttackButton->IsCanClick())
	{
		log("abtAttack ---");
		m_pAttackButton->click();
	}
	else if (nButtonType == btAttackA && m_pAttackButtonA->IsCanClick())
	{
		log("abtAttack a---");
		m_pAttackButtonA->click();
	}
	else if (nButtonType == btAttackB && m_pAttackButtonB->IsCanClick())
	{
		log("abtAttack b---");
		m_pAttackButtonB->click();
	}
}

void HudLayer::keyAttackUp(AttackButtonType nButtonType)
{
	if (nButtonType == btAttack)
	{
		m_pAttackButton->clickUp();
	}
}
void HudLayer::setDelegate(GameUILayer *pGameUILayer)
{
	m_pGameUILayer = pGameUILayer;
}
//设置技能按钮显示状态(count隐藏技能按钮数量)
void HudLayer::setSkillButtonVisible(bool bVisible, int count)
{
    if (count==1) {
        m_pAttackButtonA->setVisible(bVisible);
    }else if(count==2){
        m_pAttackButtonA->setVisible(bVisible);
        m_pAttackButtonB->setVisible(bVisible);
    }
}
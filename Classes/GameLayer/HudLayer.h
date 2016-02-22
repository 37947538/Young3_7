//
//  HudLayer.h
//  SuperHero
//
//  Created by liuye on 14-8-19.
//
//

#ifndef __SuperHero__HudLayer__
#define __SuperHero__HudLayer__

#include <iostream>
#include "GameHeader.h"
#include "GameUILayer.h"

class AttackButton;
class AttackEffect;


class HudLayer : public Layer

{
public :
	~HudLayer();
    HudLayer();
    CREATE_FUNC(HudLayer);
    virtual bool init();
    
    void attackButtonClick(AttackButtonType nAttackType);
	void keyAttack(AttackButtonType nButtonType);
	void keyAttackUp(AttackButtonType nButtonType);
	void setDelegate(GameUILayer *pGameLayer);
    void setSkillButtonVisible(bool bVisible, int count);       //设置技能按钮显示状态(count隐藏技能按钮数量)
protected:
	Size			m_szWinSize;
	Point			m_ptCenter;
	GameUILayer		*m_pGameUILayer;
	AttackButton	*m_pAttackButton;
	AttackEffect	*m_pAttackButtonA;
	AttackEffect	*m_pAttackButtonB;
};
#endif /* defined(__SuperHero__HudLayer__) */

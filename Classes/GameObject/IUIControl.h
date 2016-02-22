//
//  IUIControl.h
//  Zombie3_4
//  用户控制接口
//  Created by jl on 15/8/18.
//
//

#ifndef __Zombie3_4__IUIControl__
#define __Zombie3_4__IUIControl__

#include <stdio.h>
#include "GameHeader.h"

class IUIControl
{
public:
    enum class UIMoveType
    {
        UIMoveNone=0,
        UIMoveLeft,
        UIMoveRight,
    };
    enum class UIAttackType
    {
        UIAttackTypeNone=0,
        UIAttackTypeAttack,
    };
    enum class UISkillType
    {
        UIAttackTypeSkillNone=0,
        UIAttackTypeSkill1,
        UIAttackTypeSkill2,
        UIAttackTypeSkill3,
        UIAttackTypeSkill4,
    };
public:
    ~IUIControl();
    IUIControl();
    void setUITouch(AttackButtonType mType,Widget::TouchEventType btnEvent);//移动类型
    bool getButtonState(AttackButtonType mType);                            //获取按钮状态
    bool isMoveButtonPress();                                               //是否移动按钮按下
    bool isSkillButtonPress();                                              //是否技能按钮按下
    bool isAttackButtonPress();                                             //是否普通攻击按钮按下
    void resetSkillButton();                                                //重置技能按钮
protected:
    void pressButton(AttackButtonType mType);
    void cancelButton(AttackButtonType mType);
    int iUIBtValue;
};

#endif /* defined(__Zombie3_4__IUIControl__) */

//
//  IUIControl.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/18.
//
//

#include "IUIControl.h"

IUIControl::~IUIControl()
{
    
}

IUIControl::IUIControl()
{
    iUIBtValue=0;
}

//移动类型
void IUIControl::setUITouch(AttackButtonType mType,Widget::TouchEventType btnEvent)
{
    if (btnEvent==Widget::TouchEventType::BEGAN || btnEvent==Widget::TouchEventType::MOVED) {
        pressButton(mType);
    }else{
        cancelButton(mType);
    }
}

void IUIControl::pressButton(AttackButtonType mType)
{
    iUIBtValue |= (1 << (int)mType);
}

void IUIControl::cancelButton(AttackButtonType mType)
{
    //重置选择按钮状态
    iUIBtValue &= ~(1 << (int)mType);
}

//获取按钮状态
bool IUIControl::getButtonState(AttackButtonType mType)
{
    return iUIBtValue & (1 << mType);
}

//是否移动按钮按下
bool IUIControl::isMoveButtonPress()
{
    return getButtonState(AttackButtonType::btLeft) || getButtonState(AttackButtonType::btRight);
}

//是否技能按钮按下
bool IUIControl::isSkillButtonPress()
{
    return getButtonState(AttackButtonType::btAttackA) || getButtonState(AttackButtonType::btAttackB) || getButtonState(AttackButtonType::btAttackC) || getButtonState(AttackButtonType::btAttackD);
}

//重置技能按钮
void IUIControl::resetSkillButton()
{
    cancelButton(AttackButtonType::btAttackA);
    cancelButton(AttackButtonType::btAttackB);
    cancelButton(AttackButtonType::btAttackC);
    cancelButton(AttackButtonType::btAttackD);
}

//是否普通攻击按钮按下
bool IUIControl::isAttackButtonPress()
{
    return getButtonState(AttackButtonType::btAttack);
}

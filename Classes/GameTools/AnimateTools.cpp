//
//  AnimateTools.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/19.
//
//

#include "AnimateTools.h"
#include "ActionFileModel.h"

//是否有攻击动画播放
bool AnimateTools::isAttackAnimatePlaying(BaseActionObject *bo)
{
    auto actionModel=bo->getActionFileMode();
    
    //连击1
    if (bo->getAnimateState(actionModel->ActionAttackName1)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //连击2
    if (bo->getAnimateState(actionModel->ActionAttackName2)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //连击3
    if (bo->getAnimateState(actionModel->ActionAttackName3)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //连击4
    if (bo->getAnimateState(actionModel->ActionAttackName4)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //连击5
    if (bo->getAnimateState(actionModel->ActionAttackName5)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    return false;
}
//技能播放
bool AnimateTools::isSkillAnimatePlaying(BaseActionObject *bo)
{
    auto actionModel=bo->getActionFileMode();
    //技能1
    if (bo->getAnimateState(actionModel->SkillName1)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //技能2
    if (bo->getAnimateState(actionModel->SkillName2)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //技能3
    if (bo->getAnimateState(actionModel->SkillName3)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //技能4
    if (bo->getAnimateState(actionModel->SkillName4)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    return false;

}
//运行播放
bool AnimateTools::isRunAnimatePlaying(BaseActionObject *bo)
{
    auto actionModel=bo->getActionFileMode();
    
    //是否在跑动中
    if (bo->getAnimateState(actionModel->ActionRunName)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    return false;
}

//是否有被播放动画
bool AnimateTools::isBeAttackAnimatePlaying(BaseActionObject *bo)
{
    auto actionModel=bo->getActionFileMode();
    
    //是否在播放被打动画
    if (bo->getAnimateState(actionModel->ActionBeAttack1)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //是否在播放被打动画
    if (bo->getAnimateState(actionModel->ActionBeAttack2)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //是否在播放被打动画
    if (bo->getAnimateState(actionModel->ActionBeAttack3)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    //是否在播放被打动画
    if (bo->getAnimateState(actionModel->ActionBeAttackDown)==BaseActionObject::AnimateState::Runing) {
        return true;
    }
    return false;
}



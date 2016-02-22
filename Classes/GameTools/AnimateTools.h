//
//  AnimateTools.h
//  Zombie3_4
//
//  Created by jl on 15/8/19.
//
//

#ifndef __Zombie3_4__AnimateTools__
#define __Zombie3_4__AnimateTools__

#include <stdio.h>
#include "GameHeader.h"
#include "BaseActionObject.h"

class AnimateTools{
public:
    static bool isAttackAnimatePlaying(BaseActionObject *bo);            //是否有攻击动画播放
    static bool isSkillAnimatePlaying(BaseActionObject *bo);             //技能播放
    static bool isRunAnimatePlaying(BaseActionObject *bo);               //运行播放
    static bool isBeAttackAnimatePlaying(BaseActionObject *bo);          //被击播放

};


#endif /* defined(__Zombie3_4__AnimateTools__) */

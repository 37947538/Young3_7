//
//  SkillBLL.h
//  Zombie3_4
//  获取技能相关业务逻辑
//  Created by jl on 15/8/18.
//
//

#ifndef __Zombie3_4__SkillBLL__
#define __Zombie3_4__SkillBLL__

#include <stdio.h>
#include "GameHeader.h"
#include "HeroBase.h"
#include "SkillModel.h"

class SkillBLL : public Ref
{
public:
    ~SkillBLL();
    SkillBLL();
    CREATE_FUNC(SkillBLL);
    virtual bool init() { return true; }
    void getHeroSkill(HeroBase* hb,SkillModel *sm,int skillNum);
    void setSkillUp(int skillID);
};

#endif /* defined(__Zombie3_4__SkillBLL__) */

//
//  SkillBLL.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/18.
//
//

#include "SkillBLL.h"
#include "SkillModelBll.h"
#include "HeroMan.h"
#include "HeroBow.h"
#include "HeroAssassin.h"
#include "HeroKnight.h"

SkillBLL::~SkillBLL()
{
    
}

SkillBLL::SkillBLL()
{
    
}

//获取英雄技能
void SkillBLL::getHeroSkill(HeroBase* hb,SkillModel *sm,int skillNum)
{
    int iHeroID=-1;
    if (dynamic_cast<HeroMan*>(hb)) {
        iHeroID=0;
    }else if (dynamic_cast<HeroBow*>(hb)) {
        iHeroID=1;
    }else if (dynamic_cast<HeroAssassin*>(hb)) {
        iHeroID=2;
    }else if (dynamic_cast<HeroKnight*>(hb)) {
        iHeroID=3;
    }
    auto smb=SkillModelBLL::create(kModelWritablePath);
    //smb->printData();
    int skillIndex=iHeroID*skillNum;
    for (int i=0; i<skillNum; i++) {
        auto skillMode = &(smb->modelData[skillIndex+i]);
        //技能伤害 = 初始技能伤害+ 伤害成长*等级
        skillMode->CurrAttack = skillMode->BaseAttack + skillMode->BaseAttackGrow * (skillMode->CurrLv - 1);
        //技能升级费用 = 技能基础升级费用+技能升级费用成长参数*（当前技能等级-1）
        skillMode->CurrPrice = skillMode->BasePrice + skillMode->BasePriceGrow * (skillMode->CurrLv - 1);
        //技能战力 = 技能初始战力+技能等级*升级战力（每个技能对应一个唯一值）
        skillMode->CurrPower = skillMode->BasePower + skillMode->PowerGrow * skillMode->CurrLv;
        memcpy(sm++, skillMode , sizeof(SkillModel));
    }
}
//设置技能升级
void SkillBLL::setSkillUp(int skillID)
{
    int index=skillID - 1;
    auto smb=SkillModelBLL::create(kModelWritablePath);
    auto skillModel=&(smb->modelData[index]);
    //升级后等级
    int upLv=skillModel->CurrLv + 1;
    //计算升级后攻击力 技能伤害 = 初始技能伤害+伤害成长*等级
    int attack=skillModel->BaseAttack + skillModel->BaseAttackGrow * upLv;
    //计算升级后价格
    int price=skillModel->BasePrice + skillModel->BasePriceGrow * upLv;
    
    skillModel->CurrLv=upLv;
    skillModel->CurrAttack=attack;
    skillModel->CurrPrice=price;
    
    smb->saveData();
}

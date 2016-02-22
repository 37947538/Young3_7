//
//  UpgradeSystem.cpp
//  Zombie3_4
//
//  Created by jl on 15/9/2.
//
//

#include "GameHeader.h"
#include "UpgradeSystem.h"
#include "HeroModelBLL.h"

//增加英雄经验
bool UpgradeSystem::addHeroExp(int exp, HeroModel *lb)
{
    bool isUpLv=false;
    lb->CurrExp+=exp;
    if (lb->CurrExp > lb->NextExp) {
        //英雄升级
        lb->LV=lb->LV + 1;
        lb->CurrExp=0;
        UpgradeSystem::calculationHeroData(lb);
        
        isUpLv=true;
    }
    
    auto hmb=HeroModelBLL::create(kModelWritablePath);
    for (int i=0; i<hmb->getModelSize(); i++) {
        auto hm=&(hmb->modelData[i]);
        if (hm->HeroID==lb->HeroID) {
            hm->LV=lb->LV;
            hm->CurrExp=lb->CurrExp;
            break;
        }
    }
    
    hmb->saveData();
    
    return isUpLv;
}

//设置怪等级
bool UpgradeSystem::setEnemyLv(int iLv, EnemyModel *em)
{
    int hp=em->BaseHp + em->HpGrow * iLv;
    em->CurrHp=hp;
    em->MaxHp=hp;
    int attack=em->BaseAttack + em->AttackGrow * iLv;
    em->Attack=attack;
    //掉落权值 从原来的 怪物权值内掉落，调整为 当前怪物权值 = 怪物当前等级/2+怪物基础权值
    em->DropValue+=em->LV / 2;
    
    return true;
}

//根据等级获取经验
int UpgradeSystem::getHeroLvExp(int iLv)
{
    //每级升级所需经验 = (（等级—1）^2+60)/5*((等级-1)*2+60）
    int lv=iLv - 1;
    int exp=(lv * lv + 60) / 5 * (lv * 2 + 60);
    return exp;
}

//计算英雄数据
bool UpgradeSystem::calculationHeroData(HeroModel *model)
{
    //等级
    int iLv=model->LV;
    //血量＝基础血量 + 等级 * 血量成长
    int hp=model->BaseHp + iLv * model->HpGrow;
    hp+=model->AddHp;
    model->MaxHp=hp;
    model->CurrHp=hp;
    //攻击力＝基础攻击力 + 等级 * 攻击成长
    model->Attack=model->BaseAttack + iLv * model->AttackGrow;
    model->Attack+=model->AddAttack;
    //防御力＝基础防御力 + 等级 * 防御成长
    model->Def=model->BaseDef + iLv * model->DefGrow;
    model->Def+=model->AddDef;
    //暴击率(没有等级增长)
    model->AttackHit=model->BaseAttackHit;
    model->AttackHit+=model->AddAttackHit;
    //升级需要经验
    model->NextExp=UpgradeSystem::getHeroLvExp(iLv);
    
    return true;
}

//计算英雄战力
bool UpgradeSystem::calculationHeroPower(HeroModel *model, SkillModel* skills)
{
    //战力 = 攻击力（（1-暴击率）+暴击率*暴击倍率）+ 防御力 + 生命值/10 +技能A战力+技能B战力+技能C战力+技能D战力
    float attackHit=model->AttackHit * 0.01;
    int sumSkillPower=skills[0].CurrPower + skills[1].CurrPower + skills[2].CurrPower + skills[3].CurrPower;
    int basePower=((1 - attackHit) + attackHit * 2) + model->Def + (model->CurrHp / 10);
    model->CurrPower = basePower + sumSkillPower;
    
    return true;
}
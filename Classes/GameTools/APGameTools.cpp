//
//  APGameTools.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/24.
//
//

#include "APGameTools.h"

//获取玩家当前等级所需要的经验
int APGameTools::getLvExp(int iLV)
{
    return (pow((iLV-1),3)+60)/5*((iLV-1)*2+60)+60;
}
//获取某角色战斗力的算法
int APGameTools::getPower(HeroModel* pmodel)
{
    //参考兰切斯特方程
    //战斗力=有效攻击*有效生命
    //有效攻击=攻击*（1+暴击率*（暴击倍数-1））
    //有效生命=血量/(1-闪避率)  =生命*2+防御
    int power;
    auto att = pmodel->Attack+pmodel->AddAttack;
    auto def = pmodel->Def+pmodel->AddDef;
    auto hit = pmodel->AddAttackHit+pmodel->AddAttackHit;
    auto hp = pmodel->AddHp+pmodel->AddHp;
    //有效攻击
    float sigatt;
    sigatt=att*(1+hit*(2.0f));
    //有效生命
    float sigHP;
    sigHP=hp*2+def;
    power = (sigatt*sigHP+0.5f)/1000;
    return power;
}
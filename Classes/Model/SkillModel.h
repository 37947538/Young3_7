#ifndef __MyProjectName_SkillModel_H__
#define __MyProjectName_SkillModel_H__



/**
 k_ClassDes
 */

class SkillModel 
{
public:
   int   SkillModelID;   //技能序号
   char  Name[32];   //技能
   int   HeroID;   //英雄ID
   int   BasePower;   //基础战力
   int   CurrPower;   //当前战力
   int   PowerGrow;   //战力成长
   float   CurrCDTime;   //技能冷却时间
   float   CdTime;   //冷却时间
   int   isTwoWay;   //是否双面攻击
   int   AttackDist;   //攻击范围
   char  IconPath[128];   //图标
   int   CurrLv;   //当前等级
   int   MaxLv;   //最高等级
   int   AttackCount;   //攻击次数
   int   BaseAttack;   //基础伤害
   int   CurrAttack;   //当前伤害
   int   BaseAttackGrow;   //伤害成长
   int   BasePrice;   //基础价格
   int   CurrPrice;   //升级所需要价格
   int   BasePriceGrow;   //基础价格成长
   char  Desc[256];   //文字描述

};

#endif 


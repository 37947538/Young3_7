#ifndef __MyProjectName_HeroModel_H__
#define __MyProjectName_HeroModel_H__



/**
 k_ClassDes
 */

class HeroModel 
{
public:
   int   HeroID;   //HeroID
   char  HeroName[32];   //英雄名
   char  ImgFile[128];   //头像
   char  HeroImgFile[128];   //全身照
   char  CommonAttackImg[128];   //普通攻击按钮
   int   ActionFileModelID;   //动作文件编号
   int   LV;   //等级
   int   CurrPower;   //当前战斗力
   int   BaseHp;   //基础血量
   int   CurrHp;   //当前血量
   int   MaxHp;   //最大血量
   int   AddHp;   //附加血量
   int   HpGrow;   //血量成长
   char  HpPosition[128];   //血条位置
   int   HpBarWidth;   //血条宽度
   int   CurrExp;   //当前经验
   int   NextExp;   //下次升级经验
   int   AttackDist;   //攻击距离
   int   BaseAttack;   //基础攻击
   int   Attack;   //攻击
   int   AddAttack;   //附加攻击力
   int   AttackGrow;   //攻击成长
   int   BaseDef;   //基础防御
   int   Def;   //防御
   int   AddDef;   //附加防御
   int   DefGrow;   //防御成长
   float   BaseAttackHit;   //基础暴击
   float   AttackHit;   //暴击
   float   AddAttackHit;   //附加暴击
   float   RunMoveSpeed;   //跑移动位置
   float   WareMoveSpeed;   //走路移动位置
   char  EffectTypeName[128];   //特效名称
   int   Price;   //英雄价格

};

#endif 


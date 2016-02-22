#ifndef __MyProjectName_Weapon_H__
#define __MyProjectName_Weapon_H__



/**
 k_ClassDes
 */

class Weapon 
{
public:
   int   WeaponID;   //武器ID
   char  WeaponName[64];   //名称
   int   Type;   //类型
   int   Quality;   //品质
   char  ImgFile[128];   //图片文件
   int   Price;   //价格
   float   PriceAddRate;   //价格增长率
   int   MaxLv;   //最大等级
   int   AddAttack;   //增加攻击力
   int   AddDef;   //增加防御力
   int   AddHp;   //增加生命
   float   AddAttackHit;   //增加暴击
   float   AttributeRate;   //属性增长率
   int   DropValue;   //掉落权值
   float   DropRate;   //掉落概率

};

#endif 


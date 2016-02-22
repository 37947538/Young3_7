#ifndef __MyProjectName_Equipment_H__
#define __MyProjectName_Equipment_H__



/**
 k_ClassDes
 */

class Equipment 
{
public:
   int   EquipmentID;   //装备序号
   int   HeroID;   //佩戴英雄ID
   char  WeaponName[64];   //武器名称
   int   WeaponID;   //获取武器装备
   int   CurrLv;   //当前装备等级
   int   MaxLv;   //最大装备等级
   int   Seat;   //座位123装备负数为背包
   int   CurrPrice;   //当前价格
   int   UpPrice;   //升级价格
   char  ImgFile[128];   //图片文件
   int   Type;   //类型
   int   Price;   //价格
   float   PriceAddRate;   //价格增长率
   float   AttributeRate;   //属性增长率
   int   AddAttack;   //增加攻击力
   int   AddDef;   //增加防御力
   int   AddHp;   //增加生命
   float   AddAttackHit;   //增加暴击

};

#endif 


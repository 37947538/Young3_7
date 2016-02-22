#ifndef __MyProjectName_EnemyModel_H__
#define __MyProjectName_EnemyModel_H__



/**
 k_ClassDes
 */

class EnemyModel 
{
public:
   int   EnemyID;   //EnemyID
   char  EnemyName[64];   //怪名
   char  BulletName[128];   //子弹名称
   int   IsBulletRate;   //是否子弹旋转0不旋转1旋转
   char  BulletStartOffset[128];   //子弹开始偏移量
   char  BulletEndOffset[128];   //子弹结束偏移量
   int   EnemyType;   //0近攻1远攻2boss
   int   EnemyQuality;   //敌兵品质0普通1精英2boss
   char  HpPosition[128];   //血条位置
   int   HpBarWidth;   //血条宽度
   int   ActionFileModelID;   //动作文件ID
   int   LV;   //等级
   int   AttackDist;   //攻击距离单位像素
   char  CatchTime[128];   //捕捉时间
   char  AttackAfterTime[128];   //攻击后时间秒
   char  AttackBeforeTime[128];   //准备攻击等待时间秒
   int   BaseHp;   //基础Hp
   int   CurrHp;   //当前Hp
   int   MaxHp;   //最大Hp
   int   HpGrow;   //血量成长
   int   BaseAttack;   //基础攻击力
   int   Attack;   //攻击力
   int   AttackGrow;   //攻击力成长
   int   ArmorValue;   //防御值
   float   SpeedValue;   //速度
   int   DropExp;   //掉落经验
   int   DropValue;   //掉落权值
   char  EffectTypeName[128];   //特效名称

};

#endif 


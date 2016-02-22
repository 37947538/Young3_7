#ifndef __MyProjectName_ActionFileModel_H__
#define __MyProjectName_ActionFileModel_H__



/**
 k_ClassDes
 */

class ActionFileModel 
{
public:
   int   ActionFileModelID;   //编号
   char  BindHero[32];   //绑定英雄
   char  ArmFilePath[128];   //骨骼文件
   char  ArmName[128];   //骨骼名
   char  FrameEventDownName[128];   //击倒事件
   char  FrameEventName[128];   //事件名
   char  ActionIdle[128];   //动作待机
   char  ActionAttackName1[128];   //动作攻击1
   char  ActionAttackName2[128];   //动作攻击2
   char  ActionAttackName3[128];   //动作攻击3
   char  ActionAttackName4[128];   //动作攻击4
   char  ActionAttackName5[128];   //动作攻击5
   char  ActionRunName[128];   //动作跑
   char  ActionWareName[128];   //动作走
   char  ActionBeAttack1[128];   //动作被击1
   char  ActionBeAttack2[128];   //动作被击2
   char  ActionBeAttack3[128];   //动作被击3
   char  ActionBeAttackDown[128];   //被击倒
   char  ActionDie[128];   //动作死亡
   char  SkillName1[128];   //技能名称1
   char  SkillName2[128];   //技能名称2
   char  SkillName3[128];   //技能名称
   char  SkillName4[128];   //技能名称

};

#endif 


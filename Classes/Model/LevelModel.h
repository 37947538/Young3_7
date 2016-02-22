#ifndef __MyProjectName_LevelModel_H__
#define __MyProjectName_LevelModel_H__



/**
 k_ClassDes
 */

class LevelModel 
{
public:
   int   LevelID;   //关卡ID
   int   LevelState;   //关卡状态
   char  LevelName[32];   //关卡名称
   char  MapFile[128];   //地图文件
   float   LevelHigth;   //水平线高度
   int   LevelWidth;   //关卡长度
   char  BackgroundFile[128];   //背景文件
   int   Interval;   //出兵间隔
   char  AttackTimer[2048];   //攻击波次{敌兵ID,等级,数量,出兵方式}

};

#endif 


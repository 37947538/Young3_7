#ifndef __MyProjectName_EnemyBevTreeModel_H__
#define __MyProjectName_EnemyBevTreeModel_H__



/**
 k_ClassDes
 */

class EnemyBevTreeModel 
{
public:
   int   EnemyBevTreeModel;   //行为节点编号
   int   ParentID;   //父节点编号
   char  NodeType[64];   //节点类型
   int   NodeValue;   //节点值
   char  Name[64];   //节点名称
   char  ClassName[128];   //节点类名
   char  Condition[128];   //执行条件表达式
   char  ConditionKey[128];   //Key
   char  ConditionDes[32];   //条件描述

};

#endif 


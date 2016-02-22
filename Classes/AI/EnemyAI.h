//
//  EnemyRootNode.h
//  HeroTower3_4
//  敌兵智能对象
//  Created by jl on 15/5/11.
//
//

#ifndef __HeroTower3_4__EnemyRootNode__
#define __HeroTower3_4__EnemyRootNode__

#include <stdio.h>
#include "APBevTreeHeader.h"
#include "EnemyBase.h"

class EnemyAI
{
public:
    ~EnemyAI();
    EnemyAI(EnemyBase *m_Parent);
    void update(float ft);
    APBevTreeNode* getBevTreeRoot(){ return m_BevTreeRoot; }       //获取树根
    void createBevTree();                                          //创建行为树
protected:
    APBevTreeNode *m_BevTreeRoot;
    EnemyBase *m_Parent;
};

#endif /* defined(__HeroTower3_4__EnemyRootNode__) */

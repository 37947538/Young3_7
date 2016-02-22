//
//  HeroAI.h
//  Zombie3_4
//
//  Created by jl on 15/8/18.
//
//

#ifndef __Zombie3_4__HeroAI__
#define __Zombie3_4__HeroAI__

#include <stdio.h>

#include "APBevTreeHeader.h"
#include "HeroBase.h"

class HeroAI
{
public:
    ~HeroAI();
    HeroAI(HeroBase *m_Parent);
    void update(float ft);
    APBevTreeNode* getBevTreeRoot(){ return m_BevTreeRoot; }       //获取树根
    void createBevTree();                                          //创建行为树
protected:
    APBevTreeNode *m_BevTreeRoot;
    HeroBase *m_Parent;
};

#endif /* defined(__Zombie3_4__HeroAI__) */

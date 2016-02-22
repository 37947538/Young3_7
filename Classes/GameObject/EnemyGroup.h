//
//  EnemyGroup.h
//  Zombie3_4
//
//  Created by liuye on 15/9/8.
//
//

#ifndef __Zombie3_4__EnemyGroup__
#define __Zombie3_4__EnemyGroup__

#include <stdio.h>
#include "GameHeader.h"

class EnemyGroup : public Ref
{
public:
    EnemyGroup();
    ~EnemyGroup();
    CREATE_FUNC(EnemyGroup);
    virtual bool init();
    void add(EnemyGroup* obj);
    void remove(EnemyGroup* obj);
    void removeForParent();
    Rect mapRect;
    Rect enemyRect;
    std::string className;
    std::string enemyRectString;
    Vector<EnemyGroup*> enemys;
    EnemyGroup* parent=nullptr;
};

#endif /* defined(__Zombie3_4__EnemyGroup__) */

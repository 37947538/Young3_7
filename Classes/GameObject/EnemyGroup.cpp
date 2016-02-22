//
//  EnemyGroup.cpp
//  Zombie3_4
//
//  Created by liuye on 15/9/8.
//
//

#include "EnemyGroup.h"

EnemyGroup::EnemyGroup()
{
    mapRect=Rect::ZERO;
    enemyRect=Rect::ZERO;
}

EnemyGroup::~EnemyGroup()
{
    enemys.clear();
}

bool EnemyGroup::init()
{
    return true;
}

void EnemyGroup::add(EnemyGroup* obj)
{
    obj->parent=this;
    enemys.pushBack(obj);
}

void EnemyGroup::remove(EnemyGroup* obj)
{
    enemys.eraseObject(obj);
}

void EnemyGroup::removeForParent()
{
    if (enemys.empty()) {
        if (parent) {
            parent->remove(this);
        }
    }
}

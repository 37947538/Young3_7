//
//  RewardEquipBLL.h
//  Zombie3_4
//  奖励物品业务逻辑
//  Created by jl on 15/7/28.
//
//

#ifndef __Zombie3_4__RewardEquipBLL__
#define __Zombie3_4__RewardEquipBLL__

#include <stdio.h>
#include "GameHeader.h"
#include "DropObject.h"

class EnemyBase;

class RewardEquipBLL : public Ref
{
public:
    CREATE_FUNC(RewardEquipBLL);
    bool init();
    void update(float arg1);                                            //奖励掉落装备更新
    void randDrop(EnemyBase* eb);                                       //随机掉落
    void dropOneEquip(EnemyBase* eb, float dropRate=100.0);             //掉落一个装备
private:
    void addOneGold(const Vec2& goldPos);                               //增加金币
    void addOneEquip(const Vec2& ePos, int weaponIndex);                //增加一个装备
    void removeEquip(Node* gold);                                       //删除金币
    Vector<DropObject*> m_dropObjects;                                  //掉落金币
};

#endif /* defined(__Zombie3_4__RewardEquipBLL__) */

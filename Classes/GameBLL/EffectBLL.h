//
//  EffectBLL.h
//  Zombie3_4
//  特效业务逻辑
//  Created by jl on 15/7/29.
//
//

#ifndef __Zombie3_4__EffectBLL__
#define __Zombie3_4__EffectBLL__

#include <stdio.h>
#include "GameHeader.h"

class HeroBase;
class EnemyBase;
class AttackObject;

class EffectBLL
{
public:
    static EffectBLL* getInstance();
    static void destroyInstance();
    ~EffectBLL();
    EffectBLL();
    void addEnemyEffect(EnemyBase *eb,AttackObject *att);                                   //增加敌兵特效
    void addHeroEffect(HeroBase *h);                                                        //增加英雄特效
    void addHeroEffectUp(HeroBase *h);                                                      //增加英雄升级
    void addShowGo(Layer *h);                                                               //增加go
    void addDieEffect(Layer *h);                                                            //增加死亡
    void addEffect(Node *h, const std::string& effName, Vec2 pos, bool isAutoRemove=true);  //增加特效
    void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);
};

#endif /* defined(__Zombie3_4__EffectBLL__) */

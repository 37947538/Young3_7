//
//  BulletObject.h
//  Zombie3_4
//  子弹对象
//  Created by jl on 15/8/17.
//
//

#ifndef __Zombie3_4__BulletObject__
#define __Zombie3_4__BulletObject__

#include <stdio.h>
#include "GameHeader.h"
#include "AttackObject.h"
#include "GameBaseObject.h"

class BulletObject : public AttackObject
{
public:
    ~BulletObject();
    BulletObject();
    CREATE_FUNC(BulletObject);
    CC_SYNTHESIZE(int, m_AttackType, AttackType);                           //1攻击敌兵,2攻击英雄
    CC_SYNTHESIZE(bool, m_PenetrateAttack, PenetrateAttack);                //是否穿透攻击(攻击两个或多个目标)
    CC_SYNTHESIZE(bool, m_IsCollision, IsCollision);                        //是否碰撞检测
    CC_SYNTHESIZE(bool, m_isDone, IsDone);                                  //是否做完
    virtual void setTargetPos(Vec2 var, float speed=1500);                  //设置移动目标
    virtual bool init() { return true; };
    virtual void setSprite(Sprite* spr);                                    //设置子弹精灵
    virtual void update(float ft);                                          //更新子弹逻辑
    virtual void executeCallback();                                         //执行回调
    virtual bool isAttack(GameBaseObject* obj);                             //是否攻击
    virtual APOBB* getOBB();                                                //获取碰撞矩形
    GameCallback m_DoneCallback;                                            //完成回调    
private:
    Sprite* m_Bullet;
    Vec2 m_positionDelta;                                                   //目标偏移量
    Vec2 _startPosition;
    Vec2 _previousPosition;
    float totalTime;                                                        //总共时间
    float currTime;                                                         //当前时间
    Vector<GameBaseObject*> lastVector;
};

#endif /* defined(__Zombie3_4__BulletObject__) */

//
//  EnemyCannon.cpp
//  Zombie3_4
//  炮兵－抛物线发射子弹
//  Created by liuye on 15/8/27.
//
//

#include "EnemyCannon.h"
#include "GameBLL.h"
#include "EnemyModel.h"
#include "BulletObject.h"
#include "GameLayer.h"
#include "EffectBLL.h"

EnemyCannon::~EnemyCannon()
{
    
}

EnemyCannon::EnemyCannon()
{
    
}

//敌兵数据
void EnemyCannon::loadData(EnemyModel* arg1)
{
    EnemyBase::loadData(arg1);
}

AttackObject* EnemyCannon::createAttackObject()
{
    auto model=getEnemyModel();
    float attackDist=model->AttackDist;                                 //攻击距离
    Vec2 startOffsetPos=PointFromString(model->BulletStartOffset);      //添加子弹开始坐标偏移量(例如弓箭子弹偏上)
    Vec2 endOffsetPos=PointFromString(model->BulletEndOffset);          //添加子弹结束坐标偏移量(例如法师子弹向下攻击)
    bool facing=getFacing();                                            //获取方向
    if(!facing){
        attackDist*=-1;
    }
    
    Vec2 startPos=getPosition()+startOffsetPos;
    Vec2 endPos=getPosition()+Vec2(attackDist,startOffsetPos.y)+endOffsetPos;
    
    ccBezierConfig bc;
    bc.endPosition=endPos;
    
    float sx = startPos.x; float sy = startPos.y;
    float ex = endPos.x; float ey = endPos.y;
    
    if (startPos.x<endPos.x) {
        bc.controlPoint_1 = Vec2(sx+(ex-sx)*0.3, sy+300);
        bc.controlPoint_2 = Vec2(sx+(ex-sx)*0.75, ey+300);
    }else{
        bc.controlPoint_1 = Vec2(sx-(sx-ex)*0.3, sy+300);
        bc.controlPoint_2 = Vec2(sx-(sx-ex)*0.75, ey+300);
    }
    
    auto bez=BezierTo::create(0.5, bc);
    
    //创建子弹
    auto bullet=BulletObject::create();
    bullet->setAttackType(2);
    bullet->setAttackObject(this);
    auto bulletSprite=Sprite::createWithSpriteFrameName(model->BulletName);
    bulletSprite->setFlippedX(!facing);
    bullet->setSprite(bulletSprite);
    bullet->setPosition(startPos);
    bullet->setTargetPos(endPos);
    //直接添加到游戏层
    GameBLL::instance()->m_GameLayer->addGameObject(bullet);
    
    auto callExplode=CallFunc::create(CC_CALLBACK_0(EnemyCannon::bulletExplode, this, endPos));
    auto seq=Sequence::create(bez,Hide::create(),callExplode,RemoveSelf::create(), NULL);
    bullet->runAction(seq);
    
    if (model->IsBulletRate==1) {
        auto seq=Sequence::create(RotateBy::create(0.3, -360), NULL);
        bullet->runAction(seq);
    }
    
    return nullptr;
}
void EnemyCannon::bulletExplode(const Vec2& pos)
{
    //创建攻击对象
    auto att=AttackObject::create();
    att->setAttackObject(this);
    Rect attRect=Rect(pos.x-50,pos.y,100, 100);
    att->setAttRange(attRect);
    GameBLL::instance()->attackForEnemy(att);
    
    auto model=getEnemyModel();
    EffectBLL::getInstance()->addEffect(GameBLL::instance()->m_GameLayer->getMapLayer(), model->EffectTypeName, pos-Vec2(0, 15));
}
BTNodeInputData* EnemyCannon::readBevNodeInputData()
{
    auto inputData=EnemyBase::readBevNodeInputData();
    inputData->m_iAttackDistMin=inputData->m_iAttackDist-CCRANDOM_0_1()*80;
    return m_InputData;
}

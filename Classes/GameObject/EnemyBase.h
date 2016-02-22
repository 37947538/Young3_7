#ifndef __MyProjectName_EnemyBase_H__
#define __MyProjectName_EnemyBase_H__

#include "GameHeader.h"
#include "BaseActionObject.h"
#include "HealthBarCompoment.h"
#include "AttackObject.h"

/**
 k_ClassDes
 */

class EnemyModel;
class EnemyAI;
class EnemyBevInputData;
class EnemyBevOutputData;
class HeroBase;

class EnemyBase : public BaseActionObject
{
public:
    EnemyBase();                                                    //敌兵构造
    ~EnemyBase();                                                   //析构
    virtual void loadData(EnemyModel* arg1);                        //敌兵数据
    virtual void animateFinish(const std::string& name);            //动画播放完成
    virtual AttackObject* createAttackObject();                     //创建攻击对象
    virtual void update(float ft);                                  //更新对象
    virtual void puton(Vec2 pos);                                   //放在游戏中
    virtual void beAttack(AttackObject *hero);                      //被攻击
    virtual void subBlood(int iBeAttack);                           //减血
    virtual float getHpPercent();                                   //获取hp百分比
    virtual void die();                                             //怪死亡
    virtual void beAttackKnowAnimate();                             //被击倒
    EnemyAI* getEnemyAI(){ return m_EnemyAI;}                       //获取树节点
    EnemyModel* getEnemyModel(){ return m_EnemyModel; };            //获取敌兵模型
    virtual BTNodeInputData* readBevNodeInputData();                //获取怪的状态数据
    virtual void updateAIOutData(BTNodeOutputData *data);           //更新英雄输出数据
    virtual APOBB* getOBB();                                        //获取碰撞矩形
    virtual void setQualityEffect();                                //设置品质特效
    virtual void setHpBarVisible(bool bVisible);                    //设置血条显示隐藏
    virtual void setShadowVisible(bool bVisible);                   //设置阴影显示隐藏
    virtual void showEnemyInfo();                                   //显示敌兵信息
protected:
    void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);
    EnemyAI *m_EnemyAI;                                             //行为树根
    Vec2 hpPos;                                                     //获取血条高度
    EnemyModel *m_EnemyModel;
    HealthBarCompoment *m_HealthBar;
private:
    void onShaderChange(GameEnum::EnemyEvent newState);             //切换shader状态
    Sprite *m_Shadow;
};

#endif 


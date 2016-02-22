//
//  BaseActionObject.h
//  Zombie3_4
//  动作类基础对象
//  Created by jl on 15/6/25.
//
//

#ifndef __Zombie3_4__BaseActionObject__
#define __Zombie3_4__BaseActionObject__

#include <stdio.h>
#include "GameBaseObject.h"
#include "GameEnum.h"
#include "APBevTreeNode.h"
#include "BevNodeDataHeader.h"
#include "SteeringBehaviors.h"

class ActionFileModel;

class BaseActionObject : public GameBaseObject
{
public:
    enum class AnimateState
    {
        Static=0,     //静止
        Runing=1,     //运行
        Finish=2,     //结束
    };
    ~BaseActionObject();                                                                //基础动作对象
    BaseActionObject();                                                                 //基础动作对象
    CC_SYNTHESIZE(int, m_OrderID, OrderID);                                             //对象排序ID
    CC_SYNTHESIZE(GameEnum::BodyState, m_BodyState, BodyState);                         //主体状态
    virtual void changeState(GameEnum::BodyState bs,const std::string& animateName);    //切换状态
    virtual void animateFinish(const std::string& name);                                //动画播放完成
    virtual void beAttack(AttackObject *att);                                           //被攻击
    virtual void idleAnimate();                                                         //待机闲置
    virtual void runAnimate();                                                          //跑动动画
    virtual void dieAnimate();                                                          //死亡
    virtual void setFacing(Vec2 facing);                                                //设置对象方向
    virtual void updatePosition(float ft);                                              //每侦更新位置
    virtual void addForce(float sp,float f);                                            //设置对象加力 sp:速度 f:力量(距离)
    virtual void addForceTime(float t,float f);                                         //设置对象加力 t:时间 f:力量(距离)
    virtual bool getFacing();                                                           //获取对象方向
    virtual void setHpBarVisible(bool bVisible)=0;                                      //设置血条显示隐藏
    virtual void setShadowVisible(bool bVisible)=0;                                     //设置阴影显示隐藏
    virtual Vec2 getVelocity(){ return m_vVelocity;}                                    //获取速度
    virtual std::string commonAttack(){return "null";};                                 //普通攻击,返回攻击动作
    void loadActionFile(int fid);                                                       //加载动作文件
    Armature* getArmature(){return m_Armature;}                                         //返回骨骼文件
    ActionFileModel* getActionFileMode(){ return m_ActionFileModel;}                    //返回动作文件模型
    float MaxSpeed()const{return m_dMaxSpeed;}                                          //返回最大速度
    BaseActionObject::AnimateState getAnimateState(const std::string& animateName);     //获取播放播放动画状态
    std::string lastPlayAnimateName;                                                    //最后播放动画名称
    virtual void updateAIOutData(const BevNodeInputParam* outAaram){};                  //更新输出数据
    virtual BTNodeInputData* readBevNodeInputData(){  return m_InputData;};             //获取怪的状态数据
    virtual BTNodeOutputData* getBevOutputData(){ return m_BevOutData; };               //获取怪的输出数据
protected:
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);
    virtual void playAnimate(const std::string& animateName);           //播放动画
    float currHp;                                                       //当前血量
    float maxHp;                                                        //最大血量
    Armature* m_Armature;                                               //骨骼动画
    std::map<std::string,AnimateState> m_animateStates;                 //动画播放状态
    ActionFileModel* m_ActionFileModel;                                 //动作文件模型
    BTNodeInputData *m_InputData;                                       //行为输入数据
    BTNodeOutputData *m_BevOutData;                                     //行为输出数据
    SteeringBehaviors *m_steeringBehavior;                              //行为数据
    Vec2 m_vVelocity;                                                   //速度
    Vec2 m_vHeading;                                                    //指向实体的朝向
    Vec2 m_vSide;                                                       //垂直于朝向向量的向量
    double m_dMass;                                                     //质量
    float m_dMaxForce;                                                  //实体产生的供以自己动力的最大力
    float m_dAddSpeed;                                                  //实体产生的供以自己动力的速度
    float m_dMaxSpeed;                                                  //实体的最大速度
    double m_dMaxTurnRate;                                              //旋转的最大速率(弧度每秒)
    float m_BeAttackFlyPower;                                           //被击飞的力量
    friend class SteeringBehaviors;
};

#endif /* defined(__Zombie3_4__BaseActionObject__) */

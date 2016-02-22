#ifndef __MyProjectName_HeroBase_H__
#define __MyProjectName_HeroBase_H__

#include "GameHeader.h"
#include "LevelModel.h"
#include "APObject.h"
#include "HeroModel.h"
#include "EnemyBase.h"
#include "StateMachine.h"
#include "ActionFileModel.h"
#include "BaseActionObject.h"
#include "SkillModel.h"

/**
 k_ClassDes
 */

class EnemyBase;
class DropObject;
class HeroAI;
class HeroBevTreeOutputData;
class HeroBevTreeInputData;

class HeroBase : public BaseActionObject
{
public:
    HeroBase();    //英雄基础类
    ~HeroBase();    //稀构函数
    virtual void loadData(HeroModel* arg1);                                 //加载数据模型
    virtual HeroModel* getHeroModel();                                      //获取数据模型
    virtual void animateFinish(const std::string& name);                    //动画播放完成
    virtual std::string commonAttack();                                     //普通攻击,返回攻击动作
    virtual void beAttack(int subHp);                                       //被攻击
    virtual void addExp(int exp);                                           //加经验
    virtual void skillA(){};                                                //技能A动画
    virtual void skillB(){};                                                //技能B动画
    virtual void skillC(){};                                                //技能c动画
    virtual void skillD(){};                                                //技能d动画
    virtual void update(float ft);                                          //每侦更新动画
    virtual void animateSpeed(float ft);                                    //减速效果
    virtual void setInitPosition(const Vec2 &position);                     //设置英雄初始化位置
    virtual void getDropObject(DropObject* dobj);                           //获取掉落物品
    virtual void updateAIOutData(BTNodeOutputData *data);                   //更新英雄输出数据
    virtual void playAnimate(const std::string& animateName);               //播放动画
    virtual void beAttack(AttackObject *att);                               //被攻击
    virtual void subBlood(EnemyBase *hero);                                 //扣血值
    virtual void setMainHero(bool isMainHero);                              //设置主英雄
    virtual bool getMainHero(){ return m_isMainHero;}                       //获取是否主英雄
    virtual void setHpBarVisible(bool bVisible);                            //设置血条显示隐藏
    virtual void setShadowVisible(bool bVisible);                           //设置阴影显示隐藏
    void skillCdTime(int skillID);                                          //当前技能冷却时间
    void onShaderChange(GameEnum::EnemyEvent newState);                     //切换shader状态
    virtual APOBB* getOBB();                                                //获取英雄碰撞矩形
    virtual void die();                                                     //怪死亡
    void subHp(float sub);                                                  //掉血
    void addHp(int addHp);                                                  //加血
    float getHpPercent();                                                   //获取hp百分比
    void updateShadow(float ft);                                            //更新阴影大小
    virtual BTNodeInputData* readBevNodeInputData();                        //获取怪的状态数据
    Armature* getArmature() const { return m_Armature; }                    //获取骨骼
    SkillModel* skills;                                                     //技能模型
protected:
    virtual void attackEvent(AttackObject* ao);                             //攻击事件
    virtual AttackObject* createAttackObject(){ return nullptr;};           //创建攻击对象
    virtual void frameEvent(Bone *bone, const std::string& fn, int oi, int ci); //事件回调
    HeroAI *heroAI;                                         //英雄AI
    HealthBarCompoment* m_HealthBar;
private:
    HeroModel* m_HeroModel;                                 //数据模型
    Sprite *m_Shadow;                                       //阴影文件
    bool m_isMainHero;                                      //是否主英雄
    friend class HeroStateAttack;
};

#endif 


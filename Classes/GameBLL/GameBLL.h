#ifndef __MyProjectName_GameBLL_H__
#define __MyProjectName_GameBLL_H__

#include "GameHeader.h"
#include "LevelModel.h"
#include "APObject.h"
#include "HeroBase.h"
#include "EnemyBase.h"
#include "IUIControl.h"

/**
 k_ClassDes
 */

class GameLayer;
class GameUILayer;
class HeroBase;
class EnemyBase;
class RewardEquipBLL;
class BulletObject;

class GameBLL : public APObject ,public IUIControl
{
public:
    static GameBLL* instance();                             //返回游戏业务逻辑
    static void destory();                                  //释放游戏逻辑
    ~GameBLL();                                             //构造函数
    GameBLL();                                              //希构函数
    Scene* createGame(LevelModel* arg1);                    //创建游戏对象(LevelModel关卡模型)
    virtual void gameReady();                               //准备游戏
    virtual void gameStart();                               //游戏开始
    virtual void gamePause();                               //游戏暂停
    virtual void gameResue();                               //游戏恢复
    virtual void gameWin();                                 //游戏胜利
    virtual void gameOver();                                //游戏失败
    virtual void gameRestart();                             //游戏重新开始
    virtual void heroRelive();                              //英雄复活
    virtual void changeHero();                              //切换英雄
    virtual void attackForHero(HeroBase* h,AttackObject* a); //英雄攻击
    virtual void attackForEnemy(AttackObject* eb);          //敌兵攻击
    virtual void update(float arg1);                        //游戏主循环
    virtual void updateLevelCollision(float arg1);          //关卡碰撞检测
    virtual void updateBullets(float arg1);                 //更新子弹业务
    virtual void addHero(HeroBase* arg1);                   //增加英雄对象
    virtual void removeHero(HeroBase*  arg1);               //移除英雄
    virtual void addEnemyConfig(const std::string& scconst, Rect r);  //增加敌兵通过配置文件
    virtual void readyAddEnemy(const Rect& enemyConfig);    //准备增加敌兵
    virtual void addEnemy(EnemyBase* arg1);                 //增加敌兵
    virtual void removeEnemy(EnemyBase* arg1);              //移除敌人
    virtual void enemyWillDie(EnemyBase* arg1);             //怪将要死亡
    virtual void heroWillDie(HeroBase* arg1);               //英雄将要死
    virtual void shake(int shakeLv);                        //颤屏,shakeLv等级
    virtual void shake(float dt, float x, float y);         //颤屏
    virtual void animateSpeed(float ft);                    //全屏减速
    virtual void animateScale(Vec2 pos,float scaleX,float time); //放大
    virtual void resetComboCount(){nCombo=0;}               //重置连击数
    virtual void viewComboCount();                          //显示连击数
    virtual void addMoney(int i);                           //增加钱
    virtual void setViewScreeCenter();                      //设置屏幕滚动中心点
    GameUILayer *m_GameUILayer;                             //ui层
    GameLayer *m_GameLayer;                                 //游戏层
    HeroBase *m_MainHero;                                   //主要英雄
    Vector<EnemyBase*> vectorEnemy;                         //怪集合
    Vector<HeroBase*> vectorHero;                           //英雄集合
    StateMachine<GameBLL>* getFSM() const { return m_pGameState; }      //获取状态机
    std::vector<int> m_WeaponIndexVector;                               //获得的装备索引
    int getMaxMapWidth(){ return m_LevelModel->LevelWidth; }            //获取地图最大宽度
    int m_CurrLevelGetExp=0;                                            //当前关卡获得的经验
    int m_CurrLevelGetGold=0;                                           //当前关卡获得的金币
    int m_CurrLevelGetDia=0;                                            //当前关卡获得的钻石
private:
    int nCombo=0;                                                       //连击数
    RewardEquipBLL *m_rewardEquipBll;                                   //奖励业务逻辑
    StateMachine<GameBLL>* m_pGameState=nullptr;                        //游戏状态机
    LevelModel* m_LevelModel;
    friend class GameStateRun;
};

#endif 


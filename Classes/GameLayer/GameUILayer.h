//
//  GameUILayer.h
//  hero3_2
//
//  Created by liuye on 14-8-21.
//
//

#ifndef __hero3_2__GameUILayer__
#define __hero3_2__GameUILayer__

#include "GameHeader.h"
#include "APBaseObject.h"
#include "HeroBase.h"

class HudLayer;
class HeroA;
class GameBLL;

class GameUILayer : public Layer
{
public:
    ~GameUILayer();
    CREATE_FUNC(GameUILayer);
    virtual bool init();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    void Button_QieHuan_BtnOnTouch(Ref* sender, Widget::TouchEventType type);   //切换
    void skillAttack_ButtonOnTouch(Ref* sender,Widget::TouchEventType type);    //技能攻击
    void Button_attack_1_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //攻击A
    void Button_attack_2_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //攻击B
    void Button_attack_3_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //攻击C
    void Button_attack_4_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //攻击D
    void Button_Attack_BtnOnTouch(Ref* sender,Widget::TouchEventType type);     //普通攻击
    void Button_Pause_BtnOnTouch(Ref* sender,Widget::TouchEventType type);      //暂停按钮
    void Button_left_BtnOnTouch(Ref* sender,Widget::TouchEventType type);       //左移动按钮
    void Button_right_BtnOnTouch(Ref* sender,Widget::TouchEventType type);      //右移动按钮
    void runStartArmature();                                                    //运行开始动画
    void runWinArmature();                                                      //运行胜利动画
    void setWarningTips(const Vec2 &pos, float time=3);                         //设置警告提示
    void setBatterTips(int number);                                             //设置连击提示
    void setAllButtonVisible(bool bVisible);                                    //设置全部按钮状态
    void setSkillButtonVisible(bool bVisible, int count);                       //设置技能按钮状态(count隐藏按钮数)
    virtual bool handleMessage(const APMessage& msg);                           //消息响应函数
    void updateHeroState(HeroBase* hero, bool isRunAction=true);                //获得英雄状态
    void updateUIHPNum(int n_hp,int n_maxhp, bool isRunAction=true);            //更新UIHP数值显示
    void updateUIEXPNum(int n_exp,int n_maxexp, bool isRunAction=true);         //更新UIEXP数值显示
    void updateHeroImg(HeroBase* hero);                                         //更新英雄响应图片
    void updateDirection(const Vec2 &pos, Widget::TouchEventType type);
private:
    void pauseButtonOnTouch(Ref* sender, Widget::TouchEventType type);          //暂停按钮事件
    void resumeGame(Ref *sender);                                               //恢复游戏
    void restartGame(Ref *sender);                                              //重新游戏
    void setButtonProgressTimer(Button* sender, float cdTime=0.0, float percent=0.0);   //设置技能按钮冷却时间
    void setSkillButtonTouchEnabled(Button* sender);                            //设置技能按钮Touch
    void movementCallback(Armature *armature, MovementEventType type, const std::string& movementID);
protected:
    Vector<ui::Button*> uiSkills;                                               //技能按钮
    HudLayer *m_HudLayer;                                                       //遥感控制
    Layout* m_RootNode;
    ImageView *m_TipsIcon;                                                      //出怪提示
    Layout *m_BatterNumberLabel;                                                //连击数字
    ui::TextBMFont *linkNumb;                                                   //连击数字字体
    Sprite *m_BatterTitle;                                                      //连击文字图片
    ProgressTimer *m_LoadProgress;                                              //连击进度条
    Armature *m_StartArmature;                                                  //开始骨骼动画
    ui::Button *m_PauseButton;                                                  //暂停按钮
    ui::Text* m_LvLabel;                                                        //等级
    ui::Text* curhp;                                                            //当前血量数值
    ui::Text* maxhp;                                                            //最大血量数值
    ui::Text* curexp;                                                           //当前经验数值
    ui::Text* maxexp;                                                           //最大经验数值
    ui::ImageView* heroImg;                                                     //英雄头像
    ui::Button *Button_Attack;                                                  //普通攻击按钮
    ui::LoadingBar* m_HpBar;
    ui::LoadingBar* m_ExpBar;
    ui::Button* m_LeftButton;
    ui::Button* m_RightButton;
};

#endif /* defined(__hero3_2__GameUILayer__) */

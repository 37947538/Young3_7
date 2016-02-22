#ifndef __MyProjectName_MainMapScene_H__
#define __MyProjectName_MainMapScene_H__

#include "GameHeader.h"

/**
 k_ClassDes
 */

class MainMapScene : public Layer
{
public:
    static Scene* createScene();
    CREATE_FUNC(MainMapScene);
    virtual bool init();
protected:
    Layout* m_RootNode;
private:
    void Button_play_BtnOnTouch(Ref* sender,Widget::TouchEventType type);           //开始
    void Button_DayReward_BtnOnTouch(Ref* sender,Widget::TouchEventType type);      //签到
    void Button_Equip_BtnOnTouch(Ref* sender,Widget::TouchEventType type);          //装备按钮
    void Button_EquipUpgrade_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //装备强化按钮
    void Button_SkillUpgrade_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //技能强化按钮
    void Button_Lottery_BtnOnTouch(Ref* sender,Widget::TouchEventType type);        //抽奖按钮
    void Button_Shop_BtnOnTouch(Ref* sender,Widget::TouchEventType type);           //商店
    void updateLabel();                                                             //更新钻石及金币数
    ui::ScrollView* scroll;
    ui::Text* tCoin;                                                                //金币数
    ui::Text* tDiamond;                                                             //钻石数
    TextBMFont* m_SumPower;
};

#endif


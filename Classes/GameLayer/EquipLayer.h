//
//  EquipLayer.h
//  Zombie3_4
//
//  Created by yuankang on 15/7/24.
//
//

#ifndef __Zombie3_4__EquipLayer__
#define __Zombie3_4__EquipLayer__

#include "GameHeader.h"
#include "PopBase.h"
#include "HeroModelBLL.h"

class EquipmentLocalBLL;

class EquipLayer : public PopBase
{
public:
    static Scene* createScene();
    ~EquipLayer();
    CREATE_FUNC(EquipLayer);
    virtual bool init();
    GameCallback updateCalllback;                  //更新回调
    GameCallback closeBtnCallback;                 //关闭回调
protected:
    Layout* m_RootNode;
    Layout* m_Panel;
    Layout* m_EquipPanel;
    Layout* m_WearPanel;
    Layout* m_BackPanel;
    ui::ScrollView* sv_Menu;
private:
    void onEnter();
    void heroButton_OnTouch(Ref* sender, Widget::TouchEventType type);          //英雄按钮
    void backpackBtn_OnTouch(Ref* sender, Widget::TouchEventType type);         //绑定背包里的按钮
    void wearpackBtn_OnTouch(Ref* sender, Widget::TouchEventType type);         //绑定佩戴背包里的按钮
    void Button_Exit_BtnOnTouch(Ref* sender,Widget::TouchEventType type);       //退出按钮
    void Button_xiezai_BtnOnTouch(Ref* sender,Widget::TouchEventType type);     //卸载
    void Button_chushou_BtnOnTouch(Ref* sender,Widget::TouchEventType type);    //出售
    void Button_shiyong_BtnOnTouch(Ref* sender,Widget::TouchEventType type);    //使用
    void updateInfo(HeroModel* heromodel);                                      //更新信息
    void creatBorder(ui::Button* pbtn);                                         //创建选中物品边框
    void showBackpack();                                                        //显示背包装备
    void showWearpack();                                                        //显示穿戴背包装备
    void setBackpackDataView(bool isVisible, int equipID=0);                    //设置背包信息显示状态
    void setWearpackDataView(bool isVisible, int equipID=0);                    //设置穿戴信息显示状态
    void sellCallback(Ref* sender);                                             //卖出回调
    ui::ScrollView *sv_backpack;                                                //背包面板
    EquipmentLocalBLL *equiplocalBll;                                           //本地装备逻辑
    Vector<ui::Button*> m_HeroItemButtons;                                      //英雄选项按钮
    Vector<ui::Button*> backpack;                                               //背包
    Vector<ui::Button*> wearpack;                                               //穿戴包
    int currSelectBackpackID;                                                   //选择背包的ID
    int currSelectWearpackID;                                                   //选择穿戴ID
    int currSelectHeroID;                                                       //当前选择英雄ID
    Sprite*   s_backborder;                                                     //背包选中框
    Sprite*   s_wearborder;                                                     //穿戴选中框
    ui::Text* t_wearpackDes;                                                    //穿戴包说明
    ui::Text* t_gold;                                                           //金币
    ui::Text* t_backpackDes;                                                    //背包说明
    ui::Text* t_wearitemname;                                                   //穿戴物品名称
    ui::Text* t_backitemname;                                                   //背包物品名称
    ui::Text* t_lv;                                                             //等级
    ui::Text* t_currExp;                                                        //经验值
    ui::Text* t_power;                                                          //战斗力
    ui::Text* t_currHP;                                                         //基础血量
    ui::Text* t_attack;                                                         //基础攻击力
    ui::Text* t_def;                                                            //基础防御力
    ui::Text* t_critical;                                                       //基础暴击率
    ui::Text* t_addcurrHP;                                                      //附加血量
    ui::Text* t_addattack;                                                      //附加攻击力
    ui::Text* t_adddef;                                                         //附加防御力
    ui::Text* t_addcritical;                                                    //附加暴击率
};

#endif /* defined(__Zombie3_4__EquipLayer__) */

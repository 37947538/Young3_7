#ifndef __MyProjectName_EquipUpgradeLayer_H__
#define __MyProjectName_EquipUpgradeLayer_H__

#include "GameHeader.h"
#include "PopBase.h"
#include "HeroModelBLL.h"
#include "EquipmentLocalBLL.h"
/**
 k_ClassDes
 */

class EquipUpgradeLayer : public PopBase
{
public:
    static Scene* createScene();
    ~EquipUpgradeLayer();
    CREATE_FUNC(EquipUpgradeLayer);
    virtual bool init();
    void updateInfo(HeroModel* pmodel);
    GameCallback updateCalllback;
    GameCallback closeBtnCallback;                 //关闭回调
protected:
    Layout* m_RootNode;
    Layout* m_Panel;
    Layout* m_EquipPanel;
    Layout* m_WearPanel;
    ui::ScrollView* sv_Menu;
    Vector<ui::Button*> m_HeroItemButtons;                                      //英雄选项按钮
private:
    void heroButton_OnTouch(Ref* sender, Widget::TouchEventType type);          //英雄按钮
    void Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type);
    void wearpackBtn_OnTouch(Ref* sender, Widget::TouchEventType type);
    void upgradeBtn_OnTouch(Ref* sender, Widget::TouchEventType type);
    void onEnter();
    void showWearpack();                                                        //显示穿戴背包装备
    void creatBorder(ui::Button* pbtn);                                         //创建选中物品边框
    void createRightItem(Button* btn, const Vec2& pos);                         //创建右侧强化项
    ui::ScrollView *sv_backpack;                                                //背包面板
    EquipmentLocalBLL *equiplocalBll;                                           //本地装备逻辑
    Vector<ui::Button*> wearpack;                                               //穿戴包
    Sprite*   s_wearborder;                                                     //穿戴选中框
    int currSelectWearpackID;                                                   //选择穿戴ID
    int currSelectHeroID;                                                       //当前选择英雄ID
    ui::Text* t_wearitemname;                                                   //穿戴物品名称
    ui::Text* t_backpackDes;                                                    //背包说明
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

#endif


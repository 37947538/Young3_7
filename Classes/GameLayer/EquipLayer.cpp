//
//  EquipLayer.cpp
//  Zombie3_4
//
//  Created by yuankang on 15/7/24.
//
//

#include "EquipLayer.h"
#include "APSystem.h"
#include "GameHeader.h"
#include "EquipmentLocalBLL.h"
#include "PlayerModelBLL.h"
#include "APGameTools.h"
#include "PlayerBLL.h"
#include "GameObjectFactory.h"
#include "HeroBase.h"
#include "PopTipsLayer.h"
#include "PopConfirmLayer.h"
#include "APShader.h"
#include "ShaderEffect.h"
#include "ShaderEffectSprite.h"
#include "ShaderEffectOutline.h"

Scene* EquipLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = EquipLayer::create();
    scene->addChild(layer);
    return scene;
}

EquipLayer::~EquipLayer()
{
    CC_SAFE_RELEASE_NULL(equiplocalBll);
}

bool EquipLayer::init()
{
    if (!PopBase::init()){
        return false;
    }
    //选择背包的ID
    currSelectBackpackID=-1;
    //选择穿戴ID
    currSelectWearpackID=-1;
    //当前选择英雄ID
    currSelectHeroID=1;
    
    equiplocalBll=EquipmentLocalBLL::create();
    equiplocalBll->retain();
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("EquipLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto Button_Close=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (Button_Close) {
        Button_Close->addTouchEventListener(CC_CALLBACK_2(EquipLayer::Button_Exit_BtnOnTouch, this));
    }
    auto Button_xiezai=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_xiezai"));
    if (Button_xiezai) {
        Button_xiezai->addTouchEventListener(CC_CALLBACK_2(EquipLayer::Button_xiezai_BtnOnTouch, this));
    }
    auto Button_chushou=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_chushou"));
    if (Button_chushou) {
        Button_chushou->addTouchEventListener(CC_CALLBACK_2(EquipLayer::Button_chushou_BtnOnTouch, this));
    }
    auto Button_shiyong=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_shiyong"));
    if (Button_shiyong) {
        Button_shiyong->addTouchEventListener(CC_CALLBACK_2(EquipLayer::Button_shiyong_BtnOnTouch, this));
    }
    
    sv_backpack=dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_RootNode, "ScrollView_wupinlan"));
    m_EquipPanel=dynamic_cast<Layout*>(Helper::seekWidgetByName(m_RootNode, "Panel_zhuangbeilan"));
    m_WearPanel=dynamic_cast<Layout*>(Helper::seekWidgetByName(m_RootNode, "Panel_zhuangbei"));
    m_BackPanel=dynamic_cast<Layout*>(Helper::seekWidgetByName(m_RootNode, "Panel_wupin"));
    //选择英雄
    sv_Menu = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_RootNode, "ScrollView_menu"));
    auto sv_MenuSize=sv_Menu->getInnerContainerSize();
    
    auto pb=PlayerBLL::create();
    
    int iRow=0;
    HeroModelBLL *hmb=HeroModelBLL::create(kModelWritablePath);
    for (int i=0; i<HeroModel_MaxData; i++) {
        if (pb->getIsBuyHero(i)) {
            HeroModel *hm=&(hmb->modelData[i]);
            auto btn=Button::create();
            btn->setTag(i+1);
            btn->loadTextureNormal("imgs/tb_qiehuan_2.png");
            btn->loadTextureDisabled("imgs/tb_qiehuan_1.png");
            btn->addTouchEventListener(CC_CALLBACK_2(EquipLayer::heroButton_OnTouch, this));
            btn->setPosition(Vec2(sv_MenuSize.width/2, sv_MenuSize.height-((iRow * 100)+60)));
            btn->setTitleText(hm->HeroName);
            sv_Menu->addChild(btn);
            
            m_HeroItemButtons.pushBack(btn);
            iRow++;
        }
    }
    m_HeroItemButtons.at(0)->setTouchEnabled(false);
    m_HeroItemButtons.at(0)->setBright(false);
    
    m_Panel=dynamic_cast<Layout*>(Helper::seekWidgetByName(m_RootNode, "Panel_juese"));
    //角色基本属性
    t_lv=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "t_LV"));
    t_currExp=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "t_currExp"));
    t_power=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "t_strength"));
    t_currHP=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "t_currHP"));
    t_attack=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_Attack"));
    t_def=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_Def"));
    t_critical=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_critical"));
    //金币数量
    t_gold=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_jinbishu"));
    //增加的属性
    t_addcurrHP=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "t_currHP_add"));
    t_addattack=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_Attack_add"));
    t_adddef=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_Def_add"));
    t_addcritical=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_critical_add"));
    //佩戴物品说明
    t_wearpackDes=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_zhuangbeixinxi"));
    t_backpackDes=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_shuxing"));
    //佩戴物品名
    t_wearitemname=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_wupinmingcheng_1"));
    //包裹物品名
    t_backitemname=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_wupinmingcheng_2"));
    //选中物品边框
    s_wearborder = Sprite::create("imgs/k_xuanzhong.png");
    m_RootNode->addChild(s_wearborder);
    
    //英雄
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    //刷新数据
    updateInfo(hero->getHeroModel());
    
    showWearpack();
    showBackpack();
    
    setWearpackDataView(false);
    setBackpackDataView(false);
    
    return true;
}
//英雄按钮
void EquipLayer::heroButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    for (auto &btn : m_HeroItemButtons) {
        btn->setTouchEnabled(true);
        btn->setBright(true);
    }
    
    auto btn=(ui::Button*)sender;
    btn->setTouchEnabled(false);
    btn->setBright(false);
    
    currSelectHeroID=btn->getTag();
    
    showWearpack();
    setBackpackDataView(false);
    setWearpackDataView(false);
    //英雄
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    //刷新数据
    updateInfo(hero->getHeroModel());
}
//显示背包装备
void EquipLayer::showBackpack()
{
    for (auto &btn :backpack) {
        btn->removeFromParentAndCleanup(true);
    }
    backpack.clear();
    
    sv_backpack->removeAllChildren();
    s_backborder = Sprite::create("imgs/k_xuanzhong.png");
    s_backborder->setVisible(false);
    sv_backpack->addChild(s_backborder);
    
    equiplocalBll->readBackpack(backpack);
    int equipCount=(int)backpack.size();
    
    //偏移间距
    Vec2 diffV=Vec2(75,-75);
    //每行5个框
    int iColNum=5;
    //背包默认20个格
    int defaultCount=20;
    if (equipCount>=defaultCount) {
        defaultCount=((equipCount / 10) + 1) * 10;
    }
    if (defaultCount-equipCount<iColNum) {
        defaultCount+=iColNum;
    }
    int addRow=(defaultCount / iColNum);
    //增加滑动区高度
    Size backpackSize=Size(sv_backpack->getInnerContainerSize().width, addRow * std::abs(diffV.y));
    sv_backpack->setInnerContainerSize(backpackSize);
    //计算起点
    Vec2 origPoint=Vec2(50,backpackSize.height-40);
    for (int i=0; i<defaultCount; i++) {
        int iRow=i / iColNum;
        int iCol=i % iColNum;
        
        auto bg=ImageView::create("imgs/wupinkuang.png");
        bg->setPosition(origPoint + Vec2(iCol * diffV.x ,iRow * diffV.y));
        sv_backpack->addChild(bg);
        
        if (i<equipCount) {
            auto ubtn=backpack.at(i);
            ubtn->setPosition(bg->getPosition());
            sv_backpack->addChild(ubtn);
            //绑定事件
            ubtn->addTouchEventListener(CC_CALLBACK_2(EquipLayer::backpackBtn_OnTouch, this));
        }
    }
}

//显示穿戴装备
void EquipLayer::showWearpack()
{
    for (auto &btn :wearpack) {
        btn->removeFromParentAndCleanup(true);
    }
    wearpack.clear();
    
    m_EquipPanel->removeAllChildren();
    //计算起点
    Vec2 origPoint=Vec2(37.5,187.5);
    //偏移间距
    Vec2 diffV=Vec2(75,-75);
    //每行2个框
    int iColNum=2;
    
    equiplocalBll->readWearpack(wearpack, currSelectHeroID);
    for (int i=0; i<6; i++) {
        int iRow=i / iColNum;
        int iCol=i % iColNum;
        
        auto pos=origPoint + Vec2(iCol* diffV.x ,iRow * diffV.y);
        auto bgPath=__String::createWithFormat("imgs/zhuangbei_bj_%d.png",i+1);
        auto bg=ImageView::create(bgPath->getCString());
        bg->setPosition(pos);
        m_EquipPanel->addChild(bg);
        
        for (auto &btn : wearpack) {
            auto currEquip=(Equipment*)btn->getUserData();
            if ((i+1)==currEquip->Type) {
                bg->loadTexture("imgs/wupinkuang_2.png");
                btn->setPosition(pos);
                m_EquipPanel->addChild(btn);
                btn->addTouchEventListener(CC_CALLBACK_2(EquipLayer::wearpackBtn_OnTouch, this));
                break;
            }
        }
    }
}
//设置背包信息显示状态
void EquipLayer::setBackpackDataView(bool isVisible, int equipID)
{
    m_BackPanel->setVisible(isVisible);
    s_backborder->setVisible(isVisible);
    if (isVisible) {
        auto equip=&(equiplocalBll->modelData[equipID]);
        auto att=equiplocalBll->getEquipChineseName(equipID);
        std::string strDes=StringUtils::format("Lv.%d \n%s",equip->CurrLv,att.c_str());
        std::string strName=StringUtils::format("%s",equip->WeaponName);
        std::string strPrice=StringUtils::format("$%d",equip->CurrPrice);
        
        t_gold->setString(strPrice);
        t_backpackDes->setString(strDes);
        t_backitemname->setString(strName);
        currSelectBackpackID=equipID;
        currSelectWearpackID=-1;
    }
}
//设置穿戴信息显示状态
void EquipLayer::setWearpackDataView(bool isVisible, int equipID)
{
    m_WearPanel->setVisible(isVisible);
    s_wearborder->setVisible(isVisible);
    
    if (isVisible) {
        auto equip=&(equiplocalBll->modelData[equipID]);
        auto att=equiplocalBll->getEquipChineseName(equipID);
        std::string strDes=StringUtils::format("Lv.%d \n%s",equip->CurrLv,att.c_str());
        std::string strName=StringUtils::format("%s",equip->WeaponName);
        std::string strPrice=StringUtils::format("价格:$%d",equip->CurrPrice);
        
        t_wearpackDes->setString(strDes);
        t_wearitemname->setString(strName);
        
        currSelectWearpackID=equipID;
        currSelectBackpackID=-1;
    }
}
#pragma mark - 绑定背包里的按钮
void EquipLayer::backpackBtn_OnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectSelectItem);
    auto btn=(ui::Button*)sender;
    int equipId=btn->getTag();
    
    setWearpackDataView(false);
    setBackpackDataView(true, equipId);
    creatBorder(btn);
}

#pragma mark - 绑定佩戴背包里的按钮
void EquipLayer::wearpackBtn_OnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectSelectItem);
    auto btn=(ui::Button*)sender;
    int equipId=btn->getTag();
    
    setWearpackDataView(true, equipId);
    setBackpackDataView(false);
    creatBorder(btn);
}
void EquipLayer::Button_Exit_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectClose);
    if (closeBtnCallback) {
        closeBtnCallback(this);
    }
    this->removeFromParentAndCleanup(true);
}
//卸载
void EquipLayer::Button_xiezai_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    //是否有选择的ID
    if(currSelectWearpackID==-1){
        PopTipsLayer::addTipLayer(this, "请选择要卸载的装备！");
        return;
    }
    
    equiplocalBll->removeEquip(currSelectWearpackID, currSelectHeroID);
    
    setWearpackDataView(false);
    setBackpackDataView(false);
    
    showBackpack();
    showWearpack();
    
    //刷新数据
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    updateInfo(hero->getHeroModel());
    
    if (updateCalllback) {
        updateCalllback(this);
    }
}
void EquipLayer::Button_chushou_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    auto eq = &equiplocalBll->modelData[currSelectBackpackID];
    auto price = eq->CurrPrice;
    
    auto pop=PopConfirmLayer::create();
    pop->setInfoString(__String::createWithFormat("$%d",price)->getCString());
    pop->enterCallback=CC_CALLBACK_1(EquipLayer::sellCallback, this);
    this->addChild(pop);
}
void EquipLayer::sellCallback(Ref* sender)
{
    auto pop=(PopConfirmLayer*)sender;
    pop->removeFromParentAndCleanup(true);
    
    auto eq = &equiplocalBll->modelData[currSelectBackpackID];
    auto price = eq->CurrPrice;
    equiplocalBll->deleEquip(currSelectBackpackID);
    
    auto pb=PlayerBLL::create();
    pb->addGold(price);
    
    setBackpackDataView(false);
    showBackpack();
    currSelectBackpackID=-1;
    
    if (updateCalllback) {
        updateCalllback(this);
    }
}
//使用按钮
void EquipLayer::Button_shiyong_BtnOnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    
    //是否有选择的ID
    if(currSelectBackpackID==-1){
        PopTipsLayer::addTipLayer(this, "请选择装备！");
        return;
    }
    
    if(!equiplocalBll->wearEquip(currSelectBackpackID, currSelectHeroID)) {
        PopTipsLayer::addTipLayer(this, "装备栏已满！");
        return;
    }
    currSelectBackpackID=-1;
    
    setWearpackDataView(false);
    setBackpackDataView(false);
    
    showBackpack();
    showWearpack();
    
    //刷新数据
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    updateInfo(hero->getHeroModel());
    
    if (updateCalllback) {
        updateCalllback(this);
    }
}
void EquipLayer::updateInfo(HeroModel* pmodel)
{
    m_Panel->removeAllChildren();
    auto heroImg=ImageView::create(pmodel->HeroImgFile);
    heroImg->setPosition(aprateccp(m_Panel, 0.5, 0.5));
    m_Panel->addChild(heroImg);
    
    t_lv->setString(StringUtils::format("%d",pmodel->LV));
    t_currExp->setString(StringUtils::format("%d/%d",pmodel->CurrExp,APGameTools::getLvExp(pmodel->LV)));
    t_power->setString(StringUtils::format("%d",pmodel->CurrPower));
    t_currHP->setString(StringUtils::format("%d",pmodel->CurrHp - pmodel->AddHp));
    t_attack->setString(StringUtils::format("%d",pmodel->Attack - pmodel->AddAttack));
    t_def->setString(StringUtils::format("%d",pmodel->Def - pmodel->AddDef));
    t_critical->setString(StringUtils::format("%.2f",pmodel->AttackHit - pmodel->AddAttackHit));
    //附加 为0时隐藏
    t_addcurrHP->setVisible(true);
    t_addcurrHP->setString(StringUtils::format("+%d",pmodel->AddHp));
    if (pmodel->AddHp==0) {
        t_addcurrHP->setVisible(false);
    }
    t_addattack->setVisible(true);
    t_addattack->setString(StringUtils::format("+%d",pmodel->AddAttack));
    if (pmodel->AddAttack==0) {
        t_addattack->setVisible(false);
    }
    t_adddef->setVisible(true);
    t_adddef->setString(StringUtils::format("+%d",pmodel->AddDef));
    if (pmodel->AddDef==0) {
        t_adddef->setVisible(false);
    }
    t_addcritical->setVisible(true);
    t_addcritical->setString(StringUtils::format("+%.2f",pmodel->AddAttackHit));
    if (pmodel->AddAttackHit==0) {
        t_addcritical->setVisible(false);
    }
}
//弹出效果
void EquipLayer::onEnter()
{
    PopBase::onEnter();
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,NULL);
    m_RootNode->runAction(m_Sequence);
}
//选中物品边框
void EquipLayer::creatBorder(ui::Button* pbtn){
    s_wearborder->setVisible(false);
    s_backborder->setVisible(false);
    if (currSelectWearpackID!=-1) {
        Vec2 pos = m_EquipPanel->convertToWorldSpace(pbtn->getPosition());
        s_wearborder->setVisible(true);
        s_wearborder->setPosition(pos);
    }
    if (currSelectBackpackID!=-1) {
        Vec2 pos = pbtn->getPosition();
        s_backborder->setVisible(true);
        s_backborder->setPosition(pos);
    }
}
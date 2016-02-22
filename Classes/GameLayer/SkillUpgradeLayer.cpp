//
//  SkillUpgradeLayer.cpp
//  Zombie3_4
//
//  Created by yuankang on 15/7/27.
//
//

#include "SkillUpgradeLayer.h"
#include "GameObjectFactory.h"
#include "HeroBase.h"
#include "APGameTools.h"
#include "HeroModelBLL.h"
#include "PopTipsLayer.h"
#include "SkillBLL.h"
#include "PlayerBLL.h"

Scene* SkillUpgradeLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = SkillUpgradeLayer::create();
    scene->addChild(layer);
    return scene;
}
SkillUpgradeLayer::~SkillUpgradeLayer()
{
    CC_SAFE_RELEASE_NULL(equiplocalBll);
}
bool SkillUpgradeLayer::init(){
    if ( !PopBase::init() )
    {
        return false;
    }
    
    equiplocalBll=EquipmentLocalBLL::create();
    equiplocalBll->retain();
    
    //当前选择英雄ID
    currSelectHeroID=1;
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_ui.csb");
    
    m_RootNode=static_cast<Layout*>(CSLoader::createNode("SkillUpgradeLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    auto close=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (close) {
        close->addTouchEventListener(CC_CALLBACK_2(SkillUpgradeLayer::Button_Close_BtnOnTouch, this));
    }
    m_EquipPanel=dynamic_cast<Layout*>(Helper::seekWidgetByName(m_RootNode, "Panel_zhuangbeilan"));
    m_WearPanel=dynamic_cast<Layout*>(Helper::seekWidgetByName(m_RootNode, "Panel_zhuangbei"));
    m_WearPanel->setVisible(false);
    sv_Skill=dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_RootNode, "ScrollView_jineng"));
    //选择英雄
    sv_Menu=dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_RootNode, "ScrollView_menu"));
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
            btn->addTouchEventListener(CC_CALLBACK_2(SkillUpgradeLayer::heroButton_OnTouch, this));
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
    //增加的属性
    t_addcurrHP=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "t_currHP_add"));
    t_addattack=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_Attack_add"));
    t_adddef=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_Def_add"));
    t_addcritical=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "T_critical_add"));
    //佩戴物品说明
    t_backpackDes=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_zhuangbeixinxi"));
    //佩戴物品名
    t_wearitemname=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_wupinmingcheng"));
    
    //英雄
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    updateInfo(hero->getHeroModel());
    
    showWearpack();
    showSkill();
    
    //选中物品边框
    s_wearborder = Sprite::create("imgs/k_xuanzhong.png");
    s_wearborder->setVisible(false);
    m_EquipPanel->addChild(s_wearborder);
    
    return true;
}
//英雄按钮
void SkillUpgradeLayer::heroButton_OnTouch(Ref* sender, Widget::TouchEventType type)
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
    showSkill();
    m_WearPanel->setVisible(false);
    s_wearborder->setVisible(false);
    
    m_Panel->removeAllChildren();
    //英雄
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    //刷新数据
    updateInfo(hero->getHeroModel());
}
//弹出效果
void SkillUpgradeLayer::onEnter(){
    PopBase::onEnter();
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,NULL);
    m_RootNode->runAction(m_Sequence);
}
//关闭
void SkillUpgradeLayer::Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectClose);
    if (closeBtnCallback) {
        closeBtnCallback(this);
    }
    removeFromParentAndCleanup(true);
}
//穿戴物品点击
void SkillUpgradeLayer::wearpackBtn_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectSelectItem);
    auto btn=(ui::Button*)sender;
    int equipId=btn->getTag();
    auto equip=&(equiplocalBll->modelData[equipId]);
    auto att = equiplocalBll->getEquipChineseName(equipId);
    std::string strDes=StringUtils::format("Lv.%d \n%s",equip->CurrLv,att.c_str());
    std::string strName=StringUtils::format("%s",equip->WeaponName);
    t_backpackDes->setString(strDes);
    t_wearitemname->setString(strName);
    m_WearPanel->setVisible(true);
    currSelectWearpackID=equipId;
    creatBorder(btn);
}
void SkillUpgradeLayer::showWearpack()
{
    for (auto &btn :wearpack) {
        btn->removeFromParentAndCleanup(true);
    }
    wearpack.clear();
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
                btn->setName(__String::createWithFormat("wearpack_%d",btn->getTag())->getCString());
                m_EquipPanel->addChild(btn);
                btn->addTouchEventListener(CC_CALLBACK_2(SkillUpgradeLayer::wearpackBtn_OnTouch, this));
                break;
            }
        }
    }
}
//显示技能
void SkillUpgradeLayer::showSkill()
{
    sv_Skill->removeAllChildren();
    
    Size svSize=sv_Skill->getInnerContainerSize();
    
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    for (int i=0; i<4; i++) {
        auto skillModel=&hero->skills[i];
        auto bg=ImageView::create("imgs/jinengkuang.png");
        bg->setPosition(Vec2(svSize.width / 2 , svSize.height - (i * 105 + 37.5)));
        sv_Skill->addChild(bg);
        
        auto skillIcon=ImageView::create(skillModel->IconPath);
        skillIcon->setPosition(Vec2(37,43));
        bg->addChild(skillIcon);
        
        int upAttack=skillModel->BaseAttack + skillModel->BaseAttackGrow * skillModel->CurrLv;
        std::string strDes=StringUtils::format("%s Lv.%d\n当前伤害:%d\n升级伤害:%d",skillModel->Name,skillModel->CurrLv,skillModel->CurrAttack,upAttack);
        //技能描述
        auto btxt = ui::Text::create(strDes,"Arial",15);
        btxt->setAnchorPoint(Vec2(0, 0.5f));
        btxt->setPosition(skillIcon->getPosition()+Vec2(50, 0));
        bg->addChild(btxt);
        //价格
        std::string strprice = StringUtils::format("消耗\n%d",skillModel->CurrPrice);
        auto bprice = ui::Text::create(strprice,"Arial",15);
        bprice->setColor(Color3B(255,204,0));
        bprice->setAnchorPoint(Vec2(0, 0.5f));
        bprice->setPosition(skillIcon->getPosition()+Vec2(190,0));
        bg->addChild(bprice);
        //升级按钮
        auto upButton=ui::Button::create("imgs/tb_qianghua.png");
        upButton->setTag(i);
        upButton->addTouchEventListener(CC_CALLBACK_2(SkillUpgradeLayer::upButton_OnTouch, this));
        upButton->setPosition(Vec2(bg->getContentSize().width-50,43));
        upButton->setTitleText("升级");
        upButton->setTitleFontSize(15);
        upButton->setTitleFontName("font/hanzhen.TTF");
        bg->addChild(upButton);
    }
}
void SkillUpgradeLayer::upButton_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto btn=(ui::Button*)sender;
    btn->setTouchEnabled(false);
    int skillIndex=btn->getTag();
    
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    auto skillModel=&hero->skills[skillIndex];
    
    if (skillModel->CurrLv >= hero->getHeroModel()->LV) {
        PopTipsLayer::addTipLayer(this, "技能等级不能超过英雄等级！");
    }else{
        //读取玩家金币数据
        auto pbb=PlayerBLL::create();
        auto gold=pbb->getPlayerGold();
        if (gold<skillModel->CurrPrice) {
            PopTipsLayer::addTipLayer(this, "金币不足！");
            btn->setTouchEnabled(true);
            return;
        }
        pbb->addGold(-skillModel->CurrPrice);
     
        auto sb=SkillBLL::create();
        sb->setSkillUp(skillModel->SkillModelID);
    
        auto worldPos=btn->getWorldPosition();
        auto effect=Armature::create("anxt_ui");
        effect->setPosition(worldPos+Vec2(-285, 5));
        effect->setLocalZOrder(kGameTopZ);
        m_RootNode->addChild(effect);
        effect->getAnimation()->play("ui_3");
    
        if (closeBtnCallback) {
            closeBtnCallback(this);
        }
        
        auto func=[&](){
            showSkill();
        };
        effect->runAction(Sequence::create(DelayTime::create(0.5),CallFunc::create(func),RemoveSelf::create(), NULL));
    }
}
//更新状态栏数值
void SkillUpgradeLayer::updateInfo(HeroModel* pmodel)
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
//创建选中物品边框
void SkillUpgradeLayer::creatBorder(ui::Button* pbtn){
    s_wearborder->setVisible(false);
    if (currSelectWearpackID!=-1) {
        int iTag=pbtn->getTag();
        auto wearpackBtnName=__String::createWithFormat("wearpack_%d",iTag);
        auto wearpackBtn=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, wearpackBtnName->getCString()));
        
        s_wearborder->setVisible(true);
        s_wearborder->setPosition(wearpackBtn->getPosition());
    }
}
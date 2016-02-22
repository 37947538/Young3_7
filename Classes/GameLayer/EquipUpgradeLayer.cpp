#include "EquipUpgradeLayer.h"
#include "EquipmentLocalBLL.h"
#include "PlayerBLL.h"
#include "APGameTools.h"
#include "GameObjectFactory.h"
#include "HeroBase.h"
#include "PopTipsLayer.h"

Scene* EquipUpgradeLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = EquipUpgradeLayer::create();
    scene->addChild(layer);
    return scene;
}
EquipUpgradeLayer::~EquipUpgradeLayer()
{
    CC_SAFE_RELEASE_NULL(equiplocalBll);
}
// on "init" you need to initialize your instance
bool EquipUpgradeLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !PopBase::init() )
    {
        return false;
    }
    //选择穿戴ID
    currSelectWearpackID=-1;
    //当前选择英雄ID
    currSelectHeroID=1;
    
    equiplocalBll=EquipmentLocalBLL::create();
    equiplocalBll->retain();
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_ui.csb");
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("EquipUpgradeLayer.csb"));
    this->addChild(m_RootNode);
    
    auto Button_Close=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (Button_Close) {
        Button_Close->addTouchEventListener(CC_CALLBACK_2(EquipUpgradeLayer::Button_Close_BtnOnTouch, this));
    }
    
    m_EquipPanel=dynamic_cast<Layout*>(Helper::seekWidgetByName(m_RootNode, "Panel_zhuangbeilan"));
    m_WearPanel=dynamic_cast<Layout*>(Helper::seekWidgetByName(m_RootNode, "Panel_zhuangbei"));
    sv_backpack = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_RootNode, "ScrollView_wupinlan"));
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
            btn->addTouchEventListener(CC_CALLBACK_2(EquipUpgradeLayer::heroButton_OnTouch, this));
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
    t_wearitemname=dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_RootNode, "Text_wupinmingcheng_1"));
    //英雄
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    updateInfo(hero->getHeroModel());
    
    showWearpack();
    //选中物品边框
    s_wearborder = Sprite::create("imgs/k_xuanzhong.png");
    s_wearborder->setVisible(false);
    m_RootNode->addChild(s_wearborder);
    
    return true;
}
//英雄按钮
void EquipUpgradeLayer::heroButton_OnTouch(Ref* sender, Widget::TouchEventType type)
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
    
    m_WearPanel->setVisible(false);
    s_wearborder->setVisible(false);
    //英雄
    HeroBase *hero=GameObjectFactory::getHero(currSelectHeroID-1);
    //刷新数据
    updateInfo(hero->getHeroModel());
}
//显示穿戴背包装备
void EquipUpgradeLayer::showWearpack()
{
    for (auto &btn :wearpack) {
        btn->removeFromParentAndCleanup(true);
    }
    wearpack.clear();
    sv_backpack->removeAllChildren();
    m_EquipPanel->removeAllChildren();
    //计算起点
    Vec2 origPoint=Vec2(37.5,187.5);
    //偏移间距
    Vec2 diffV=Vec2(75,75);
    //每行2个框
    int iColNum=2;
    
    equiplocalBll->readWearpack(wearpack, currSelectHeroID);
    //默认6行
    int defaultCount=6;
    //滑动区高度
    float sv_Height=defaultCount * diffV.y;
    sv_Height=sv_Height > sv_backpack->getInnerContainerSize().height ? sv_Height : sv_backpack->getInnerContainerSize().height;
    Size backpackSize=Size(sv_backpack->getInnerContainerSize().width, sv_Height);
    sv_backpack->setInnerContainerSize(backpackSize);
    
    for (int i=0; i<defaultCount; i++) {
        int iRow=i / iColNum;
        int iCol=i % iColNum;
        //装备背景
        auto pos=origPoint + Vec2(iCol* diffV.x, -(iRow * diffV.y));
        auto bgPath=__String::createWithFormat("imgs/zhuangbei_bj_%d.png",i+1);
        auto bg=ImageView::create(bgPath->getCString());
        bg->setPosition(pos);
        m_EquipPanel->addChild(bg);
        //右侧强化背景
        auto rightPos=Vec2(backpackSize.width / 2 , sv_Height - (i * diffV.y + 37.5));
        auto rightBG=ImageView::create("imgs/k_qianghualan.png");
        rightBG->setPosition(rightPos);
        sv_backpack->addChild(rightBG);
        
        for (auto &btn : wearpack) {
            auto currEquip=(Equipment*)btn->getUserData();
            if ((i+1)==currEquip->Type) {
                btn->setName(__String::createWithFormat("wearpack_%d",btn->getTag())->getCString());
                bg->loadTexture("imgs/wupinkuang_2.png");
                btn->setPosition(pos);
                m_EquipPanel->addChild(btn);
                btn->addTouchEventListener(CC_CALLBACK_2(EquipUpgradeLayer::wearpackBtn_OnTouch, this));
                
                //创建右侧强化项
                createRightItem(btn, rightPos);
                break;
            }
        }
    }
}
//创建右侧强化项
void EquipUpgradeLayer::createRightItem(Button* btn, const Vec2& pos)
{
    //强化栏
    ImageView *rightbg=ImageView::create("imgs/k_qianghualan.png");
    rightbg->setName(__String::createWithFormat("bg_%d",btn->getTag())->getCString());
    rightbg->setPosition(pos);
    sv_backpack->addChild(rightbg);
    //强化栏物品图标
    auto bbtn=btn->clone();
    bbtn->setName(__String::createWithFormat("backborder_%d",btn->getTag())->getCString());
    bbtn->setPosition(Vec2(39, 37.5));
    rightbg->addChild(bbtn);
    
    auto equip=&(equiplocalBll->modelData[bbtn->getTag()]);
    auto att=equiplocalBll->getEquipChineseName(bbtn->getTag());
    auto attUp=equiplocalBll->getUpEquipChineseName(bbtn->getTag());
    std::string strDes=StringUtils::format("强化前 %s强化后 %s",att.c_str(),attUp.c_str());
    std::string strprice=StringUtils::format("消耗\n%d",equip->UpPrice);
    //物品描述
    auto btxt = ui::Text::create(strDes,"Arial",15);
    btxt->setAnchorPoint(Vec2(0, 0.5f));
    btxt->setPosition(bbtn->getPosition()+Vec2(45, -10));
    btxt->setTag(bbtn->getTag());
    rightbg->addChild(btxt);
    //价格
    auto bprice = ui::Text::create(strprice,"Arial",15);
    bprice->setColor(Color3B(255,204,0));
    bprice->setAnchorPoint(Vec2(0, 0.5f));
    bprice->setPosition(bbtn->getPosition()+Vec2(195,0));
    rightbg->addChild(bprice);
    //强化按钮
    auto bup=ui::Button::create("imgs/tb_qianghua.png");
    bup->setParent(rightbg);
    bup->setTag(bbtn->getTag());
    bup->addTouchEventListener(CC_CALLBACK_2(EquipUpgradeLayer::upgradeBtn_OnTouch, this));
    bup->setPosition(bbtn->getPosition()+Vec2(292,0));
    rightbg->addChild(bup);
    //强化按钮上的字
    auto tup=ui::Text::create("强化","font/hanzhen.TTF",15);
    if (equip->CurrLv >= equip->MaxLv) {
        btxt->setString(att.c_str());
        bprice->setVisible(false);
        bup->setTouchEnabled(false);
        tup=ui::Text::create("满级","font/hanzhen.TTF",15);
    }
    tup->setColor(Color3B(255,204,0));
    tup->setPosition(Vec2(bup->getContentSize().width/2,bup->getContentSize().height/2));
    bup->addChild(tup);
}
//穿戴物品点击
void EquipUpgradeLayer::wearpackBtn_OnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectSelectItem);
    auto btn=(ui::Button*)sender;
    int equipId=btn->getTag();
    auto equip=&(equiplocalBll->modelData[equipId]);
    auto att=equiplocalBll->getEquipChineseName(equipId);
    std::string strDes=StringUtils::format("Lv.%d \n%s",equip->CurrLv,att.c_str());
    std::string strName=StringUtils::format("%s",equip->WeaponName);
    t_backpackDes->setString(strDes);
    t_wearitemname->setString(strName);
    
    m_WearPanel->setVisible(true);
    
    currSelectWearpackID=equipId;
    creatBorder(btn);
}
//强化按钮
void EquipUpgradeLayer::upgradeBtn_OnTouch(Ref* sender, Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kButtonSound);
    auto btn=(ui::Button*)sender;
    btn->setTouchEnabled(false);
    
    int equipId=btn->getTag();
    auto equip=&(equiplocalBll->modelData[equipId]);
    
    //读取玩家金币数据
    auto pbb = PlayerBLL::create();
    auto gold = pbb->getPlayerGold();
    if (gold<equip->UpPrice) {
        PopTipsLayer::addTipLayer(this, "金币不足！");
        btn->setTouchEnabled(true);
        return;
    }
    
    pbb->addGold(-equip->UpPrice);
    //升级装备
    equiplocalBll->upEquip(equipId);
    //本地英雄数据
    HeroBase *h2 = GameObjectFactory::getHero(currSelectHeroID-1);
    auto mod = h2->getHeroModel();
    //更新英雄属性
    equiplocalBll->updateHeroAttribute(mod->HeroID-1);
    //重新取本地数据
    h2 = GameObjectFactory::getHero(currSelectHeroID-1);
    mod = h2->getHeroModel();
    //更新显示属性
    updateInfo(mod);
    
    equip=&(equiplocalBll->modelData[equipId]);
    auto att = equiplocalBll->getEquipChineseName(equipId);
    std::string strDes=StringUtils::format("Lv.%d \n%s",equip->CurrLv,att.c_str());
    std::string strName=StringUtils::format("%s",equip->WeaponName);
    t_backpackDes->setString(strDes);
    t_wearitemname->setString(strName);
    s_wearborder->setVisible(false);
    
    auto effect=Armature::create("anxt_ui");
    effect->setPosition(btn->getPosition() - Vec2(292, 0));
    auto parent=btn->getParent();
    parent->addChild(effect);
    effect->getAnimation()->play("ui_1");
    
    auto func=[&](){
        //刷新装备物品
        showWearpack();
    };
    effect->runAction(Sequence::create(DelayTime::create(0.5),CallFunc::create(func),RemoveSelf::create(), NULL));
    
    if (updateCalllback) {
        updateCalllback(this);
    }
}
// 关闭
void EquipUpgradeLayer::Button_Close_BtnOnTouch(Ref* sender, Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectClose);
    if (closeBtnCallback) {
        closeBtnCallback(this);
    }
    removeFromParentAndCleanup(true);
}
//弹出效果
void EquipUpgradeLayer::onEnter()
{
    PopBase::onEnter();
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,NULL);
    m_RootNode->runAction(m_Sequence);
}
//更新状态栏数值
void EquipUpgradeLayer::updateInfo(HeroModel* pmodel){
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
void EquipUpgradeLayer::creatBorder(ui::Button* pbtn){
    s_wearborder->setVisible(false);
    if (currSelectWearpackID!=-1) {
        int iTag=pbtn->getTag();
        auto wearpackBtnName=__String::createWithFormat("wearpack_%d",iTag);
        auto wearpackBtn=dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, wearpackBtnName->getCString()));
        
        Vec2 pos=m_EquipPanel->convertToWorldSpace(wearpackBtn->getPosition());
        s_wearborder->setVisible(true);
        s_wearborder->setPosition(pos);
    }
}

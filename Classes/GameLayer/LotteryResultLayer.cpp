//
//  LotteryResultLayer.cpp
//  Zombie3_4
//
//  Created by liuye on 15/8/31.
//
//

#include "LotteryResultLayer.h"
#include "EquipmentLocalBLL.h"
#include "ShaderEffectOutline.h"

Scene* LotteryResultLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = LotteryResultLayer::create();
    scene->addChild(layer);
    return scene;
}

bool LotteryResultLayer::init()
{
    if ( !PopBase::init() )
    {
        return false;
    }
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guge/anxt_ui.csb");
    
    m_RootNode = static_cast<Layout*>(CSLoader::createNode("LotteryResultLayer.csb"));
    this->addChild(m_RootNode);
    
    if (kIsPayTest) {
        APTools::PrintUIWidgetChildrenInfo(m_RootNode);
    }
    
    m_CloseButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_RootNode, "Button_Close"));
    if (m_CloseButton) {
        m_CloseButton->addTouchEventListener(CC_CALLBACK_2(LotteryResultLayer::Button_Close_BtnOnTouch, this));
        m_CloseButton->setVisible(false);
    }
    
    return true;
}
//弹出效果
void LotteryResultLayer::onEnter(){
    PopBase::onEnter();
    
    auto call=CallFunc::create(CC_CALLBACK_0(LotteryResultLayer::randStart, this));
    auto basePoint=m_RootNode->getPosition();
    m_RootNode->setPosition(basePoint + Point(0,m_WinSize.height));
    auto move=MoveTo::create(0.8, basePoint);
    auto easeInout=EaseElasticOut::create(move);
    m_Sequence=Sequence::create(easeInout,call,NULL);
    m_RootNode->runAction(m_Sequence);
}
//关闭
void LotteryResultLayer::Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type){
    if (type!=Widget::TouchEventType::ENDED) return;
    SoundBLL::getInstance()->playEffect(kEffectClose);
    if (closeBtnCallback) {
        closeBtnCallback(this);
    }
    removeFromParentAndCleanup(true);
}
void LotteryResultLayer::randStart()
{
    vectorQuality.clear();
    
    std::string goldStr="3,6,1,0#4,3,2,1#4,3,3,0#3,3,3,1#2,6,2,0#4,3,2,1#1,3,3,3#3,6,1,0#3,4,2,1#3,2,3,2";
    std::string diaStr="4,2,3,1#3,5,1,1#2,1,4,3#3,3,3,1#2,3,2,3#4,2,1,3#4,2,1,3#3,2,2,3#5,1,3,1#1,1,4,4";
    std::vector<std::string> results;
    if (m_TypeID==1 || m_TypeID==3) {
        APStringHelper::split(goldStr, "#" ,&results);
    }else{
        APStringHelper::split(diaStr, "#" ,&results);
    }
    
    for (int i=0; i<results.size(); i++) {
        std::string config=results.at(i);
        std::vector<std::string> smallResults;
        APStringHelper::split(config, "," ,&smallResults);
        
        int lastNumber=0;
        int iRand=APTools::getRand(1, 100);
        for (int j=0; j<smallResults.size(); j++) {
            int number=std::atoi(smallResults.at(j).c_str()) * 10;
            int iStart=lastNumber + 1;
            int iEnd=lastNumber + number;
            if (iRand>=iStart && iRand<=iEnd) {
                vectorQuality.pushBack(__Integer::create(j+1));
                //log("iRand:%d,iStart:%d,iEnd:%d,j:%d",iRand,iStart,iEnd,j);
                break;
            }
            lastNumber=iEnd;
        }
    }
    
    Vector<FiniteTimeAction*> arrayOfActions;
    if (m_TypeID==1 || m_TypeID==3) {
        arrayOfActions.pushBack(CallFunc::create(CC_CALLBACK_0(LotteryResultLayer::luck, this, 0)));
    }else if (m_TypeID==2 || m_TypeID==4){
        for (int i=0; i<10; i++) {
            arrayOfActions.pushBack(CallFunc::create(CC_CALLBACK_0(LotteryResultLayer::luck, this, i)));
            arrayOfActions.pushBack(DelayTime::create(0.3));
        }
    }
    arrayOfActions.pushBack(CallFunc::create(CC_CALLBACK_0(LotteryResultLayer::setCloseButtonVisible, this)));
    
    auto seq=Sequence::create(arrayOfActions);
    this->runAction(seq);
}
void LotteryResultLayer::luck(int index)
{
    int quality=vectorQuality.at(index)->getValue();
    std::vector<Weapon*> weaponVector;
    std::vector<Weapon*> qualityWeaponVector;
    auto eLocalBLL=EquipmentLocalBLL::create();
    eLocalBLL->getAllEquipment(weaponVector, quality, quality);
    eLocalBLL->getAllEquipment(qualityWeaponVector, 4, 4);
    
    Weapon* weapon=nullptr;
    auto bg=ImageView::create("imgs/wupinkuang_1.png");
    if (m_TypeID==1 || m_TypeID==3) {
        int iRand=APTools::getRand(0, (int)weaponVector.size() - 1);
        weapon=weaponVector.at(iRand);
        eLocalBLL->addEquip(weapon->WeaponID);
        
        bg->setPosition(aprateccp(m_RootNode, 0.5, 0.5));
        m_RootNode->addChild(bg);
        
        auto nameLabel=Label::create();
        nameLabel->setString(weapon->WeaponName);
        nameLabel->setPosition(aprateccp(bg, 0.5, 1.1));
        bg->addChild(nameLabel);

        auto img=Sprite::create(weapon->ImgFile);
        img->setPosition(aprateccp(bg, 0.5, 0.5));
        bg->addChild(img);
    }else if (m_TypeID==2 || m_TypeID==4){
        int iRand=APTools::getRand(0, (int)weaponVector.size() - 1);
        weapon=weaponVector.at(iRand);
        if (index==9 && m_QualityCount==0) {
            iRand=APTools::getRand(0, (int)qualityWeaponVector.size() - 1);
            weapon=qualityWeaponVector.at(iRand);
        }
        eLocalBLL->addEquip(weapon->WeaponID);
        
        //计算起点
        Vec2 origPoint=Vec2(460,400);
        //偏移间距
        Vec2 diffV=Vec2(90,-95);
        
        int iRow=index / 5;
        int iCol=index % 5;
        auto pos=origPoint + Vec2(iCol* diffV.x ,iRow * diffV.y);
        
        bg->setPosition(pos);
        m_RootNode->addChild(bg);
        
        auto nameLabel=Label::create();
        nameLabel->setString(weapon->WeaponName);
        nameLabel->setPosition(aprateccp(bg, 0.5, 1.1));
        bg->addChild(nameLabel);
        
        auto img=Sprite::create(weapon->ImgFile);
        img->setPosition(aprateccp(bg, 0.5, 0.5));
        bg->addChild(img);
    }
    
    auto effect=Armature::create("anxt_ui");
    effect->setPosition(aprateccp(bg, 0.5, 0.5));
    bg->addChild(effect);
    effect->getAnimation()->play("ui_1");
    
    if (weapon->Quality>=4) {
        m_QualityCount++;
        auto effect2=Armature::create("anxt_ui");
        effect2->setPosition(aprateccp(bg, 0.5, 0.5));
        bg->addChild(effect2);
        effect2->getAnimation()->play("ui_2");
    }
}

void LotteryResultLayer::setCloseButtonVisible()
{
    m_CloseButton->setVisible(true);
}

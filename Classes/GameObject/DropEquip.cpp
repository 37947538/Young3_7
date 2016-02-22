//
//  DropEquip.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/29.
//
//

#include "DropEquip.h"
#include "WeaponBLL.h"
#include "APTools.h"
#include "LevelBLL.h"
#include "EquipmentLocalBLL.h"

#define kBgPath "imgs/weapon/biankuang_%d.png"
#define kWPath "imgs/weapon/knife_%d.png"
#define kLightPath "Default/clipping.png"

DropEquip::DropEquip()
{
    m_WeaponIndex=-1;
}

DropEquip::~DropEquip()
{
    
}

DropEquip* DropEquip::create(int weaponIndex)
{
    DropEquip *pRet = new(std::nothrow) DropEquip();
    if (pRet && pRet->init(weaponIndex))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
    
}

bool DropEquip::init(int weaponIndex)
{
    /*
    int weaponIndex=APTools::getRand(1, Weapon_MaxData) - 1;
    //如果是BOSS关必掉相对品级装备
    if (LevelBLL::instance()->getIsBossLevel()) {
        int iLevelIndex=LevelBLL::instance()->getPlayerSelecLevelID();
        int iQuality=iLevelIndex + 1;   //装备品质
        
        std::vector<Weapon*> equipVector;
        auto eBLL=EquipmentLocalBLL::create();
        eBLL->getAllEquipment(equipVector, iQuality, iQuality);
        
        int equipCount=(int)equipVector.size();
        weaponIndex=APTools::getRand(1, equipCount) - 1;
    }*/
    setWeaponIndex(weaponIndex);
    
    auto wBll=WeaponBLL::create(kModelWritablePath);
    auto model=&wBll->modelData[weaponIndex];
    
    spr = Sprite::create(model->ImgFile);
    this->addChild(spr);
    
    //加点光效
    clip=Sprite::create(model->ImgFile);
    auto cur=ClippingNode::create(clip);
    cur->setAlphaThreshold(0.0f);
    this->addChild(cur,3);
    //light
    auto light=Sprite::create(kLightPath);
    light->setPosition(Vec2(-50,-50));
    light->setOpacity(120);
    cur->addChild(light,2);
    light->setRotation(30);
    auto toRight = MoveTo::create(1.5f, Vec2(200,50));
    auto toLeft = MoveTo::create(0.0f, Vec2(-50,-50));
    auto seq = Sequence::create(toRight,DelayTime::create(0.5f),toLeft, nullptr);
    auto move = RepeatForever::create(seq);
    light->runAction(move);
    
    return true;
}
bool DropEquip::init(Sprite* spr,Sprite* sprbg,Sprite* clip)
{
    //this->addChild(sprbg);
    this->addChild(spr);
    //加点光效
    //clipping node
    auto cur=ClippingNode::create(clip);
    cur->setAlphaThreshold(0.0f);
    this->addChild(cur,3);
    //light
    auto light=Sprite::create(kLightPath);
    light->setPosition(Vec2(-50,-50));
    light->setOpacity(120);
    cur->addChild(light,2);
    light->setRotation(30);
    auto toRight = MoveTo::create(1.5f, Vec2(200,50));
    auto toLeft = MoveTo::create(0.0f, Vec2(-50,-50));
    auto seq = Sequence::create(toRight,DelayTime::create(0.5f),toLeft, nullptr);
    auto move = RepeatForever::create(seq);
    light->runAction(move);
    
    return true;
}
//克隆
DropEquip* DropEquip::clone()
{
    DropEquip* a = DropEquip::create(m_WeaponIndex);
    //a->init(spr,sprbg,clip);
    //a->autorelease();
    return a;
}
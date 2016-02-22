//
//  PlayerBLL.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/29.
//
//

#include "PlayerBLL.h"
#include "PlayerModelBLL.h"

bool PlayerBLL::init()
{
    return true;
}

//获取玩家金币
int PlayerBLL::getPlayerGold()
{
    PlayerModelBLL *pb=PlayerModelBLL::create(kModelWritablePath);
    auto playModle=&(pb->modelData[0]);
    return playModle->Gold;
}

//获取玩家钻石
int PlayerBLL::getPlayerDia()
{
    PlayerModelBLL *pb=PlayerModelBLL::create(kModelWritablePath);
    auto playModle=&(pb->modelData[0]);
    return playModle->Dia;
}
//加金币
void PlayerBLL::addGold(int iGold)
{
    PlayerModelBLL *pb=PlayerModelBLL::create(kModelWritablePath);
    auto playModle=&(pb->modelData[0]);
    playModle->Gold+=iGold;
    pb->saveData();
}

//加钻石
void PlayerBLL::addDia(int iDia)
{
    PlayerModelBLL *pb=PlayerModelBLL::create(kModelWritablePath);
    auto playModle=&(pb->modelData[0]);
    playModle->Dia+=iDia;
    pb->saveData();
}

//获取英雄ID是否选择
bool PlayerBLL::getIsSelectHero(int iHeroID)
{
    auto pb= PlayerModelBLL::create(kModelWritablePath);
    int iSelectID=pb->modelData[0].SelectHeroID;
    bool bSelect=iSelectID & ( 1 << iHeroID );
    return bSelect;
}

//选择英雄上场
void PlayerBLL::setSelectHero(int iHeroID)
{
    auto pb= PlayerModelBLL::create(kModelWritablePath);
    int iSelectID=pb->modelData[0].SelectHeroID;
    //重置选择英雄状态
    iSelectID |= (1 << iHeroID);
    
    pb->modelData[0].SelectHeroID=iSelectID;
    pb->saveData();
}

//取消英雄上场
void PlayerBLL::setUnSelectHero(int iHeroID)
{
    auto pb= PlayerModelBLL::create(kModelWritablePath);
    int iSelectID=pb->modelData[0].SelectHeroID;
    //重置选择英雄状态
    iSelectID &= ~(1 << iHeroID);
    
    pb->modelData[0].SelectHeroID=iSelectID;
    pb->saveData();
}

//获取玩家选择的主英雄
Vector<__Integer*> PlayerBLL::getSelectMainHero()
{
    Vector<__Integer*> seleHeroID;
    auto pb= PlayerModelBLL::create(kModelWritablePath);
    int iSelectID=pb->modelData[0].SelectHeroID;
    
    //判断五个英雄选择了几个
    for (int i=0; i < 5 ; i++) {
        if(iSelectID & (1 << i))
        {
            seleHeroID.pushBack(__Integer::create(i));
        }
    }
    return seleHeroID;
}

//设置购买英雄
void PlayerBLL::setBuyHero(int iHeroIndex)
{
    auto pb=PlayerModelBLL::create(kModelWritablePath);
    int iBuyHeroID=pb->modelData[0].BuyHeroID;
    //英雄购买状态
    iBuyHeroID |= (1 << iHeroIndex);
    
    pb->modelData[0].BuyHeroID=iBuyHeroID;
    pb->saveData();
}

//获取英雄是否已购买
bool PlayerBLL::getIsBuyHero(int iHeroIndex)
{
    auto pb= PlayerModelBLL::create(kModelWritablePath);
    int iBuyHeroID=pb->modelData[0].BuyHeroID;
    bool bBuy=iBuyHeroID & (1 << iHeroIndex);
    return bBuy;
}

//设置开启关卡ID
void PlayerBLL::setOpenLevelID(int iLevelID, bool isBossLevel)
{
    int iMaxID=getOpenLevelID(isBossLevel);
    if (iLevelID<=iMaxID) {
        return;
    }
    
    auto pb=PlayerModelBLL::create(kModelWritablePath);
    if (isBossLevel) {
        pb->modelData[0].OpenBossLevelID=iLevelID;
    }else{
        pb->modelData[0].OpenLevelID=iLevelID;
    }
    pb->saveData();
}
//获取开启关卡ID
int PlayerBLL::getOpenLevelID(bool isBossLevel)
{
    auto pb=PlayerModelBLL::create(kModelWritablePath);
    int iOpenLevelID=pb->modelData[0].OpenLevelID;
    if (isBossLevel) {
        iOpenLevelID=pb->modelData[0].OpenBossLevelID;
    }
    if (iOpenLevelID<0) {
        iOpenLevelID=0;
    }
    return iOpenLevelID;
}

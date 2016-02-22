//
//  PlayerBLL.h
//  Zombie3_4
//  玩家业务逻辑
//  Created by jl on 15/7/29.
//
//

#ifndef __Zombie3_4__PlayerBLL__
#define __Zombie3_4__PlayerBLL__

#include <stdio.h>
#include "GameHeader.h"

class PlayerBLL : public Ref
{
public:
    CREATE_FUNC(PlayerBLL);
    virtual bool init();
    int getPlayerGold();                                            //获取玩家金币
    int getPlayerDia();                                             //获取玩家钻石
    void addGold(int iGold);                                        //加金币
    void addDia(int iDia);                                          //加钻石
    Vector<__Integer*> getSelectMainHero();                         //获取玩家选择的主英雄
    bool getIsSelectHero(int iHeroID);                              //获取英雄ID是否选择
    void setSelectHero(int iHeroID);                                //选择英雄上场
    void setUnSelectHero(int iHeroID);                              //取消英雄上场
    void setOpenLevelID(int iLevelID, bool isBossLevel=false);      //设置开启关卡ID
    int getOpenLevelID(bool isBossLevel=false);                     //获取开启关卡ID
    void setBuyHero(int iHeroIndex);                                //设置购买英雄
    bool getIsBuyHero(int iHeroIndex);                              //获取英雄是否已购买
};

#endif /* defined(__Zombie3_4__PlayerBLL__) */

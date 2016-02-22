//
//  LevelBLL.h
//  Zombie3_4
//
//  Created by jl on 15/8/11.
//
//

#ifndef __Zombie3_4__LevelBLL__
#define __Zombie3_4__LevelBLL__

#include <stdio.h>
#include "GameHeader.h"
#include "LevelModel.h"
#include "EnemyGroup.h"

class MapLayer;

class LevelBLL : public Ref
{
public:
    static LevelBLL* instance();
    static void destory();    
    ~LevelBLL();
    LevelBLL();
    CC_SYNTHESIZE(float, m_LevelHeight, LevelHeight);                                       //关卡高度
    CC_SYNTHESIZE(int, m_PlayerSelecLevelID, PlayerSelecLevelID);                           //玩家选择ID
    CC_SYNTHESIZE(bool, m_IsTryGame, IsTryGame);                                            //是否试玩
    CC_SYNTHESIZE(bool, m_IsBossLevel, IsBossLevel);                                        //是否BOSS关
    void parse(LevelModel* levelModel);                                                     //解析关卡模型
    int getLevelWidth(LevelModel* levelModel);                                              //获取当前关卡宽度
    MapLayer* getLevelLayer(LevelModel* levelModel,float bgWidth,float bgHeight);           //获取当前关卡背景层
    std::set<int> enemyIDs;                                                                 //怪ID
    std::vector<int> heroIDs;                                                               //选择英雄ID
    EnemyGroup* getEnemyGroup() { return m_EnemyGroup; }
    void getEnemyRect(const Vec2& pos, Vector<EnemyGroup*>& enemys);
private:
    bool m_IsParsed;          //是否解析
    int m_LevelBgWidth;       //关卡背景高度
    LevelModel* m_LevelModel; //关卡模型
    EnemyGroup* m_EnemyGroup;
};

#endif /* defined(__Zombie3_4__LevelBLL__) */

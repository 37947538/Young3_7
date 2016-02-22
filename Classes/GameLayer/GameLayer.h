#ifndef __MyProjectName_GameLayer_H__
#define __MyProjectName_GameLayer_H__

#include "GameHeader.h"
#include "LevelModel.h"
#include "DropEquip.h"
#include "MapLayer.h"

/**
 k_ClassDes
 */

class GameLayer : public Layer
{
public:
    GameLayer();        //构造函数
    ~GameLayer();       //希构函数
    CC_SYNTHESIZE(float, m_MapMoveWidth, MapMoveWidth);                     //设置地图移动宽度
    virtual void loadData(LevelModel*  arg1);                               //加载数据模型
    virtual LevelModel* getLevelModel();                                    //获取数据模型
    virtual void addGameObject(Node* mObj);                                 //增加游戏对象
    virtual void removeGameObject(Node* mObj);                              //删除游戏对象
    virtual void scroolViewScree();                                         //滚动屏幕
    virtual void setViewScreeCenter(const Vec2& center);                    //设置屏幕滚动中心点
    virtual void setMapPostion(const Vec2& mapPos);                         //设置地图位置
    virtual Rect getMapRect()  const;                                       //获取地图矩形
    virtual void shake(float dt, float x, float y);                         //屏幕晃动
    virtual void subCurrHp(Vec2 vec,int delta,long demage,int zOrder);      //飘血数字
    virtual void addHpNumber(Vec2 vec,int addHp);                           //加血数字
    virtual void addCoinTips(Vec2 vec,int delta,int icoin,int zOrder);      //加钱提示
    virtual void addExpTips(Vec2 vec,int delta,int iexp,int zOrder);        //加经验提示
    virtual void addEquiptips(Vec2 vec,DropEquip* equip);                   //拾取装备提示
    virtual void crops(Vec2 vec);                                           //掉落
    virtual MapLayer* getMapLayer(){ return m_Background ;};                //获取地图层
private:
    LevelModel* m_LevelModel;
    MapLayer   *m_Background;
    Size m_WinSize;
    Sprite  *m_Light;
};

#endif 


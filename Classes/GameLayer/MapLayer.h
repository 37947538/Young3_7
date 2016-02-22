//
//  MapLayer.h
//  Zombie3_4
//  地图层
//  Created by jl on 15/8/18.
//
//

#ifndef __Zombie3_4__MapLayer__
#define __Zombie3_4__MapLayer__

#include <stdio.h>
#include "GameHeader.h"
#include "LevelModel.h"
#include "DropEquip.h"

/**
 k_ClassDes
 */

class MapLayer : public LayerColor
{
public:
    static MapLayer* create(const Color4B& color, GLfloat width, GLfloat height);
    MapLayer();        //构造函数
    ~MapLayer();       //希构函数
    virtual void drawOBB(APOBB* obb);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
    cocos2d::CustomCommand _customCmd;
    void onDraw(const Mat4 &transform, uint32_t flags);
    void printOBB(APOBB* obb);
};

#endif /* defined(__Zombie3_4__MapLayer__) */

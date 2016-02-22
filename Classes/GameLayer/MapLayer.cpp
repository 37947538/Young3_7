//
//  MapLayer.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/18.
//
//

#include "MapLayer.h"
#include "GameBaseObject.h"
#include "GameBLL.h"
#include "BulletObject.h"
#include "BulletBLL.h"

MapLayer * MapLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    auto map=new MapLayer();
    map->initWithColor(color, width, height);
    map->autorelease();
    return map;
}

//构造函数
MapLayer::MapLayer()
{
    
}
//希构函数
MapLayer::~MapLayer()
{
    
}

void MapLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Node::draw(renderer, transform, flags);
    if (kDrawLine) {
        _customCmd.init(_globalZOrder+kGameTopZ, transform, flags);
        _customCmd.func = CC_CALLBACK_0(MapLayer::onDraw, this, transform, flags);
        renderer->addCommand(&_customCmd);
    }
}

void MapLayer::onDraw(const Mat4 &transform, uint32_t flags)
{
    //初始化
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    auto cs=this->getChildren();
    for (auto &hero : GameBLL::instance()->vectorHero) {
        auto obb=hero->getOBB();
        printOBB(obb);
    }
    
    for (auto &enemy : GameBLL::instance()->vectorEnemy) {
        if (enemy->getBodyState()==GameEnum::BodyState::Die) {
            continue;
        }
        auto obb=enemy->getOBB();
        printOBB(obb);
    }
    
    for (auto &b : BulletBLL::getInstance()->vectorBullets) {
        if (!b->getIsCollision()) {
            continue;
        }
        auto obb=b->getOBB();
        printOBB(obb);
    }
}

void MapLayer::printOBB(APOBB* obb)
{
    return;
    auto v1=obb->getVertex(0);
    auto v2=obb->getVertex(1);
    auto v3=obb->getVertex(2);
    auto v4=obb->getVertex(3);
    {
        //画线
        CHECK_GL_ERROR_DEBUG();
        glLineWidth(1.0f);//设置线条宽度
        DrawPrimitives::setDrawColor4B(255, 0, 0, 255);//设置颜色
        DrawPrimitives::drawLine(Vec2(v1.x,v1.y), Vec2(v2.x,v2.y));
    }
    {
        //画线
        CHECK_GL_ERROR_DEBUG();
        glLineWidth(1.0f);//设置线条宽度
        DrawPrimitives::setDrawColor4B(255, 0, 0, 255);//设置颜色
        DrawPrimitives::drawLine(Vec2(v2.x,v2.y), Vec2(v3.x,v3.y));
    }
    {
        //画线
        CHECK_GL_ERROR_DEBUG();
        glLineWidth(1.0f);//设置线条宽度
        DrawPrimitives::setDrawColor4B(255, 0, 0, 255);//设置颜色
        DrawPrimitives::drawLine(Vec2(v3.x,v3.y), Vec2(v4.x,v4.y));
    }
    {
        //画线
        CHECK_GL_ERROR_DEBUG();
        glLineWidth(1.0f);//设置线条宽度
        DrawPrimitives::setDrawColor4B(255, 0, 0, 255);//设置颜色
        DrawPrimitives::drawLine(Vec2(v4.x,v4.y), Vec2(v1.x,v1.y));
    }
}

void MapLayer::drawOBB(APOBB* obb)
{
    return;
    if (!kDrawLine) return;
    
    auto v1=obb->getVertex(0);
    auto v2=obb->getVertex(1);
    auto v3=obb->getVertex(2);
    auto v4=obb->getVertex(3);
    
    auto dn=DrawNode::create();
    dn->drawLine(Vec2(v1.x,v1.y), Vec2(v2.x,v2.y), Color4F::GREEN);
    dn->drawLine(Vec2(v2.x,v2.y), Vec2(v3.x,v3.y), Color4F::GREEN);
    dn->drawLine(Vec2(v3.x,v3.y), Vec2(v4.x,v4.y), Color4F::GREEN);
    dn->drawLine(Vec2(v4.x,v4.y), Vec2(v1.x,v1.y), Color4F::GREEN);
    this->addChild(dn);
    
    dn->runAction(Sequence::create(DelayTime::create(0.1),RemoveSelf::create(), NULL));
}
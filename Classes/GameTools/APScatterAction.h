//
//  APScatterAction.h
//  Zombie3_4
//
//  Created by yuankang on 15/7/24.
//  类似爆金币的动作
//

#ifndef __Zombie3_4__APScatterAction__
#define __Zombie3_4__APScatterAction__

#include "cocos2d.h"

USING_NS_CC;

class APScatterAction : public ActionInterval
{
public:
    static APScatterAction* create(float _height=300, float _minX=150, float _maxX=200, float _rotate=0);   //跳跃高度，旋转
    virtual void startWithTarget(Node *target) override;
    virtual void update(float t) override;
    virtual APScatterAction *clone() const override;
    bool initWithDuration(float _height, float _minX, float _maxX, float _rotate);
protected:
    Vec2 m_startPosition;        //开始位置
    Vec2 m_previousPos;          //过去位置
private:
    int m_jumps;                 //弹动次数
    float m_baseRotate;          //旋转基数
    float m_rotation;            //旋转系数
    float m_duration;            //动作持续时间
    float m_width;               //X偏移位置左右距离
    float m_height;              //跳跃力（动能）
    float m_gravity;             //重力
    float m_mass;                //质量
    float m_groundY;             //地板y轴
    float m_X;
    float getRandFloat(float minNum, float maxNum);
};

#endif /* defined(__Zombie3_4__APScatterAction__) */

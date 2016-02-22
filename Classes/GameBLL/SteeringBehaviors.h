//
//  SteeringBehaviors.h
//  Zombie3_4
//  行为专项
//  Created by jl on 15/7/10.
//
//

#ifndef __Zombie3_4__SteeringBehaviors__
#define __Zombie3_4__SteeringBehaviors__

#include <stdio.h>
#include "GameHeader.h"

class BaseActionObject;

class SteeringBehaviors
{
public:
    SteeringBehaviors(BaseActionObject *agent);
    ~SteeringBehaviors();
    
    enum summing_method{weighted_average, prioritized, dithered};
    
    enum behavior_type
    {
        none               = 0x00000,
        bseek               = 0x00002,
        flee               = 0x00004,
        arrive             = 0x00008,
        wander             = 0x00010,
        cohesion           = 0x00020,
        separation         = 0x00040,
        allignment         = 0x00080,
        obstacle_avoidance = 0x00100,
        wall_avoidance     = 0x00200,
        follow_path        = 0x00400,
        pursuit            = 0x00800,
        evade              = 0x01000,
        interpose          = 0x02000,
        hide               = 0x04000,
        flock              = 0x08000,
        offset_pursuit     = 0x10000,
    };

    Vec2 calculate();                           //计算合力
    Vec2 calculate(float ft);                   //计算合力
    Vec2 seek(Vec2 TargetPos);                  //靠近目标
private:
    //a pointer to the owner of this instance
    BaseActionObject*     m_pBaseActionObject;
    
    //the steering force created by the combined effect of all
    //the selected behaviors
    Vec2 m_vSteeringForce;
};

#endif /* defined(__Zombie3_4__SteeringBehaviors__) */

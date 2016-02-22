//
//  HeroEventObject.h
//  Zombie3_4
//
//  Created by jl on 15/8/19.
//
//

#ifndef __Zombie3_4__HeroEventObject__
#define __Zombie3_4__HeroEventObject__

#include <stdio.h>
#include "GameHeader.h"
#include "GameBaseObject.h"
#include "EnemyEventObject.h"

class HeroEventObject : public EnemyEventObject
{
public:
    ~HeroEventObject(){};
    HeroEventObject(){};
    CREATE_FUNC(HeroEventObject);
    virtual bool init() { return true; };
    
};
#endif /* defined(__Zombie3_4__HeroEventObject__) */

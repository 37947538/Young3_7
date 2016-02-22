//
//  GameBaseObject.h
//  Zombie3_4
//  游戏基础对象
//  Created by jl on 15/6/11.
//
//

#ifndef __Zombie3_4__GameBaseObject__
#define __Zombie3_4__GameBaseObject__

#include <stdio.h>
#include <GameHeader.h>
#include "APOBB.h"

class GameBaseObject : public Node
{
public:
    GameBaseObject();
    ~GameBaseObject();
    virtual APOBB* getOBB(){ return m_obb; };
protected:
    APOBB *m_obb;
};

#endif /* defined(__Zombie3_4__GameBaseObject__) */

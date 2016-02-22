//
//  APPath.h
//  Knight3_4
//
//  Created by jl on 15/4/23.
//
//

#ifndef __Knight3_4__APPath__
#define __Knight3_4__APPath__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class APPath
{
public:
    static std::string getPath(const std::string& kVersion);     //获取路径
};

#endif /* defined(__Knight3_4__APPath__) */

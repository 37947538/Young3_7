//
//  Effect.h
//  Zombie3_4
//
//  Created by jl on 15/6/24.
//
//

#ifndef __Zombie3_4__Effect__
#define __Zombie3_4__Effect__

#include <stdio.h>
#include "GameHeader.h"

class ShaderEffectSprite;

class ShaderEffect : public Ref
{
public:
    GLProgramState* getGLProgramState() const { return _glprogramstate; }
    virtual void setTarget(ShaderEffectSprite *sprite){}
    
protected:
    bool initGLProgramState(const std::string &fragmentFilename);
    ShaderEffect();
    virtual ~ShaderEffect();
    GLProgramState *_glprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::string _fragSource;
    EventListenerCustom* _backgroundListener;
#endif
};
#endif /* defined(__Zombie3_4__Effect__) */

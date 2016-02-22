//
//  ShaderEffectOutline.h
//  Zombie3_4
//
//  Created by jl on 15/6/24.
//
//

#ifndef __Zombie3_4__ShaderEffectOutline__
#define __Zombie3_4__ShaderEffectOutline__

#include <stdio.h>
#include "ShaderEffect.h"
#include "ShaderEffectSprite.h"


// Outline
class ShaderEffectHurt : public ShaderEffect
{
public:
    CREATE_FUNC(ShaderEffectHurt);
    
    bool init()
    {
        initGLProgramState("shader/actor_hurt.fsh");
        
        /*
        Vec3 color(1.0f, 0.2f, 0.3f);
        GLfloat radius = 0.01f;
        GLfloat threshold = 1.75;
        
        _glprogramstate->setUniformVec3("u_outlineColor", color);
        _glprogramstate->setUniformFloat("u_radius", radius);
        _glprogramstate->setUniformFloat("u_threshold", threshold);
         */
        return true;
    }
    
 
     virtual void setTarget(ShaderEffectSprite* sprite) override
     {
         auto s = sprite->getTexture()->getContentSizeInPixels();
         //getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
         
         //设置纹理
         getGLProgramState()->setUniformTexture("u_texture", sprite->getTexture());
         //getGLProgramState()->setu
     }
    
};


// Outline
class ShaderEffectOutline : public ShaderEffect
{
public:
    CREATE_FUNC(ShaderEffectOutline);
    
    bool init()
    {
        initGLProgramState("shader/example_outline.fsh");
        //initGLProgramState("shader/actor_copy.fsh");
        Vec3 color(1.0f, 0.2f, 0.3f);
        GLfloat radius = 0.01f;
        GLfloat threshold = 1.75;
        
        _glprogramstate->setUniformVec3("u_outlineColor", color);
        _glprogramstate->setUniformFloat("u_radius", radius);
        _glprogramstate->setUniformFloat("u_threshold", threshold);
        return true;
    }
    
};

#endif /* defined(__Zombie3_4__ShaderEffectOutline__) */

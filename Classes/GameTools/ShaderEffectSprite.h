//
//  ShaderEffectSprite.h
//  Zombie3_4
//
//  Created by jl on 15/6/24.
//
//

#ifndef __Zombie3_4__ShaderEffectSprite__
#define __Zombie3_4__ShaderEffectSprite__

#include <stdio.h>
#include "GameHeader.h"
#include "ShaderEffect.h"

class ShaderEffectSprite;
static int tuple_sort( const std::tuple<ssize_t,ShaderEffect*,QuadCommand> &tuple1, const std::tuple<ssize_t,ShaderEffect*,QuadCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

class ShaderEffectSprite : public Sprite
{
public:
    static ShaderEffectSprite *create(const std::string& filename) {
        auto ret = new (std::nothrow) ShaderEffectSprite;
        
        if(ret && ret->initWithFile(filename)) {
            ret->autorelease();
            return ret;
        }
        
        CC_SAFE_RELEASE(ret);
        return nullptr;
    }
    
    void setEffect(ShaderEffect* effect) {
        if(_defaultEffect != effect) {
            effect->setTarget(this);
            
            CC_SAFE_RELEASE(_defaultEffect);
            _defaultEffect = effect;
            CC_SAFE_RETAIN(_defaultEffect);
            
            setGLProgramState(_defaultEffect->getGLProgramState());
        }
    }
    void addEffect(ShaderEffect *effect, ssize_t order) {
        effect->retain();
        effect->setTarget(this);
        
        _effects.push_back(std::make_tuple(order,effect,QuadCommand()));
        
        std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
    }
    
    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override
    {
#if CC_USE_CULLING
        // Don't do calculate the culling if the transform was not updated
        _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
        
        if(_insideBounds)
#endif
        {
            // negative effects: order < 0
            int idx=0;
            for(auto &effect : _effects) {
                
                if(std::get<0>(effect) >=0)
                    break;
                QuadCommand &q = std::get<2>(effect);
                q.init(_globalZOrder, _texture->getName(), std::get<1>(effect)->getGLProgramState(), _blendFunc, &_quad, 1, transform, flags);
                renderer->addCommand(&q);
                idx++;
                
            }
            /*
            // normal effect: order == 0
            _quadCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, transform, flags);
            renderer->addCommand(&_quadCommand);
            */
            // postive effects: oder >= 0
            for(auto it = std::begin(_effects)+idx; it != std::end(_effects); ++it) {
                QuadCommand &q = std::get<2>(*it);
                q.init(_globalZOrder, _texture->getName(), std::get<1>(*it)->getGLProgramState(), _blendFunc, &_quad, 1, transform, flags);
                renderer->addCommand(&q);
                idx++;
            }
        }
    }
protected:
    ShaderEffectSprite() : _defaultEffect(nullptr)
    {
        _effects.reserve(2);
    }
    ~ShaderEffectSprite() {
        for(auto &tuple : _effects) {
            std::get<1>(tuple)->release();
        }
        CC_SAFE_RELEASE(_defaultEffect);
    }
    
    std::vector<std::tuple<ssize_t,ShaderEffect*,QuadCommand>> _effects;
    ShaderEffect* _defaultEffect;
};

#endif /* defined(__Zombie3_4__ShaderEffectSprite__) */

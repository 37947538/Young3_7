//
//  LoadingScene.h
//  Zombie3_4
//
//  Created by yuankang on 15/8/11.
//  读条场景
//

#ifndef __Zombie3_4__LoadingScene__
#define __Zombie3_4__LoadingScene__

#include "GameHeader.h"

class LoadingScene : public Layer
{
public:
    static Scene* createScene(void* obj);
    static LoadingScene* create(void* obj);
    virtual bool init(void* obj);
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
protected:
    Layout* m_RootNode;
    std::vector<std::string> m_ArmNameVector;
private:
    LoadingBar* m_LoadProgress;                                 //进度条
    int currentNum=0;                                           //当前加载到第几张
    int totalNum=0;                                             //加载总数
    void addImg();
    void plistImageAsyncCallback(Texture2D* texture);
};

#endif


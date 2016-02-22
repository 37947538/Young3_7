//
//  APSystem.h
//  Cat3_4
//
//  Created by yuankang on 15/6/3.
//
//

#ifndef __Cat3_4__APSystem__
#define __Cat3_4__APSystem__

#include "GameHeader.h"
typedef enum APEvent
{
    APEventLogo=0,         //显示logo
    APEventGame,           //跳转游戏
    APEventChoosePeople,   //选择人物
    APEventMainMap,        //主地图
    APEventMain,           //封面
    APEventPrepare,        //准备界面
    APEventEquip,          //装备
    APEventDevelop,        //改装
    APEventRestart,        //重新开始
}APEvent;

class APSystem : public cocos2d::Ref
{
public:
    static APSystem* getInstance();
    static void destroyInstance();
    APSystem(void);
    virtual ~APSystem(void);
    virtual void sendEvent(enum APEvent event, void* obj=NULL);
};


#endif /* defined(__Cat3_4__APSystem__) */

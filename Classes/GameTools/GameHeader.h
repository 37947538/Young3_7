//
//  GameHeader.h
//  Zombie3_4
//
//  Created by jl on 15/6/3.
//
//

#ifndef Zombie3_4_GameHeader_h
#define Zombie3_4_GameHeader_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameEnum.h"
#include "APPath.h"
#include "APLibHeader.h"
#include "SoundBLL.h"
#include "SoundHeader.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

typedef std::function<void(Ref*)> GameCallback;
typedef std::function<void()> GameCallbackNoArg;             //不带参数

#define kVersion "0.2"   //+kVersion+"/"
#define kGameTopZ 10000000
#define kIsPayTest 0    //发布设置为1
#define kPopLayerColor Color4B(0, 0, 0, 125)                //弹出背景属性
#define kModelWritablePath APPath::getPath(kVersion)        //模型可写路径

#define kHeroPosition Vec2(200,280)                         //英雄位置
#define kDrawLine 1                                         //碰撞检测划线

#pragma mark - enum
// 攻击按钮类型
typedef enum AttackButtonType
{
    btAttackNone=0,
    btAttack,           //普通攻击
    btAttackA,          //技能A
    btAttackB,          //技能B
    btAttackC,          //技能C
    btAttackD,          //技能D
    btLeft,             //左移按钮
    btRight,            //右移按钮
}AttackButtonType;

typedef enum kMessageType
{
    kMessageTypeShape=1,        //屏幕震动
    kMessageTypeBlink,          //红屏闪烁
    kMessageTypeAttack,         //攻击
    kMessageTypeSkillAttack,    //技能攻击
    kMessageTypeDie,            //被杀死
    kMessageTypeOpenFire,       //射箭
    kMessageTypePauseGame,      //暂停游戏
    kMessageTypeResumeGame,     //恢复游戏
    kMessageTypeRestartGame,    //重新游戏
    kMessageTypeGameWin,        //游戏胜利消息
    kMessageTypeEnemySub,       //怪掉血消息
    kMessageTypeHeroChianEnd,   //英雄连击完成
}kMessageType;

#endif

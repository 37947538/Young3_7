//
//  SoundBLL.h
//  Human3_4
//
//  Created by liuye on 15/3/17.
//
//

#ifndef __Human3_4__SoundBLL__
#define __Human3_4__SoundBLL__

#include <stdio.h>
#include "SoundBLL.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define kMusicVol "musicVol"
#define kEffectVol "effectVol"
#define kFirstRunSoundSet "kFirstRunSoundSet"
#define kFirstSoundRunSoundSet "kFirstSoundRunSoundSet"

class SoundBLL : public Ref{
public:
    static SoundBLL* getInstance();
    static void destroyInstance();
    SoundBLL();
    ~SoundBLL();
    CC_SYNTHESIZE_RETAIN(__String*, m_currBackground, currBackground);
    void playbackground(const char* bgName);        //播放背景音乐
    bool sound();
    void saveEffectVol(float vol);                  //保存音效是否播放的真
    void saveMusicVol(float vol);                   //保存背景音乐是否播放的真
    void playEffect(const char* effectName);        //播放特效声音
    void preloadEffect(const char* pszFilePath);    //预备播放音效
    bool isMusicMute();                             //音乐是否静音
    void setMusicMute(bool isMute);                 //音乐静音
    void setEffectMute(bool isMute);                //音效静音
    bool isEffectMute();                            //音效是否静音
    void setMusicPause();                           //音乐暂停
    void setMusicResume();                          //音乐恢复
private:
    void setAlreadRun();                            //是否已经运行一次
    bool isFirstRun();                              //是否首次运行
    void setSoundAlreadRun();                       //是否声音已经运行一次
    bool isSoundFirstRun();                         //是否声音首次运行
};

#endif /* defined(__Human3_4__SoundBLL__) */

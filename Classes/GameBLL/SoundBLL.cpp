//
//  SoundBLL.cpp
//  Human3_4
//
//  Created by liuye on 15/3/17.
//
//

#include "SoundBLL.h"

static SoundBLL *s_pSoundBLL;
SoundBLL* SoundBLL::getInstance()
{
    if (nullptr == s_pSoundBLL)
    {
        s_pSoundBLL = new SoundBLL();
        __String *soundInit=ccs("0");
        s_pSoundBLL->setcurrBackground(soundInit);
    }
    
    return s_pSoundBLL;
}

void SoundBLL::destroyInstance()
{
    CC_SAFE_DELETE(s_pSoundBLL);
}

SoundBLL::SoundBLL()
{
    m_currBackground=NULL;
}

SoundBLL::~SoundBLL()
{
    CC_SAFE_RELEASE_NULL(m_currBackground);
}

void SoundBLL::playEffect(const char* effectName)
{
    if (isEffectMute() && !isFirstRun()) {
        setEffectMute(true);
    }
    SimpleAudioEngine::getInstance()->playEffect(effectName);
}

void SoundBLL::preloadEffect(const char* pszFilePath)
{
    SimpleAudioEngine::getInstance()->preloadEffect(pszFilePath);
}
void SoundBLL::playbackground(const char* bgName)
{
    if (isMusicMute() && !isSoundFirstRun()) {
        setMusicMute(true);
    }
    if (m_currBackground->compare(bgName)==0) {  //已经有播放的背景音乐了
        return;
    }
    __String *bgStr=__String::create(bgName);
    setcurrBackground(bgStr);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(m_currBackground->getCString(),true);

    if (isMusicMute() && !isSoundFirstRun()) {
        return;
    }
}
//保存声音设置
void SoundBLL::saveMusicVol(float vol)
{
    UserDefault *userDefault=UserDefault::getInstance();
    userDefault->setIntegerForKey(kMusicVol,vol);
    userDefault->flush();
}
//音效保存设置
void SoundBLL::saveEffectVol(float vol)
{
    UserDefault *userDefault=UserDefault::getInstance();
    userDefault->setIntegerForKey(kEffectVol,vol);
    userDefault->flush();
}
//音乐是否静音
bool SoundBLL::isMusicMute()
{
    if (isSoundFirstRun()) {
        return false;
    }
    UserDefault *userDefault=UserDefault::getInstance();
    int iValue =userDefault->getIntegerForKey(kMusicVol);
    return !(bool)iValue;
}
//音乐静音
void SoundBLL::setMusicMute(bool isMute)
{
    float fValue=isMute ? 0 : 1;
    SimpleAudioEngine *am= SimpleAudioEngine::getInstance();
    am->setBackgroundMusicVolume(fValue);
    saveMusicVol(fValue);
    setSoundAlreadRun();
}
//音效静音
void SoundBLL::setEffectMute(bool isMute)
{
    float fValue=isMute ? 0 : 1;
    SimpleAudioEngine *am= SimpleAudioEngine::getInstance();
    am->setEffectsVolume(fValue);
    saveEffectVol(fValue);
    setAlreadRun();
}
//音效是否静音
bool SoundBLL::isEffectMute()
{
    if (isFirstRun()) {
        return false;
    }
    UserDefault *userDefault=UserDefault::getInstance();
    int iValue =userDefault->getIntegerForKey(kEffectVol);
    return !(bool)iValue;
}
//是否已经运行一次
void SoundBLL::setAlreadRun()
{
    UserDefault *userDefault=UserDefault::getInstance();
    userDefault->setIntegerForKey(kFirstRunSoundSet,1);
    userDefault->flush();
}
//是否首次运行
bool SoundBLL::isFirstRun()
{
    UserDefault *userDefault=UserDefault::getInstance();
    int iValue =userDefault->getIntegerForKey(kFirstRunSoundSet);
    return !(bool)iValue;
}
//是否声音已经运行一次
void SoundBLL::setSoundAlreadRun()
{
    UserDefault *userDefault=UserDefault::getInstance();
    userDefault->setIntegerForKey(kFirstSoundRunSoundSet,1);
    userDefault->flush();
}
//是否声音首次运行
bool SoundBLL::isSoundFirstRun()
{
    UserDefault *userDefault=UserDefault::getInstance();
    int iValue =userDefault->getIntegerForKey(kFirstSoundRunSoundSet);
    return !(bool)iValue;
}
//音乐暂停
void SoundBLL::setMusicPause()
{
    auto audio=SimpleAudioEngine::getInstance();
    audio->pauseBackgroundMusic();
}
//音乐恢复
void SoundBLL::setMusicResume()
{
    auto audio=SimpleAudioEngine::getInstance();
    audio->resumeBackgroundMusic();
}
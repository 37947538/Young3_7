//
//  HealthBarCompoment.cpp
//  Human3_4
//
//  Created by liuye on 15/3/17.
//
//

#include "HealthBarCompoment.h"

HealthBarCompoment* HealthBarCompoment::create(const char *pszFileName, const char *hpTopFileName, const char *hpDownFileName)
{
    HealthBarCompoment *pobSprite = new HealthBarCompoment();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->setProgressTimer(hpTopFileName, hpDownFileName);
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
HealthBarCompoment::~HealthBarCompoment()
{
    
}
HealthBarCompoment::HealthBarCompoment()
{
    progressTimerDown=NULL;
    progressTimerTop=NULL;
}
void HealthBarCompoment::setProgressTimer(const char *hpTopFileName, const char *hpDownFileName)
{
    auto size = this->getContentSize();
    auto position = Vec2(size.width * 0.5, size.height * 0.5);
    
    if (hpDownFileName) {
        auto var=Sprite::create(hpDownFileName);
        progressTimerDown = ProgressTimer::create(var);
        progressTimerDown->setType(ProgressTimer::Type::BAR);
        progressTimerDown->setMidpoint(Point(0, 0.5));
        progressTimerDown->setBarChangeRate(Point(1, 0));
        progressTimerDown->setPercentage(100);//满值 100%
        progressTimerDown->setPosition(position);
        this->addChild(progressTimerDown,1);
    }
    if (hpTopFileName) {
        auto var=Sprite::create(hpTopFileName);
        progressTimerTop = ProgressTimer::create(var);
        progressTimerTop->setType(ProgressTimer::Type::BAR);
        progressTimerTop->setMidpoint(Point(0, 0.5));
        progressTimerTop->setBarChangeRate(Point(1, 0));
        progressTimerTop->setPercentage(100);//满值 100%
        progressTimerTop->setPosition(position);
        this->addChild(progressTimerTop,2);
    }
}
void HealthBarCompoment::setHpPercentage(float tarPercent)
{
    float startPercent=0;
    if (progressTimerTop) {
        startPercent=progressTimerTop->getPercentage();
        progressTimerTop->setPercentage(tarPercent);
    }
    if (progressTimerDown) {
        progressTimerDown->stopAllActions();
        auto action=ProgressFromTo::create(0.2, startPercent, tarPercent);
        auto seq=Sequence::create(DelayTime::create(0.1),action, NULL);
        if (tarPercent<=0) {
            auto call=CallFunc::create(CC_CALLBACK_0(HealthBarCompoment::setVisible, this, false));
            seq=Sequence::create(DelayTime::create(0.1),action,call, NULL);
        }
        progressTimerDown->runAction(seq);
    }    
}
void HealthBarCompoment::setHpVisible(bool bVisible)
{
    this->setVisible(bVisible);
}
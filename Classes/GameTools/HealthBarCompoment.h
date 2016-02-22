//
//  HealthBarCompoment.h
//  Human3_4
//  血条
//  Created by liuye on 15/3/17.
//
//

#ifndef __Human3_4__HealthBarCompoment__
#define __Human3_4__HealthBarCompoment__

#include <stdio.h>
#include "GameHeader.h"

class HealthBarCompoment : public Sprite
{
public:
    static HealthBarCompoment* create(const char *bgFileName, const char *hpTopFileName, const char *hpDownFileName=NULL);
    ~HealthBarCompoment();
    HealthBarCompoment();
    void setHpPercentage(float tarPercent);
private:
    ProgressTimer* progressTimerDown;
    ProgressTimer* progressTimerTop;
    void setProgressTimer(const char *hpTopFileName, const char *hpDownFileName);
    void setHpVisible(bool bVisible);
};

#endif /* defined(__Human3_4__HealthBarCompoment__) */

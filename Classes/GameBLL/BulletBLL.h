//
//  BulletBLL.h
//  Zombie3_4
//  子弹运行业务逻辑
//  Created by jl on 15/9/4.
//
//

#ifndef __Zombie3_4__BulletBLL__
#define __Zombie3_4__BulletBLL__

#include <stdio.h>
#include "GameHeader.h"
#include "BulletObject.h"

class BulletObject;

class BulletBLL
{
public:
    static BulletBLL* getInstance();
    static void destroyInstance();
    ~BulletBLL();
    BulletBLL();
    void addBullet(BulletObject* bullet);                   //增加子弹
    void removeBullet(BulletObject* bullet);                //删除子弹
    void update(float dt);                                  //子弹更新
    std::vector<BulletObject*> vectorBullets;               //子弹集合
    std::vector<BulletObject*> waitRemove;                  //等待删除集合
private:
    void addWaitRemove(Ref* bullet);                        //等待删除
};

#endif /* defined(__Zombie3_4__BulletBLL__) */

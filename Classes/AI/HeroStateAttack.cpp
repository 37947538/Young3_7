/**
 k_ClassDes
 */

#include "HeroStateAttack.h"
#include "GameBLL.h"

//英雄攻击状态
HeroStateAttack* HeroStateAttack::Instance()
{
   static HeroStateAttack instance;    return &instance;
}

//英雄攻击状态
void HeroStateAttack::enter(HeroBase*  arg1)
{
//    //修改移动速度
//    arg1->m_vVelocity*=0.1;
//    
//    //移动距离
//    //arg1->addForceTime(0.2,5);
//    
//    Vec2 diff=Vec2::ZERO;
//    //TODO:
//    auto m_Armature=arg1->getArmature();
//    std::string strAnimateName= m_Armature->getAnimation()->getCurrentMovementID();
//    log("name:%s",strAnimateName.c_str());
//    log("name:%s",strAnimateName.c_str());
//    if (strAnimateName==arg1->m_ActionFileModel->ActionAttackName1) {
//        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
//        if (currPercent < 0.6) return;
//        
//        //移动距离
//        //arg1->addForceTime(0.4,50);
//        
//        m_Armature->getAnimation()->stop();
//        arg1->attackAnimate(2);
//    }else if(strAnimateName==arg1->m_ActionFileModel->ActionAttackName2 && strcmp(arg1->m_ActionFileModel->ActionAttackName3,"null")!=0){
//        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
//        if (currPercent < 0.4) return;
//        m_Armature->getAnimation()->stop();
//        
//        //移动距离
//        //arg1->addForceTime(0.2,10);
//        
//        arg1->attackAnimate(3);
//        //GameBLL::Instance()->animateSpeed(1.0);
//        //arg1->animateSpeed(2.0);
//    }else if(strAnimateName==arg1->m_ActionFileModel->ActionAttackName3 && strcmp(arg1->m_ActionFileModel->ActionAttackName4,"null")!=0){
//        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
//        if (currPercent < 0.4) return;
//        m_Armature->getAnimation()->stop();
//        
//        //移动距离
//        //arg1->addForceTime(0.2,50);
//        arg1->attackAnimate(4);
//    }else if(strAnimateName==arg1->m_ActionFileModel->ActionAttackName4 && strcmp(arg1->m_ActionFileModel->ActionAttackName5,"null")!=0){
//        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
//        if (currPercent < 0.8) return;
//        m_Armature->getAnimation()->stop();
//        arg1->attackAnimate(1);
//    }
//    /*
//    else if(strAnimateName==arg1->m_ActionFileModel->ActionAttackName5){
//        float currPercent= m_Armature->getAnimation()->getCurrentPercent();
//        if (currPercent < 1) return;
//        m_Armature->getAnimation()->stop();
//        arg1->attackAnimate(1);
//    }*/
//    else{
//        arg1->attackAnimate(1);
//    }
    arg1->commonAttack();
}

//英雄攻击状态
void HeroStateAttack::execute(HeroBase*  arg1)
{
   //TODO:
}

//英雄攻击状态
void HeroStateAttack::executeTime(HeroBase*  arg1,float arg2)
{
    arg1->updatePosition(arg2);
    
    //更新阴影
    arg1->updateShadow(arg2);
}

//英雄攻击状态
void HeroStateAttack::exit(HeroBase*  arg1)
{
   
}



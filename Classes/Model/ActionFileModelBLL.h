#ifndef __MyProjectName_ActionFileModelBLL_H__
#define __MyProjectName_ActionFileModelBLL_H__

#include "ActionFileModel.h"

/**
 k_ClassDes
 */

#define ActionFileModel_MaxData 21


class ActionFileModelBLL : public Ref
{
public:
    static ActionFileModelBLL *create(const std::string& localPath)
    {
        ActionFileModelBLL *pRet = new(std::nothrow) ActionFileModelBLL();
        if (pRet)
        {
            pRet->loadResData(localPath);
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }

    ~ActionFileModelBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    ActionFileModelBLL()
    {
        modelData=new ActionFileModel[ActionFileModel_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return ActionFileModel_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(ActionFileModel), ActionFileModel_MaxData, readFile);
        //    result=true;
        //}
        //fclose(readFile);
        //return result;
        
        Data dt=FileUtils::getInstance()->getDataFromFile(resPath.c_str());
        if (dt.isNull()) {
            return false;
        }
        localData=resPath;
        
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[151484];    //151484 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, ActionFileModel_MaxData*sizeof(ActionFileModel));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[151484];    //151484 内存文件存在位置
        memcpy(currBuff,modelData, ActionFileModel_MaxData*sizeof(ActionFileModel));
        
        FILE *readFile = fopen(localData.c_str(), "wb");
        if (readFile)
        {
            fwrite(dt.getBytes(), sizeof(unsigned char),dt.getSize() , readFile);
        }
        fclose(readFile);
        
        
        return result;
    }
    
    //打印当前数据
    void printData()
    {
         for(int i=0; i< getModelSize(); i++) {
               printf("model[%d]\n",i);
               auto m=&modelData[i];
               printf("ActionFileModelID[%d]",m->ActionFileModelID);
               printf("BindHero[%s]",m->BindHero);
               printf("ArmFilePath[%s]",m->ArmFilePath);
               printf("ArmName[%s]",m->ArmName);
               printf("FrameEventDownName[%s]",m->FrameEventDownName);
               printf("FrameEventName[%s]",m->FrameEventName);
               printf("ActionIdle[%s]",m->ActionIdle);
               printf("ActionAttackName1[%s]",m->ActionAttackName1);
               printf("ActionAttackName2[%s]",m->ActionAttackName2);
               printf("ActionAttackName3[%s]",m->ActionAttackName3);
               printf("ActionAttackName4[%s]",m->ActionAttackName4);
               printf("ActionAttackName5[%s]",m->ActionAttackName5);
               printf("ActionRunName[%s]",m->ActionRunName);
               printf("ActionWareName[%s]",m->ActionWareName);
               printf("ActionBeAttack1[%s]",m->ActionBeAttack1);
               printf("ActionBeAttack2[%s]",m->ActionBeAttack2);
               printf("ActionBeAttack3[%s]",m->ActionBeAttack3);
               printf("ActionBeAttackDown[%s]",m->ActionBeAttackDown);
               printf("ActionDie[%s]",m->ActionDie);
               printf("SkillName1[%s]",m->SkillName1);
               printf("SkillName2[%s]",m->SkillName2);
               printf("SkillName3[%s]",m->SkillName3);
               printf("SkillName4[%s]",m->SkillName4);
             }

    }

    ActionFileModel *modelData;
    std::string localData;
};

#endif 


#ifndef __MyProjectName_SkillModelBLL_H__
#define __MyProjectName_SkillModelBLL_H__

#include "SkillModel.h"

/**
 k_ClassDes
 */

#define SkillModel_MaxData 20


class SkillModelBLL : public Ref
{
public:
    static SkillModelBLL *create(const std::string& localPath)
    {
        SkillModelBLL *pRet = new(std::nothrow) SkillModelBLL();
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

    ~SkillModelBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    SkillModelBLL()
    {
        modelData=new SkillModel[SkillModel_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return SkillModel_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(SkillModel), SkillModel_MaxData, readFile);
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
        unsigned char* currBuff=&buff[141724];    //141724 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, SkillModel_MaxData*sizeof(SkillModel));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[141724];    //141724 内存文件存在位置
        memcpy(currBuff,modelData, SkillModel_MaxData*sizeof(SkillModel));
        
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
               printf("SkillModelID[%d]",m->SkillModelID);
               printf("Name[%s]",m->Name);
               printf("HeroID[%d]",m->HeroID);
               printf("BasePower[%d]",m->BasePower);
               printf("CurrPower[%d]",m->CurrPower);
               printf("PowerGrow[%d]",m->PowerGrow);
               printf("CurrCDTime[%0.2f]",m->CurrCDTime);
               printf("CdTime[%0.2f]",m->CdTime);
               printf("isTwoWay[%d]",m->isTwoWay);
               printf("AttackDist[%d]",m->AttackDist);
               printf("IconPath[%s]",m->IconPath);
               printf("CurrLv[%d]",m->CurrLv);
               printf("MaxLv[%d]",m->MaxLv);
               printf("AttackCount[%d]",m->AttackCount);
               printf("BaseAttack[%d]",m->BaseAttack);
               printf("CurrAttack[%d]",m->CurrAttack);
               printf("BaseAttackGrow[%d]",m->BaseAttackGrow);
               printf("BasePrice[%d]",m->BasePrice);
               printf("CurrPrice[%d]",m->CurrPrice);
               printf("BasePriceGrow[%d]",m->BasePriceGrow);
               printf("Desc[%s]",m->Desc);
             }

    }

    SkillModel *modelData;
    std::string localData;
};

#endif 


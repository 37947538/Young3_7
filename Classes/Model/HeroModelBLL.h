#ifndef __MyProjectName_HeroModelBLL_H__
#define __MyProjectName_HeroModelBLL_H__

#include "HeroModel.h"

/**
 k_ClassDes
 */

#define HeroModel_MaxData 5


class HeroModelBLL : public Ref
{
public:
    static HeroModelBLL *create(const std::string& localPath)
    {
        HeroModelBLL *pRet = new(std::nothrow) HeroModelBLL();
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

    ~HeroModelBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    HeroModelBLL()
    {
        modelData=new HeroModel[HeroModel_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return HeroModel_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(HeroModel), HeroModel_MaxData, readFile);
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
        unsigned char* currBuff=&buff[28];    //28 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, HeroModel_MaxData*sizeof(HeroModel));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[28];    //28 内存文件存在位置
        memcpy(currBuff,modelData, HeroModel_MaxData*sizeof(HeroModel));
        
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
               printf("HeroID[%d]",m->HeroID);
               printf("HeroName[%s]",m->HeroName);
               printf("ImgFile[%s]",m->ImgFile);
               printf("HeroImgFile[%s]",m->HeroImgFile);
               printf("CommonAttackImg[%s]",m->CommonAttackImg);
               printf("ActionFileModelID[%d]",m->ActionFileModelID);
               printf("LV[%d]",m->LV);
               printf("CurrPower[%d]",m->CurrPower);
               printf("BaseHp[%d]",m->BaseHp);
               printf("CurrHp[%d]",m->CurrHp);
               printf("MaxHp[%d]",m->MaxHp);
               printf("AddHp[%d]",m->AddHp);
               printf("HpGrow[%d]",m->HpGrow);
               printf("HpPosition[%s]",m->HpPosition);
               printf("HpBarWidth[%d]",m->HpBarWidth);
               printf("CurrExp[%d]",m->CurrExp);
               printf("NextExp[%d]",m->NextExp);
               printf("AttackDist[%d]",m->AttackDist);
               printf("BaseAttack[%d]",m->BaseAttack);
               printf("Attack[%d]",m->Attack);
               printf("AddAttack[%d]",m->AddAttack);
               printf("AttackGrow[%d]",m->AttackGrow);
               printf("BaseDef[%d]",m->BaseDef);
               printf("Def[%d]",m->Def);
               printf("AddDef[%d]",m->AddDef);
               printf("DefGrow[%d]",m->DefGrow);
               printf("BaseAttackHit[%0.2f]",m->BaseAttackHit);
               printf("AttackHit[%0.2f]",m->AttackHit);
               printf("AddAttackHit[%0.2f]",m->AddAttackHit);
               printf("RunMoveSpeed[%0.2f]",m->RunMoveSpeed);
               printf("WareMoveSpeed[%0.2f]",m->WareMoveSpeed);
               printf("EffectTypeName[%s]",m->EffectTypeName);
               printf("Price[%d]",m->Price);
             }

    }

    HeroModel *modelData;
    std::string localData;
};

#endif 


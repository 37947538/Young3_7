#ifndef __MyProjectName_EnemyModelBLL_H__
#define __MyProjectName_EnemyModelBLL_H__

#include "EnemyModel.h"

/**
 k_ClassDes
 */

#define EnemyModel_MaxData 16


class EnemyModelBLL : public Ref
{
public:
    static EnemyModelBLL *create(const std::string& localPath)
    {
        EnemyModelBLL *pRet = new(std::nothrow) EnemyModelBLL();
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

    ~EnemyModelBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    EnemyModelBLL()
    {
        modelData=new EnemyModel[EnemyModel_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return EnemyModel_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(EnemyModel), EnemyModel_MaxData, readFile);
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
        unsigned char* currBuff=&buff[3928];    //3928 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, EnemyModel_MaxData*sizeof(EnemyModel));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[3928];    //3928 内存文件存在位置
        memcpy(currBuff,modelData, EnemyModel_MaxData*sizeof(EnemyModel));
        
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
               printf("EnemyID[%d]",m->EnemyID);
               printf("EnemyName[%s]",m->EnemyName);
               printf("BulletName[%s]",m->BulletName);
               printf("IsBulletRate[%d]",m->IsBulletRate);
               printf("BulletStartOffset[%s]",m->BulletStartOffset);
               printf("BulletEndOffset[%s]",m->BulletEndOffset);
               printf("EnemyType[%d]",m->EnemyType);
               printf("EnemyQuality[%d]",m->EnemyQuality);
               printf("HpPosition[%s]",m->HpPosition);
               printf("HpBarWidth[%d]",m->HpBarWidth);
               printf("ActionFileModelID[%d]",m->ActionFileModelID);
               printf("LV[%d]",m->LV);
               printf("AttackDist[%d]",m->AttackDist);
               printf("CatchTime[%s]",m->CatchTime);
               printf("AttackAfterTime[%s]",m->AttackAfterTime);
               printf("AttackBeforeTime[%s]",m->AttackBeforeTime);
               printf("BaseHp[%d]",m->BaseHp);
               printf("CurrHp[%d]",m->CurrHp);
               printf("MaxHp[%d]",m->MaxHp);
               printf("HpGrow[%d]",m->HpGrow);
               printf("BaseAttack[%d]",m->BaseAttack);
               printf("Attack[%d]",m->Attack);
               printf("AttackGrow[%d]",m->AttackGrow);
               printf("ArmorValue[%d]",m->ArmorValue);
               printf("SpeedValue[%0.2f]",m->SpeedValue);
               printf("DropExp[%d]",m->DropExp);
               printf("DropValue[%d]",m->DropValue);
               printf("EffectTypeName[%s]",m->EffectTypeName);
             }

    }

    EnemyModel *modelData;
    std::string localData;
};

#endif 


#ifndef __MyProjectName_EnemyBevTreeModelBLL_H__
#define __MyProjectName_EnemyBevTreeModelBLL_H__

#include "EnemyBevTreeModel.h"

/**
 k_ClassDes
 */

#define EnemyBevTreeModel_MaxData 4


class EnemyBevTreeModelBLL : public Ref
{
public:
    static EnemyBevTreeModelBLL *create(const std::string& localPath)
    {
        EnemyBevTreeModelBLL *pRet = new(std::nothrow) EnemyBevTreeModelBLL();
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

    ~EnemyBevTreeModelBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    EnemyBevTreeModelBLL()
    {
        modelData=new EnemyBevTreeModel[EnemyBevTreeModel_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return EnemyBevTreeModel_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(EnemyBevTreeModel), EnemyBevTreeModel_MaxData, readFile);
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
        unsigned char* currBuff=&buff[43476];    //43476 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, EnemyBevTreeModel_MaxData*sizeof(EnemyBevTreeModel));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[43476];    //43476 内存文件存在位置
        memcpy(currBuff,modelData, EnemyBevTreeModel_MaxData*sizeof(EnemyBevTreeModel));
        
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
               printf("EnemyBevTreeModel[%d]",m->EnemyBevTreeModel);
               printf("ParentID[%d]",m->ParentID);
               printf("NodeType[%s]",m->NodeType);
               printf("NodeValue[%d]",m->NodeValue);
               printf("Name[%s]",m->Name);
               printf("ClassName[%s]",m->ClassName);
               printf("Condition[%s]",m->Condition);
               printf("ConditionKey[%s]",m->ConditionKey);
               printf("ConditionDes[%s]",m->ConditionDes);
             }

    }

    EnemyBevTreeModel *modelData;
    std::string localData;
};

#endif 


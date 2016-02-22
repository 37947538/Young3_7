//
//  LevelBLL.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/11.
//
//

#include "LevelBLL.h"
#include "LevelModel.h"
#include "MapLayer.h"

static std::string BossLevelAttackTimer[]{ "{{14,10},{1,3}}", "{{5,20},{1,3}}", "{{13,30},{1,3}}", "{{3,40},{1,3}}", "{{15,50},{1,3}}" };

static LevelBLL *_sharedLevelBLL=nullptr;

LevelBLL* LevelBLL::instance()
{
    if (nullptr == _sharedLevelBLL)
    {
        _sharedLevelBLL = new LevelBLL();
    }
    return _sharedLevelBLL;
}

void LevelBLL::destory()
{
    if (_sharedLevelBLL) {
        CC_SAFE_DELETE(_sharedLevelBLL);
    }
}

LevelBLL::~LevelBLL()
{
    CC_SAFE_DELETE(m_LevelModel);
    CC_SAFE_DELETE(m_EnemyGroup);
}

LevelBLL::LevelBLL()
{
    m_IsTryGame=false;
    m_IsParsed=false;
    m_IsBossLevel=false;
    m_LevelModel=new LevelModel();
    m_EnemyGroup=new EnemyGroup();
    m_EnemyGroup->className="根";
    m_PlayerSelecLevelID=-1;
}

void LevelBLL::parse(LevelModel* levelModel)
{
    if (m_IsParsed) {
        return;
    }
    m_IsParsed=true;
    
    m_LevelBgWidth=levelModel->LevelWidth;
    m_LevelHeight=levelModel->LevelHigth;
    
    //解析敌兵字符串
    std::string attackTimer=levelModel->AttackTimer;
    //BOSS关卡敌兵字符串
    if (m_IsBossLevel && !m_IsTryGame) {
        attackTimer=BossLevelAttackTimer[m_PlayerSelecLevelID];
    }
    std::vector<std::string> results;
    APStringHelper::split(attackTimer, "#" ,&results);
    log("AttackTimer:%s",attackTimer.c_str());
    float beginPos=380;     //起始位置
    float attackDirectoWidth=(m_LevelBgWidth-beginPos) / results.size();

    for (int i=0; i<results.size(); i++) {
        std::string enemyConfig=results.at(i);
        std::vector<std::string> bigGroup;
        APStringHelper::split(enemyConfig, "@" ,&bigGroup);
        
        Rect mapRect=Rect(beginPos+i*attackDirectoWidth,0,960,640);
        
        auto mapm_EnemyGroup=EnemyGroup::create();
        mapm_EnemyGroup->className="地图段";
        mapm_EnemyGroup->mapRect=mapRect;
        m_EnemyGroup->add(mapm_EnemyGroup);
        
        for (int j=0; j<bigGroup.size(); j++) {
            std::string bigGroupString=bigGroup.at(j);
            std::vector<std::string> smallGroup;
            APStringHelper::split(bigGroupString, "-", &smallGroup);
            
            auto bigm_EnemyGroup=EnemyGroup::create();
            bigm_EnemyGroup->className="大组";
            bigm_EnemyGroup->mapRect=mapRect;
            mapm_EnemyGroup->add(bigm_EnemyGroup);
            
            for (auto s : smallGroup) {
                Rect enemyRect=RectFromString(s);
                
                int enemyID=(int)enemyRect.origin.x;
                enemyIDs.insert(enemyID);
                
                auto smallm_EnemyGroup=EnemyGroup::create();
                smallm_EnemyGroup->className="怪";
                smallm_EnemyGroup->mapRect=mapRect;
                smallm_EnemyGroup->enemyRect=enemyRect;
                smallm_EnemyGroup->enemyRectString=s;
                bigm_EnemyGroup->add(smallm_EnemyGroup);
            }
        }
    }
}

int LevelBLL::getLevelWidth(LevelModel* lModel)
{
    if (!m_IsParsed) {
        parse(lModel);
    }
    return m_LevelBgWidth;
}

//获取当前关卡背景层
MapLayer* LevelBLL::getLevelLayer(LevelModel* levelModel,float bgWidth,float bgHeight)
{
    MapLayer *bgLayer=MapLayer::create(Color4B(0,0,0,0), bgWidth, bgHeight);
    bgLayer->setAnchorPoint(Vec2(0,0));
    bgLayer->setPosition(Vec2(0,0));
    
    auto bgSpr=Sprite::create(levelModel->BackgroundFile);
    float imgBgWidth=bgSpr->getBoundingBox().size.width;
    int bgNum=bgWidth / imgBgWidth;
    bgNum++;
    
    for (int i=0; i<bgNum; i++) {
        auto bg=Sprite::create(levelModel->BackgroundFile);
        bg->setAnchorPoint(Vec2(0,0));
        bg->setPosition(Vec2(i*imgBgWidth,0));
        bgLayer->addChild(bg);
        
        if (i % 2==1) {
            bg->setFlippedX(true);
        }
    }
    return bgLayer;
}

void LevelBLL::getEnemyRect(const Vec2& pos, Vector<EnemyGroup*>& enemys)
{
    //地图段
    auto mapGroup=m_EnemyGroup->enemys.at(0);
    if (mapGroup) {
        //大组
        auto bigGroup=mapGroup->enemys.at(0);
        if (bigGroup) {
            if (bigGroup->mapRect.containsPoint(pos)){
                enemys=bigGroup->enemys;
                bigGroup->enemys.clear();
            }
            bigGroup->removeForParent();
        }
        mapGroup->removeForParent();
    }
}

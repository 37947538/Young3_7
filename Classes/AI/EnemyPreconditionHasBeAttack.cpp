//
//
//   是否被攻击
//
//
//

#include "EnemyPreconditionHasBeAttack.h"
#include "EnemyBevTreeData.h"
#include "AnimateTools.h"


bool EnemyPreconditionHasBeAttack::externalCondition(const BevNodeInputParam& input) const
{
    const EnemyBevInputData&  inputData	= input.getRealDataType<EnemyBevInputData>();
    
    if(inputData.attackList.size() >0)
    {
        return false;
    }
    
    if (AnimateTools::isBeAttackAnimatePlaying(inputData.m_Owner)) {
        return false;
    }
    
    
    return true;
}

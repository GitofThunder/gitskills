#include "Food.h"

CFood::CFood() : m_eFoodType(FT_ORIGIN)
{
    m_vMaterials.clear();
    for (int i = 0; i < TT_MAX; i++)
    {
        m_aTastes[i] = 0;
    }
}

CFood::~CFood()
{
    
}

bool CFood::init()
{
    if (!Sprite::init()) return false;
    return true;
}

void CFood::initProperty(FOOD_TYPE eType, std::vector<int>& vMaterials, int aTastes[], int nIndex)
{
    m_eFoodType = eType;
    m_vMaterials.clear();
    for (int i = 0; i < vMaterials.size(); i++)
    {
        m_vMaterials.push_back(vMaterials[i]);
    }
    
    m_aTastes[0] = aTastes[0];
    m_aTastes[1] = aTastes[1];
    
    m_nPanziIndex = nIndex;
}

bool CFood::isPointWithinFood(Vec2 v2Pt)
{
    return true;
}
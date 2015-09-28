#include "Food.h"
#include "FoodMaterial.h"
#include "FoodPiece.h"
#include "GlobalData.h"

float GLOBAL_SELF_SCALE = 0;

Vec2 PANZI_POSITION[5];

void CFoodInfo::initProperty(FOOD_TYPE eType, std::vector<int>& vMaterials, int aTastes[], int nIndex)
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

void CFoodInfo::initWithFood(CFood* pFood)
{
    if (pFood == NULL)
        return;
    
    m_eFoodType = pFood->getFoodType();
    m_vMaterials.clear();
    std::vector<int> vMaterials = pFood->getMaterials();
    for (int i = 0; i < vMaterials.size(); i++)
    {
        m_vMaterials.push_back(vMaterials[i]);
    }
    
    m_aTastes[0] = pFood->getTastes(TT_SUAN);
    m_aTastes[1] = pFood->getTastes(TT_LA);
    
    m_nPanziIndex = pFood->getPanziIndex();
}



CGlobalData::CGlobalData() : m_bHighRes(false)
{
    m_eLanguageType = Application::getInstance()->getCurrentLanguage();
    if(m_eLanguageType != LanguageType::CHINESE)
    {
        m_eLanguageType = LanguageType::ENGLISH;
    }
    for (int i = 0; i < PANZI_FOOD_COUNT; i++)
    {
        m_aPanziFood[i] = NULL;
    }
}

CGlobalData::~CGlobalData()
{
    
}

CGlobalData* CGlobalData::getSingleton(void)
{
    static CGlobalData mGlobalData;
    return &mGlobalData;
}

void CGlobalData::setPanziFood(int nIndex, CFood* pFood)
{
    if (nIndex >= PANZI_FOOD_COUNT) return;
    
    if (pFood == NULL)
    {
        delete m_aPanziFood[nIndex];
        m_aPanziFood[nIndex] = NULL;
    }
    else
    {
        if (m_aPanziFood[nIndex] == NULL)
        {
            m_aPanziFood[nIndex] = new CFoodInfo();
        }
        m_aPanziFood[nIndex]->initWithFood(pFood);
        m_aPanziFood[nIndex]->setPanziIndex(nIndex);
    }
}

CFoodInfo* CGlobalData::getPanziFood(int nIndex)
{
    if (nIndex < 0 || nIndex >= PANZI_FOOD_COUNT) return NULL;
    
    return m_aPanziFood[nIndex];
}

CFood* CGlobalData::createFoodByInfo(int nIndex)
{
    CFood* pFood = NULL;
    if (nIndex < 0 || nIndex >= PANZI_FOOD_COUNT) return NULL;
    CFoodInfo* pFoodInfo = m_aPanziFood[nIndex];
    if (pFoodInfo != NULL && pFoodInfo->getMaterials().size() > 0)
    {
        FOOD_TYPE eType = pFoodInfo->getFoodType();
        switch (eType)
        {
            case FT_ORIGIN:
            {
                pFood = CFoodMaterial::create((MATERIAL_ID)pFoodInfo->getMaterials()[0]);
                break;
            }
            case FT_SUIPIAN:
            {
                pFood = CFoodPiece::create((MATERIAL_ID)pFoodInfo->getMaterials()[0]);
                break;
            }
            case FT_CHUAN:
            {
                break;
            }
            case FT_TANG:
            {
                break;
            }
            case FT_SHALA:
            {
                break;
            }
            case FT_YINLIAO:
            {
                break;
            }
            default:
                break;
        }
        
        if (pFood != NULL)
        {
            std::vector<int> vMaterials;
            vMaterials.clear();
            for (int i = 0; i < pFoodInfo->getMaterials().size(); i++)
            {
                vMaterials.push_back(pFoodInfo->getMaterials()[i]);
            }
            
            int aTastes[2] = {0, 0};
            pFood->initProperty(eType, vMaterials, aTastes, nIndex);
        }
    }

    return pFood;
}

void CGlobalData::clearPanziFood()
{
    for (int i = 0; i < PANZI_FOOD_COUNT; i++)
    {
        m_aPanziFood[i] = NULL;
    }
}

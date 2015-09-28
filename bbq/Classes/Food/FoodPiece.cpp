#include "FoodPiece.h"
#include "cocostudio/CocoStudio.h"

CFoodPiece::CFoodPiece()
{
    m_eFoodType = FT_ORIGIN;
}

CFoodPiece::~CFoodPiece()
{
    
}

CFoodPiece* CFoodPiece::create(const char *pszFileName)
{
    CFoodPiece* pRet = new (std::nothrow) CFoodPiece();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

CFoodPiece* CFoodPiece::create(MATERIAL_ID eId)
{
    if (eId < MI_XIANGJIAO || eId >= MI_MAX) return NULL;
    
    CFoodPiece* pRet = new (std::nothrow) CFoodPiece();
    const char* pszFileName = MATERIAL_CONFIG[eId].sConfigName.c_str();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool CFoodPiece::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    
    
    schedule(schedule_selector(CFoodPiece::myUpdate));
    return true;
}

bool CFoodPiece::isPointWithinFood(Vec2 v2Pt)
{
    return false;
}

void CFoodPiece::myUpdate(float fEscapeTime)
{
    
}

bool CFoodPiece::initWithFile(const char *pszFileName)
{
    if (!CFood::init())
    {
        return false;
    }
    
    createNodeByCsb(pszFileName);
    
    return true;
}

void CFoodPiece::createNodeByCsb(const char *pszFileName)
{
    m_foodpieces = CSLoader::createNode(pszFileName);
    if (m_foodpieces != NULL)
    {
        this->addChild(m_foodpieces);
    }
}

Node* CFoodPiece::getChildByTag(int tag)
{
    Node* _tempNode = nullptr;
    if (m_foodpieces) {
        _tempNode = m_foodpieces->getChildByTag(tag);
    }
    return _tempNode;
}

Vector<Node*>& CFoodPiece::getChildren()
{
    return m_foodpieces->getChildren();
}
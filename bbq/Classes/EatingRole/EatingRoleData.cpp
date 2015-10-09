//
//  EatingRoleData.cpp
//  TravelDemo
//
//  Created by kids on 15/8/24.
//
//

#include "EatingRoleData.h"
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

const std::string EATING_ROLE_MEMBERS_NAMES[EATING_ROLE_INDEX::MAX_ROLE_NUM] =
{
    "Guest01",
    "Guest02",
    "Guest03",
    "Guest04",
    "Guest05",
    "Guest06",
    "Guest07",
    "Guest08",
    "Guest09",
    "Guest10",
    "Guest12"
};

const std::string EATING_ROLE_EYES_NAMES[EATING_ROLE_INDEX::MAX_ROLE_NUM * 2] =
{
    "G01_eyeballA",
    "G01_eyeballB",
    "G02_eyeball",
    "G02_eyeball_0",
    "G03_eyeball",
    "G03_eyeball_0",
    "g04_eyeball",
    "g04_eyeball_0",
    "G05_eye",
    "",
    "G06_eye",
    "",
    "G07_eyeB",
    "G07_eyeA",
    "G01_eyeball",           //Guest08
    "G01_eyeball_0",
    "G09_eye",
    "",
    "G10_eyeball",
    "G10_eyeball_0",
    "G12_eye",
    "",
};


const int EATING_ROLE_ARMATURE_BETWEEN_NUM[EATING_ROLE_INDEX::MAX_ROLE_NUM] =
{
    4,  //01
    3,  //02
    3,  //03
    4,  //04
    4,  //05
    3,  //06
    4,  //07
    4,  //08
    6,  //09
    4,  //10
    3,  //12
};

//用于加载人物信息的时候使用。
const char* EATING_MATERIALS[MATERIAL_ID::MI_MAX] =
{
    "xiangjiao",
    "xihongshi",
    "jitui",
    "boluo"
};


const char* EATING_TASTE[TASTE_TYPE::TT_MAX] = {
    "sour",
    "hot",
};


EatingRoleData* EatingRoleData::m_EatingRoleData = nullptr;

ERoleInfo EatingRoleData::ZERO = ERoleInfo();

EatingRoleData::EatingRoleData()
{
    for (int i = 0; i < sizeof(m_roleID)/sizeof(int); ++i) {
        m_roleID[i] = -1;
    }
    
    m_eRoleInfos.clear();
}

EatingRoleData::~EatingRoleData()
{
    delete m_EatingRoleData;
    m_eRoleInfos.clear();
}

EatingRoleData* EatingRoleData::getInstance()
{
    if (!m_EatingRoleData) {
        m_EatingRoleData = new EatingRoleData();
    }
    
    return m_EatingRoleData;
}

void EatingRoleData::resetRoleIDs()
{
    for (int i = 0; i < sizeof(m_roleID)/sizeof(int); ++i) {
        m_roleID[i] = -1;
    }
}

void EatingRoleData::saveRoleID(int _index, int _roleID)
{
    if (_index >= sizeof(m_roleID)/sizeof(int)) {
        log("_index is bigger than the size of array m_roleID");
    }
    m_roleID[_index] = _roleID;
}

int EatingRoleData::getSizeofRoleID()
{
    return sizeof(m_roleID)/sizeof(int);
}

int EatingRoleData::getRoleID(int index)
{
    if (index > sizeof(m_roleID)/sizeof(int) || index < 0) {
        log("index is out of range");
        return -1;
    }
    
    return m_roleID[index];
}


void EatingRoleData::loadRoleInfoFromXml()
{
    XMLDocument* xmldoc = new XMLDocument();
    long nSize;
    unsigned char* pxmlBuffer = FileUtils::getInstance()->getFileData("xmlconfig.xml", "rb", &nSize);
    if (!pxmlBuffer) {
        log("******can not read xml file******");
        return;
    }
    
    xmldoc->Parse((const char*)pxmlBuffer);
    free(pxmlBuffer);
    pxmlBuffer = nullptr;
    
    XMLElement* root = xmldoc->RootElement();
    if (!root) {
        log("******read root node error******");
        return;
    }
    XMLElement* rootfirst = root->FirstChildElement();
    while (rootfirst)
    {
        const char* dictname = rootfirst->Value();
        if (!strcmp(dictname, "record"))
        {
            ERoleInfo info;
            info.m_RoleID = rootfirst->IntAttribute("id");
            
            for (int i = 0; i < sizeof(EATING_MATERIALS)/sizeof(char*); ++i) {
                info.m_Material_Score[i] = rootfirst->IntAttribute(EATING_MATERIALS[i]);
            }
            
            for (int i = 0; i < sizeof(EATING_TASTE)/sizeof(char*); ++i) {
                info.m_TasteBear_Score[i] = rootfirst->IntAttribute(EATING_TASTE[i]);
            }
        }
        rootfirst = rootfirst->NextSiblingElement();
    }
    
    delete xmldoc;
}


ERoleInfo& EatingRoleData::getERoleInfo(int RoleID)
{
    if (RoleID > MAX_ROLE_NUM || RoleID < 0) {
        log("***** the RoleID is out of range ******");
        return EatingRoleData::ZERO;
    }
    
    return m_eRoleInfos.at(RoleID);
}

int EatingRoleData::getRoleMaterialScore(int RoleID, int materialID)
{
    if (RoleID > MAX_ROLE_NUM || RoleID < 0) {
        log("****** the RoleID is out of range ******");
        return 0;
    }
    
    if (materialID > MATERIAL_ID::MI_MAX || materialID < 0) {
        log("****** the materialID is out of range ******");
        return 0;
    }
    
    return m_eRoleInfos.at(RoleID).m_Material_Score[materialID];
}

int EatingRoleData::getRoleTasteBearScore(int RoleID, int tasteID)
{
    if (RoleID > MAX_ROLE_NUM || RoleID < 0) {
        log("****** the RoleID is out of range ******");
        return 0;
    }
    
    if (tasteID > TT_MAX || RoleID < 0) {
        log("****** the tasteID is out of range ******");
        return 0;
    }
    
    return m_eRoleInfos.at(RoleID).m_TasteBear_Score[tasteID];
}
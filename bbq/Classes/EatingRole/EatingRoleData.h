//
//  EatingRoleData.h
//  TravelDemo
//
//  Created by kids on 15/8/24.
//
//

#ifndef __TravelDemo__EatingRoleData__
#define __TravelDemo__EatingRoleData__

#include <stdio.h>
#include "cocos2d.h"
#include "MacroVariable.h"
USING_NS_CC;


enum EATING_SCENE_STATE
{
    ESS_PICKING,
    ESS_EATING
};

enum EATING_ROLE_INDEX
{
    Guest01 = 0,
    Guest02,
    Guest03,
    Guest04,
    Guest05,
    Guest06,
    Guest07,
    Guest08,
    Guest09,
    Guest10,
    Guest12,
    MAX_ROLE_NUM
};

struct ERoleInfo
{
    int m_RoleID;
    int m_Material_Score[MATERIAL_ID::MI_MAX];
    int m_TasteBear_Score[TASTE_TYPE::TT_MAX];
};

extern const std::string EATING_ROLE_MEMBERS_NAMES[EATING_ROLE_INDEX::MAX_ROLE_NUM];
extern const std::string EATING_ROLE_EYES_NAMES[EATING_ROLE_INDEX::MAX_ROLE_NUM * 2];
extern const int EATING_ROLE_ARMATURE_BETWEEN_NUM[EATING_ROLE_INDEX::MAX_ROLE_NUM];

class EatingRoleData
{
public:
    EatingRoleData();
    ~EatingRoleData();
    
    static EatingRoleData* getInstance();
    void resetRoleIDs();
    
    void saveRoleID(int _index, int _roleID);
    int getRoleID(int index);
    int getSizeofRoleID();
    
    void loadRoleInfoFromXml();
    ERoleInfo& getERoleInfo(int RoleID);
    
    int getRoleMaterialScore(int RoleID, int materialID);
    int getRoleTasteBearScore(int RoleID, int tasteID);
    
private:
    static EatingRoleData* m_EatingRoleData;
    int m_roleID[4];    //一一对应从一到四的四个角色的位置，值为-1时说明此时位置上没有人
    std::map<int, ERoleInfo> m_eRoleInfos;  //角色与食材相关的信息
public:
    static ERoleInfo ZERO;
};

#endif /* defined(__TravelDemo__EatingRoleData__) */

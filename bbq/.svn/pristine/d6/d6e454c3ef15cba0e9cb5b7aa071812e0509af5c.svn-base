#ifndef __MACROVARIABLE_H__
#define __MACROVARIABLE_H__

#include "cocos2d.h"

#define FRIDGE_FLOOR    6
#define FLOOR_OFFSET    300
#define FOOD_COUNT      FRIDGE_FLOOR * 3
#define DRAG_SCALE      1.2f

// 食物种类
enum FOOD_TYPE
{
    FT_ORIGIN = 0,  // 没切过的
    FT_SUIPIAN,     // 切碎的
    FT_CHUAN,       // 串
    FT_SHALA,       // 沙拉
    FT_TANG,        // 汤
    FT_YINLIAO,     // 饮料
    
    FT_MAX
};

// 食材id
enum MATERIAL_ID
{
    MI_XIANGJIAO = 0,
    MI_XIHONGSHI,
    MI_JITUI,
    MI_BOLUO,
    MI_MAX
};

// 味道 酸 辣
enum TASTE_TYPE
{
    TT_SUAN = 0,
    TT_LA,
    
    TT_MAX
};

// 客人id
enum GUEST_ID
{
    GI_MIANYANG = 0,
    GI_MAO,
    
    GI_MAX
};

enum SCENE_CONVERT
{
    SC_GET2MAKE = 0,
    SC_CUT2MAKE,
    SC_MAX
};

struct SMaterialConfig
{
    MATERIAL_ID eMaterial;  //材料id（暂时没用）
    std::string sName;      //素材名称
    int nType;              //肉类 蔬菜类等
    int nSideLen;
    std::string sPieceName;
    int nCount;
    std::string sConfigName;  //材料片摆布的配置文件名称
    /*
    SMaterialConfig(MATERIAL_ID material, std::string name, int type)
    {
        eMaterial = material;
        sName = name;
        nType = type;
    }
     */
};

extern const SMaterialConfig MATERIAL_CONFIG[MI_MAX];
extern const MATERIAL_ID FRIDGE_CONFIG[FOOD_COUNT];

#endif
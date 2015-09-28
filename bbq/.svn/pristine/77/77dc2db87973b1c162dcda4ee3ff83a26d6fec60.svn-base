#ifndef __PolygonSprite_H__
#define __PolygonSprite_H__

#include "cocos2d.h"
#include "PRFilledPolygon.h"

#define PTM_RATIO 32

typedef enum _State
{
    kStateIdle = 0,
    kStateTossed
} State;

typedef enum _Type
{
    kTypeWatermelon = 0,
    kTypeStrawberry,
    kTypePineapple,
    kTypeGrapes,
    kTypeBanana,
    kTypeBomb
} Type;

class CPolygonSprite : public PRFilledPolygon
{
public:
    CPolygonSprite* initWithTexture(Texture2D* texture, PhysicsBody* body, bool original);
    CPolygonSprite* initWithFile(const std::string& filename, PhysicsBody* body, bool original);
    
    static CPolygonSprite* spriteWithFile(const std::string& filename, PhysicsBody* body, bool original);
    static CPolygonSprite* spriteWithTexture(Texture2D* texture, PhysicsBody* body, bool original);
    virtual CPolygonSprite* initWithWorld(PhysicsWorld* world);
    static CPolygonSprite* spriteWithWorld(PhysicsWorld* world);
    
    PhysicsBody* createBodyForWorld(PhysicsWorld* world, b2Vec2 position, float rotation, b2Vec2* vertices, int vertexCount, float density, float friction, float restitution);
    void activateCollisions();
    void deactivateCollisions();

    virtual void setPosition(const Vec2& position);
    
private:
    bool _original;
    Vec2 _centroid;
    bool _sliceEntered;
    bool _sliceExited;

    double _sliceEntryTime;
    State _state;
    Type _type;
    ParticleSystemQuad *_splurt;
};

#endif
//
//  PolygonSprite.m
//  CutCutCut
//
//  Created by Allen Benson G Tan on 5/20/12.
//  Copyright 2012 WhiteWidget Inc. All rights reserved.
//

#include "PolygonSprite.h"

CPolygonSprite* CPolygonSprite::spriteWithFile(const std::string& filename, PhysicsBody* body, bool original)
{
    CPolygonSprite *sprite = new (std::nothrow) CPolygonSprite();
    if (sprite && sprite->initWithFile(filename, body, original))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

CPolygonSprite* CPolygonSprite::spriteWithTexture(Texture2D* texture, PhysicsBody* body, bool original)
{
    CPolygonSprite *sprite = new (std::nothrow) CPolygonSprite();
    if (sprite && sprite->initWithTexture(texture, body, original))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

CPolygonSprite* CPolygonSprite::spriteWithWorld(PhysicsWorld* world)
{
    CPolygonSprite *sprite = new (std::nothrow) CPolygonSprite();
    if (sprite && sprite->initWithWorld(world))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

CPolygonSprite* CPolygonSprite::initWithFile(const std::string& filename, PhysicsBody* body, bool original)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    return initWithTexture(texture, body, original);
}

CPolygonSprite* CPolygonSprite::initWithTexture(Texture2D* texture, PhysicsBody* body, bool original)
{
    // gather all the vertices from our Box2D shape
    PhysicsShapePolygon* shape = (PhysicsShapePolygon*)body->getFirstShape();
    int vertexCount = shape->getPointsCount();
    
    Vector2dVector points;
    Vec2* v2Points = new Vec2[vertexCount];
    for(int i = 0; i < vertexCount; i++)
    {
        Vector2d v2Point = Vector2d(shape->getPoint(i).x, shape->getPoint(i).y);
        points.push_back(v2Point);
        v2Points[i] = shape->getPoint(i);
    }

    if (PRFilledPolygon::initWithPointsAndTexture(points, texture))
    {
        _sliceExited = false;
        _sliceEntered = false;
        _sliceExited = 0;
        _updateTransformFromPhysics = true;
        _original = original;
        // gets the center of the polygon
        _centroid = shape->getPolyonCenter(v2Points, vertexCount);
        // assign an anchor point based on the center
        setAnchorPoint(Vec2(_centroid.x * PTM_RATIO / texture->getContentSize().width,
                            _centroid.y * PTM_RATIO / texture->getContentSize().height));
        _state = kStateIdle;
    }
    return this;
}

CPolygonSprite* CPolygonSprite::initWithWorld(PhysicsWorld *world)
{
    //nothing to do here
    return NULL;
}

/*
 * Creates a Box2D body that doesn't collide with anything
 */
PhysicsBody* CPolygonSprite::createBodyForWorld(PhysicsWorld* world, Vec2 position, float rotation, Vec2* vertices, int count, float density, float friction, float restitution)
{
    /*
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    bodyDef.angle = rotation;
    b2Body *body = world->CreateBody(&bodyDef);
    
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.filter.categoryBits = 0;
    fixtureDef.filter.maskBits = 0;
    fixtureDef.isSensor = true;
    
    b2PolygonShape shape;
    shape.Set(vertices, count);
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
    
    return body;
     */
    return NULL;
}

#pragma mark - Public Methods

/*
 * Overloaded setPosition method to include the Box2D body in the position adjustment
 */
/*
void CPolygonSprite::setPosition(const Vec2& position)
{
    Node::setPosition(position);
}
*/
/*
 * Sets the category and mask bits to collide with itself
 */
void CPolygonSprite::activateCollisions()
{

}

/*
 * Sets the category and mask bits to not collide with anything
 */
void CPolygonSprite::deactivateCollisions()
{

}


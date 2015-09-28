//
//  PolygonSprite.m
//  CutCutCut
//
//  Created by Allen Benson G Tan on 5/20/12.
//  Copyright 2012 WhiteWidget Inc. All rights reserved.
//

#include "PolygonSprite.h"

CPolygonSprite* CPolygonSprite::spriteWithFile(const std::string& filename, b2Body* body, bool original)
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

CPolygonSprite* CPolygonSprite::spriteWithTexture(Texture2D* texture, b2Body* body, bool original)
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

CPolygonSprite* CPolygonSprite::spriteWithWorld(b2World* world)
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

CPolygonSprite* CPolygonSprite::initWithFile(const std::string& filename, b2Body* body, bool original)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    return initWithTexture(texture, body, original);
}

CPolygonSprite* CPolygonSprite::initWithTexture(Texture2D* texture, b2Body* body, bool original)
{
    // gather all the vertices from our Box2D shape
    b2Fixture *originalFixture = body->GetFixtureList();
    b2PolygonShape *shape = (b2PolygonShape*)originalFixture->GetShape();
    int vertexCount = shape->GetVertexCount();
    
    Vector2dVector points;
    for(int i = 0; i < vertexCount; i++)
    {
        Vector2d v2Point = Vector2d(shape->GetVertex(i).x * PTM_RATIO, shape->GetVertex(i).y * PTM_RATIO);
        points.push_back(v2Point);
    }

    if (PRFilledPolygon::initWithPointsAndTexture(points, texture))
    {
        _sliceExited = false;
        _sliceEntered = false;
        _entryPoint.SetZero();
        _exitPoint.SetZero();
        _sliceExited = 0;
        _body = body;
        _updateTransformFromPhysics = true;
        _body->SetUserData(this);
        _original = original;
        // gets the center of the polygon
        _centroid = _body->GetLocalCenter();
        // assign an anchor point based on the center
        setAnchorPoint(Vec2(_centroid.x * PTM_RATIO / texture->getContentSize().width,
                            _centroid.y * PTM_RATIO / texture->getContentSize().height));
        _state = kStateIdle;
    }
    return this;
}

CPolygonSprite* CPolygonSprite::initWithWorld(b2World *world)
{
    //nothing to do here
    return NULL;
}

/*
 * Creates a Box2D body that doesn't collide with anything
 */
b2Body* CPolygonSprite::createBodyForWorld(b2World* world, b2Vec2 position, float rotation, b2Vec2* vertices, int count ,float density, float friction, float restitution)
{
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
}

#pragma mark - Public Methods

/*
 * Overloaded setPosition method to include the Box2D body in the position adjustment
 */
void CPolygonSprite::setPosition(const Vec2& position)
{
    Node::setPosition(position);
    _body->SetTransform(b2Vec2(position.x/PTM_RATIO,position.y/PTM_RATIO), _body->GetAngle());
}

/*
 * Sets the category and mask bits to collide with itself
 */
void CPolygonSprite::activateCollisions()
{
    b2Fixture *fixture = _body->GetFixtureList();
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = 0x0001;
    filter.maskBits = 0x0001;
    fixture->SetFilterData(filter);
}

/*
 * Sets the category and mask bits to not collide with anything
 */
void CPolygonSprite::deactivateCollisions()
{
    b2Fixture *fixture = _body->GetFixtureList();
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = 0;
    filter.maskBits = 0;
    fixture->SetFilterData(filter);
}


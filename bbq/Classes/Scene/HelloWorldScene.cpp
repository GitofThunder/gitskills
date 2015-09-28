#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    initPhysics();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    /*
    Sprite* pTest = Sprite::create("pineapple.png");
    if (pTest != NULL)
    {
        this->addChild(pTest, 3);
    }
    //
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody; // set the kind of the sprite
    bodydef.position.Set(500 / PTM_RATIO, 300 / PTM_RATIO);
    
    //body
    b2Body *body = world->CreateBody(&bodydef);
    
    //shape
    b2PolygonShape dynamicShape;
    dynamicShape.SetAsBox(.5f, .5f);
    
    b2FixtureDef fixtureDef;//set the 精灵添加夹具
    fixtureDef.shape = &dynamicShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
    
    //set bodydef values;
    body->CreateFixture(&fixtureDef);
    
    pTest->setPhysicsBody(body);
    */
    
    
    
    schedule(schedule_selector(HelloWorld::update));
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::initPhysics()
{
    Size s = Director::getInstance()->getVisibleSize();
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -4.25f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    
    world->SetContinuousPhysics(true);
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    /*
     groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
     groundBody->CreateFixture(&groundBox,0);
     
     // top
     groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
     groundBody->CreateFixture(&groundBox,0);
     
     // left
     groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
     groundBody->CreateFixture(&groundBox,0);
     
     // right
     groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
     groundBody->CreateFixture(&groundBox,0);*/
}

void HelloWorld::update(float delta)
{
    int32 velocityIterations = 8;
    int32 positionIterations = 1;
    
    world->Step(delta, velocityIterations, positionIterations);
    
    /*
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext())
    {
        if(b->GetUserData()!=NULL)
        {
            Sprite *sprite=(Sprite*)b->GetUserData();
            
            sprite->setPosition(ccp(b->GetPosition().x*32,b->GetPosition().y*32));
            sprite->setRotation((-1)*CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
     */
}


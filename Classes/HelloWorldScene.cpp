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

	tiledmap = TMXTiledMap::create("map/Map.tmx");
//	tiledmap->setTileSize(Size(32,32));
	addChild(tiledmap);

	barrier = tiledmap->getLayer("barrier");

	TMXObjectGroup* objects = tiledmap->getObjectGroup("objects");
	ValueMap ninja = objects->getObject("ninja");
	int x = ninja["x"].asInt();
	int y = ninja["y"].asInt();

	auto ninjaPlayer = Sprite::create("ninja.png");
	ninjaPlayer->setPosition(x,y);
	ninjaPlayer->setTag(001);
	addChild(ninjaPlayer);

	return true;
}


void HelloWorld::onEnter()
{
	Layer::onEnter();
//注册触摸事件监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
//设置监听属性
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
	
		return true;
	};
	listener->onTouchMoved = [](Touch* touch, Event* event)
	{

	};
//	auto targetSpriteNinja = this->getChildByTag(001);

//	Vec2 position; //= targetSpriteNinja->getPosition();
	listener->onTouchEnded = [ this](Touch* touch, Event* event)
	{
		auto target = static_cast<Layer*>(event->getCurrentTarget());
		Vec2 touchPosition = touch->getLocation();
		log("touchposition is (%d,%d)",touchPosition.x,touchPosition.y);

		auto targetSpriteNinja = target->getChildByTag(001);
		Vec2 ninjaPosition = targetSpriteNinja->getPosition();

		log("ninjaposition is (%d,%d)",ninjaPosition.x,ninjaPosition.y);

//		Vec2 ninjaSpaceTouchPosition = targetSpriteNinja->convertToNodeSpace(touchPosition);
		int x = touchPosition.x - ninjaPosition.x;
		int y = touchPosition.y - ninjaPosition.y;
//		log("x is %d, y is %d", x, y);
		int a = x-y;
		int b = x+y;
//		log("a is %d, b is %d", a, b);
		if(a>0){
			if(b>0){
				targetSpriteNinja->runAction(FlipX::create(false)); //false表示不翻转
				ninjaPosition.x += 32;
			}
			else{
				ninjaPosition.y -= 32;
			}
		}
		else {
			if(b<0){
				targetSpriteNinja->runAction(FlipX::create(true));//true表示翻转
				ninjaPosition.x -= 32;
			}
			else {
				ninjaPosition.y += 32;
			}
		};	
		this->setNinjaPosition(ninjaPosition);
		this->setViewCentrePoint(ninjaPosition);
	};
	
//注册事件分发器
	auto listenerDispatcher = Director::getInstance()->getEventDispatcher();
	listenerDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void HelloWorld::setNinjaPosition(Vec2 position)
{
	
	Vec2 ninjaTiledposition = this->tiledCoordFromPosition(position);
	int barrierTiledGID = barrier->getTileGIDAt(ninjaTiledposition);//同TileGIDAt（）的区别

	if(barrierTiledGID>0){
		
	}
	else
		this->getChildByTag(001)->setPosition(position);
}
 Vec2 HelloWorld::tiledCoordFromPosition(Vec2 position)
{
	int x = position.x/tiledmap->getTileSize().width;
	int y = (tiledmap->getTileSize().height*tiledmap->getMapSize().height-position.y)/tiledmap->getTileSize().height;
	return Vec2(x,y);
}
 void HelloWorld::setViewCentrePoint(Vec2 position)
 {
	 auto visibleSize = Director::getInstance()->getVisibleSize();

	 int x = MAX(position.x, visibleSize.width/2);
	 int y = MAX(position.y, visibleSize.height/2);

	 x = MIN(x, (tiledmap->getMapSize().width * tiledmap->getTileSize().width) - visibleSize.width / 2);
	 y = MIN(x, (tiledmap->getMapSize().height * tiledmap->getTileSize().height) - visibleSize.height / 2);

	 Vec2 posA = Vec2(visibleSize.width/2,visibleSize.height/2);
	 Vec2 posB = Vec2(x, y);
	 Vec2 posC = posA - posB;
	 this->setPosition(posC);
 }

void HelloWorld::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

}

void HelloWorld::onExit()
{
	Layer::onExit();
}

void HelloWorld::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();	
}

void HelloWorld::cleanup()
{
	Layer::cleanup();
}
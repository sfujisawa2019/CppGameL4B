#include "HelloShaderScene.h"

#include "ShaderNode.h"

USING_NS_CC;

Scene* HelloShader::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloShader::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloShader::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloShader::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	//// position the label on the center of the screen
	//label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height));

	//// add the label as a child to this layer
	//this->addChild(label, 1);

	Sprite* sprite;

	Director::getInstance()->setClearColor(Color4F(0.0f, 0.0f, 0.0f, 0.0f));

	// Cocos�̃��S�X�v���C�g���쐬�B�`��D���0
	//sprite = Sprite::create("HelloWorld.png");
	//sprite->setColor(Color3B(0xff, 0x00, 0x00));
	//sprite->setScale(2.0f);
	//sprite->setPosition(Vec2(visibleSize.width/2 + origin.x + 200, visibleSize.height/2 + origin.y));
	//this->addChild(sprite, 0);

	// ShaderNode���쐬�B�`��D���1
	//node = ShaderNode::create();
	//node->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//node->setRotation(45);
	//node->setScale(5.0f);
	//node->setVisible(false);
	//node->setColor(Color3B(255, 255, 0));
	//node->setOpacity(128);
	//node->setContentSize(Size(500, 500));
	//this->addChild(node, 1);

	m_pSprite3D = Sprite3D::create("orc/orc.c3t");
	m_pSprite3D->setPosition(640, 360);
	this->addChild(m_pSprite3D);

	m_pSprite3D->setScale(10.0f);
	m_pSprite3D->setRotation3D(Vec3(0, 180, 0));
	//m_pSprite3D->setRotation(50);

	Animation3D* animation = Animation3D::create("orc/orc.c3t");
	Animate3D* animate = Animate3D::create(animation);
	RepeatForever* repeat = RepeatForever::create(animate);
	m_pSprite3D->runAction(repeat);

	//// ShaderNode�ɃA�N�V������������
	//RotateBy* action = RotateBy::create(10, 360 * 10);
	//node->runAction(action);

	//// LayerColor�̎g�p��
	//LayerColor* layerColor = LayerColor::create(Color4B(255, 255, 0, 255), 600, 600);
	//this->addChild(layerColor, 2);

	//Sprite* spriteA = Sprite::create("ShaderNode.png");
	//Sprite* spriteB;
	//Sprite* spriteC;

	//// layer��SpriteA,B,C���Ԃ牺����
	//scene->addChild(spriteA, 2);
	//scene->addChild(spriteB, 0);
	//scene->addChild(spriteC, 1);

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloShader::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloShader::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloShader::onTouchEnded, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void HelloShader::menuCloseCallback(Ref* pSender)
{
	// ���݂̃A�N�V�������~����
	m_pSprite3D->stopAllActions();

	// �A�j���[�V�������J�n
	Animation3D* animation = Animation3D::create("orc/orc_jump.c3t");
	Animate3D* animate = Animate3D::create(animation);
	//RepeatForever* repeat = RepeatForever::create(animate);
	m_pSprite3D->runAction(animate);

	//Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool HelloShader::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	m_pSprite3D->setPosition(touch->getLocation());

	return true;
}

void HelloShader::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	//node->setPosition(touch->getLocation());
}

void HelloShader::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
}

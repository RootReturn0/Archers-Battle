#include "MapChose.h"
#include "Start.h"

USING_NS_CC;

extern bool language_flag;   //true->English   false->Chinese
extern char *FontToUTF8(const char* font);
//it is define in another .cpp file 
//and it is used to change character

Scene* MapChose::createScene()
{
	return MapChose::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapChose.cpp\n");
}

// on "init" you need to initialize your instance
bool MapChose::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	ScenePrinter();

	return true;
}

void MapChose::ScenePrinter()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	float x = rect.origin.x + rect.size.width / 2;
	float y = rect.origin.y + rect.size.height / 2;

	///////////////////////////////////////////
	//add Setting_Background

	x = rect.origin.x + rect.size.width / 2;
	y = rect.origin.y + rect.size.height / 2;
	auto *background = Sprite::create("Help_Background.png");
	background->setPosition(Vec2(x, y));
	this->addChild(background);

	///////////////////////////////////
	//a return button which click to back to HelloWorldScene
	auto *return_button = MenuItemImage::create(
		"backtoupper.png",
		"backtoupper_select.png",
		CC_CALLBACK_1(MapChose::menuStartScene, this));

	auto *preturn = Menu::create(return_button, NULL);
	x = rect.origin.x + rect.size.width*(10.0f / 11.0f);
	y = rect.origin.y + rect.size.height*(1.0f / 10.0f);
	preturn->setPosition(Vec2(x, y));
	preturn->setScale(1.0f);
	this->addChild(preturn);
	//////////////////////////////////////
	//add two tiledmap sceneshot
	auto pre_map1 = Sprite::create("pre_map.png");
	x = rect.origin.x + rect.size.width*(1.0f / 4.0f);
	y = rect.origin.y + rect.size.height*(1.0f / 2.0f);
	pre_map1->setPosition(Vec2(x, y));
	this->addChild(pre_map1);

	auto pre_map2 = Sprite::create("pre_map.png");
	x = rect.origin.x + rect.size.width*(3.0f / 4.0f);
	pre_map2->setPosition(Vec2(x, y));
	this->addChild(pre_map2);



	//��ըЧ��*/
	/*CCParticleSystem* particleSystem = CCParticleExplosion::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.jpg"));
	addChild(particleSystem);*/
	//����Ч��  
	/*CCParticleSystem* particleSystem = CCParticleFire::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.jpg"));
	addChild(particleSystem);*/
	//�̻�Ч��  
	/*CCParticleSystem* particleSystem = CCParticleFireworks::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.jpg"));
	addChild(particleSystem);*/
	//��ϵЧ��  
	/*CCParticleSystem* particleSystem = CCParticleGalaxy::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.jpg"));
	addChild(particleSystem);*/
	//����Ч��  
	/*CCParticleSystem* particleSystem = CCParticleRain::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.jpg"));
	addChild(particleSystem);*/
	//��ѩЧ��  
	/*CCParticleSystem* particleSystem = CCParticleSnow::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("snow.jpg"));
	addChild(particleSystem);*/
	//����Ч��  ����Ƚ���
	/*CCParticleSystem* particleSystem = CCParticleSpiral::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.jpg"));
	addChild(particleSystem);*/

	/*CCSprite* sp = Sprite::create("fire.jpg");
	x = rect.origin.x + rect.size.width / 2;
	y = rect.origin.y + rect.size.height / 2;
	sp->setPosition(Vec2(x, y));
	auto gridNodeTarget = NodeGrid::create();
	this->addChild(gridNodeTarget);
	gridNodeTarget->addChild(sp);*/


	//3D�ζ�����Ч 
	/* CCActionInterval* shaky3D = CCShaky3D::create(5, CCSize(10, 10), 15, false);
	gridNodeTarget->runAction(shaky3D);*/


	//3D��ש�ζ���Ч 
	//    CCActionInterval* shakyTiles3D = CCShakyTiles3D::create(5, CCSize(10, 10), 5, false); 
	//    gridNodeTarget->runAction(shakyTiles3D); 


	//X�� 3D��ת��Ч 
	//    CCActionInterval* filpX = CCFlipX3D::create(5); 
	//    gridNodeTarget->runAction(filpX); 


	//ˮ������Ч 
	//    CCActionInterval* ripple = CCRipple3D::create(5, CCSize(10, 10), CCPointMake(240, 160), 240, 4, 160); 
	//    gridNodeTarget->runAction(ripple); 

	//Һ����Ч 
	//    CCActionInterval* liquid = CCLiquid::create(5, CCSize(10, 10), 4, 20); 
	//    gridNodeTarget->runAction(liquid); 

	//��שϴ����Ч   ���ɧ
	//    CCActionInterval* shuffle = CCShuffleTiles::create(5, CCSize(50, 50), 50); 
	//    gridNodeTarget->runAction(shuffle); 

	//�����Ч��,�����½ǵ����Ͻ�   ɧ*2
	/*CCActionInterval* fadeOutTRTiles = CCFadeOutTRTiles::create(5, CCSize(50, 50));
	gridNodeTarget->runAction(fadeOutTRTiles); */

	//�����Ч���������Ͻǵ����½� 
	//    CCActionInterval* fadeOutBLTiles  = CCFadeOutBLTiles::create(5, CCSize(50, 50)); 
	//    gridNodeTarget->runAction(fadeOutBLTiles); 

	//�۵�Ч�� ���µ��� 
	//    CCActionInterval* fadeOutUpTiles = CCFadeOutUpTiles::create(5, CCSize(10, 10)); 
	//    gridNodeTarget->runAction(fadeOutUpTiles); 


	//������ʧ��Ч 
	//    CCActionInterval* turnOffFiels = CCTurnOffTiles::create(4, CCSize(50, 50)); 
	//    gridNodeTarget->runAction(turnOffFiels); 

	//�����ķ�����Ч 
	//    CCActionInterval* jumpTiles = CCJumpTiles3D::create(5, CCSize(20, 20), 5, 20); 
	//    gridNodeTarget->runAction(jumpTiles); 

}
void MapChose::menuStartScene(Ref* pSender)
{
	auto sc = StartScene::createScene();        //���зָ������л�����
	auto reScene = TransitionSlideInR::create(1.0f, sc);  //���ұ�����Ķ���
	Director::getInstance()->replaceScene(reScene);
}

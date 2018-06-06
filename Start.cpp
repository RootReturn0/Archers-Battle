#include "Start.h"
#include "HelloWorldScene.h"
#include "TollgateScene.h"
#include "cstdlib"
#define MAP_SIZE 1600
#define MAP1_WIDTH 49
#define MAP1_HEIGHT 49
#define BACKGROUND_GID 19
#define GAP_GID 18
USING_NS_CC;

extern bool language_flag;  //true->English   false->Chinese
extern int is_paused;       //����is_paused�ľ��������� "HelloWorldScene.h"
extern char *FontToUTF8(const char* font);
//it is define in another .cpp file 
//and it is used to change character

Scene* StartScene::createScene()
{
	is_paused = reply_music;   //������ʽ��Ϸ��ɳ�ʼ������Ϊreply_music
	//��ʽ������Ϸ����л����µ���Ϸ���֣����ѻ�ӭ�����������Ϊstop
	//�ٴη��ص���ӭ�����ʱ��ش�ͷ��������
	//////////////////////////////////
	auto scene = StartScene::create();
	//auto layer = TollgateScene::createScene();
	//scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	MapPrinter();
	ScenePrinter();
	
	return true;
}

void StartScene::MapPrinter()
{
	size = Director::getInstance()->getVisibleSize();
	//�򿪵�һ����Ƭ��ͼ
	tiledmap = TMXTiledMap::create("ArcherBattle_TiledMap_1.tmx");
	this->addChild(tiledmap);

	//��meta����Ϊ���Բ�
	meta = tiledmap->layerNamed("meta");
	//meta->setVisible(false);
	//��ȡHP��MP�����
	HP_objects = tiledmap->getObjectGroup("HP");
	std::vector<Sprite*> sprite;
	//auto *sprite = Sprite::create("HP_tiledmap.png");

	for (auto&enemy : HP_objects->getObjects()) {
		// ��ȡ���������  
		ValueMap& dict = enemy.asValueMap();
		if (dict["HP"].asString() == "HP") { // �Զ������ԡ�Enemy��  
			float x = dict["x"].asFloat();     // x����  
			float y = dict["y"].asFloat();      // y����  
			sprite.push_back(Sprite::create("HP_tiledmap.png"));
			sprite[sprite.size()-1]->ignoreAnchorPointForPosition(false);
			sprite[sprite.size() - 1]->setAnchorPoint(Vec2(0.0f, 1.0f));
			sprite[sprite.size() - 1]->setPosition(Vec2(x, y));
			CCLOG("x = %f,y = %f", x, y);
			Size mapSize = tiledmap->getMapSize();      // ��ȡ��tiles����Ϊ��λ�ĵ�ͼ�ߴ�
			Size tileSize = tiledmap->getTileSize();    // ��ȡ�����ص�Ϊ��λ��tile�ߴ�����
			x = x / tileSize.width;
			y = (mapSize.height*tileSize.height - y) / tileSize.height;
			CCLOG("x = %f,y = %f", x, y);
			meta->setTileGID(GAP_GID, Vec2(x, y));
			
			tiledmap->addChild(sprite[sprite.size() - 1],100);
		}
	}
	
}

void StartScene::ScenePrinter()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	float x = rect.origin.x + rect.size.width / 2;
	float y = rect.origin.y + rect.size.height / 2;
	
	///////////////////////////////////
	//a return button which click to back to HelloWorldScene
	auto *return_button = MenuItemImage::create(
		"backtoupper.png",
		"backtoupper_select.png",
		CC_CALLBACK_1(StartScene::menuHellowWorldScene, this));

	auto *preturn = Menu::create(return_button, NULL);
	x = rect.origin.x + rect.size.width*(10.0f / 11.0f);
	y = rect.origin.y + rect.size.height*(1.0f / 10.0f);
	preturn->setPosition(Vec2(x, y));

	preturn->setScale(1.0f);
	this->addChild(preturn,100);   //�ѷ��ذ�ť����100�㣬��ֹ�ڵ�

	/*
	////////////////////////////////////////
	//add a cover to draw something
	auto *cover = CCLayerColor::create(ccc4(0, 0, 0, 150));  //cccv�ĵ��ĸ�����ȡֵ0~225��Խ��Խ��͸��
	this->addChild(cover, 1);
	////////////////////////////////////////
	//starting cortoon���뵭��
	auto *actionFade = CCFadeOut::create(3.0f);
	auto *actionFadeBack = actionFade->reverse();
	auto *sequence1 = CCSequence::create(actionFade, actionFadeBack, NULL);
	//starting cortoon ��ɫ�仯
	auto *actionTint = CCTintBy::create(2, -255, -127, -50);
	auto *actionTinback = actionTint->reverse();
	auto *sequence2 = CCSequence::create(actionTint, actionTint, NULL);
	//chose the sequence that you prefer
	cover->runAction(sequence2);*/
	
	sprite = Sprite::create("sprite.png");
	tiledmap->addChild(sprite, 10);
	
	sprite->setPosition(Vec2(80.0f, 80.0f));

	auto* pLeft = MenuItemImage::create("left.png", "left1.png", this, menu_selector(StartScene::left));
	auto* left = Menu::create(pLeft, NULL);
	x = rect.origin.x + rect.size.width*(2.0f / 32.0f);
	y = rect.origin.y + rect.size.height*(3.0f / 16.0f);
	left->setPosition(Vec2(x, y));
	this->addChild(left);

	auto* pUp = MenuItemImage::create("up.png", "up1.png", this, menu_selector(StartScene::up));
	auto* up = Menu::create(pUp, NULL);
	x = rect.origin.x + rect.size.width*(3.0f / 32.0f);
	y = rect.origin.y + rect.size.height*(1.0f / 4.0f);
	up->setPosition(Vec2(x, y));
	this->addChild(up);

	auto* pRight = MenuItemImage::create("right.png", "right1.png", this, menu_selector(StartScene::right));
	auto* right = Menu::create(pRight, NULL);
	x = rect.origin.x + rect.size.width*(4.0f / 32.0f);
	y = rect.origin.y + rect.size.height*(3.0f / 16.0f);
	right->setPosition(Vec2(x, y));
	this->addChild(right);

	auto* pDown = MenuItemImage::create("down.png", "down1.png", this, menu_selector(StartScene::down));
	auto* down = Menu::create(pDown, NULL);
	x = rect.origin.x + rect.size.width*(3.0f / 32.0f);
	y = rect.origin.y + rect.size.height*(1.0f / 8.0f);
	down->setPosition(Vec2(x, y));
	this->addChild(down);
	isCanReach(sprite->getPositionX(), sprite->getPositionY());

}
void StartScene::up(cocos2d::Object * pSender)
{

	float y = sprite->getPositionY();   //��Ϊ�������ߣ����Ի�ȡ��������ڵ�ͼ��y����
	if (y + 16<MAP_SIZE&&isCanReach(sprite->getPositionX(), y + 32))
	{	//������������Ǹ��ǵ�ͼ���ϱ߽�
		//֮������һ���С��һ��,����Ϊ�����ê��������,����һ�����±߽�ֻ��Ҫ�ټ�16
		sprite->setPositionY(y + 32);  //�Ѿ�����������һ���λ��
		if ((y + tiledmap->getPositionY() > size.height / 2) && ((MAP_SIZE - y)>size.height / 2))
		{ //������ͼ,ʹ���ﾡ������
			tiledmap->setPositionY(tiledmap->getPositionY() - 32);
		}
	}

}
void StartScene::right(cocos2d::Object * pSender)
{
	float x = sprite->getPositionX();
	if (x + 16<MAP_SIZE&&isCanReach(x + 32, sprite->getPositionY()))
	{
		sprite->setPositionX(x + 32);
		if ((x + tiledmap->getPositionX() > size.width / 2) && ((MAP_SIZE - x)>size.width / 2))
		{
			tiledmap->setPositionX(tiledmap->getPositionX() - 32);
		}
	}
}
void StartScene::left(cocos2d::Object * pSender)
{
	float x = sprite->getPositionX();
	if (x>16&&isCanReach(x - 32, sprite->getPositionY()))
	{
		sprite->setPositionX(x - 32);
		if ((x + tiledmap->getPositionX() < size.width / 2) && tiledmap->getPositionX() != 0)
		{
			tiledmap->setPositionX(tiledmap->getPositionX() + 32);
		}
	}
}
void StartScene::down(cocos2d::Object * pSender)
{
	float y = sprite->getPositionY();
	if (y > 16&&isCanReach(sprite->getPositionX(), y - 32))
	{
		sprite->setPositionY(y - 32);
		if ((y + tiledmap->getPositionY() < size.height / 2) && tiledmap->getPositionY() != 0)
		{
			tiledmap->setPositionY(tiledmap->getPositionY() + 32);
		}
	}
}
bool StartScene::isCanReach(float x, float y)
{
	bool result;
	int mapX = (int)((x - 16) / 32);        //��ȥ16�����������ê��������
	int mapY = (int)(49 - (y - 16) / 32);   //49ΪTiled���ͼ���������ֵ
	int tileGid = meta->tileGIDAt(Vec2(mapX, mapY)); //32��һ��Ĵ�С
	if (tileGid != GAP_GID)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}
void StartScene::menuHellowWorldScene(Ref* pSender)
{
	auto sc = HelloWorld::createScene();        //���Ž�����л�����
	auto reScene = TransitionShrinkGrow::create(1.0f, sc);
	Director::getInstance()->replaceScene(reScene);
}


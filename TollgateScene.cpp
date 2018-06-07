#include "TollgateScene.h"
#include <math.h>
#define k_w (EventKeyboard::KeyCode)119
#define k_a (EventKeyboard::KeyCode)97
#define k_s (EventKeyboard::KeyCode)115
#define k_d (EventKeyboard::KeyCode)100
#define ENNUMBER 20;

using namespace std;

Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();

	scene->addChild(layer);

	return scene;
}

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = CCDirector::getInstance()->getVisibleSize();

	m_player = Player::create();
	m_player->bindSprite(Sprite::create("player1.png"));
	m_player->setScale(0.5f);
	m_player->setPosition(Point(m_player->x_coord, m_player->y_coord));
	this->addChild(m_player);

	n_player = Player::create();
	n_player->bindSprite(Sprite::create("player2.png"));
	n_player->setScale(0.5f);
	n_player->setPosition(Point(n_player->x_coord, n_player->y_coord));
	this->addChild(n_player);

	plsum.push_back(m_player);
	plsum.push_back(n_player);

	this->scheduleUpdate();

	return true;
}
//��Ҳ��֪��onEnter��ʲô��˼ֻ�����ų��ģ�ֻ֪�������Ǽ����
void TollgateScene::onEnter()
{
	Layer::onEnter();

	auto keylistener = EventListenerKeyboard::create();
	//���̼����������������ƶ�
	keylistener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		keys[keyCode] = true;
	};

	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		keys[keyCode] = false;
	};

	EventDispatcher *eventDispatcher1 = Director::getInstance()->getEventDispatcher();
	eventDispatcher1->addEventListenerWithSceneGraphPriority(keylistener, this);


	auto touchlistener = EventListenerTouchOneByOne::create();
	//�������������������﹥��
	touchlistener->onTouchBegan = [&](Touch* touch, Event *event)
	{
		touchon = true;
		Point pos1 = touch->getLocationInView();
		Point pos2 = Director::getInstance()->convertToGL(pos1);
		pos = pos2;//�õ���������
		return true;
	};

	EventDispatcher *eventDispatcher2 = Director::getInstance()->getEventDispatcher();
	eventDispatcher2->addEventListenerWithSceneGraphPriority(touchlistener, this);

}

void TollgateScene::update(float delta)
{
	if (keys[k_w] || keys[k_a] || keys[k_s] || keys[k_d])//�ֱ���wasd���μ�#define
	{
		runEvent();
	}

	if (touchon)
	{
		attack();
		touchon = false;
	}
	//������¼���ͨ��ǰ���⼸�в�������ʹ����һ��ʱ������һ�Σ�bug���޸�

	vector<BulletBase*>::iterator it;
	for (it = bubsum.begin(); it != bubsum.end();)
	{
		if ((*it)->exist != true)
		{
			it = bubsum.erase(it);
			//			log("delete");
		}
		else it++;
	}
	for (auto bub : bubsum)
	{
		for (auto pl : plsum)
		{
			bub->collidePlayer(pl);
		}
	}


}
//�����ܶ��ĺ��������������Ϊ������һ�鲻����д�ġ�����ʱ���Ÿİ�
void TollgateScene::runEvent()
{
	m_player->run(m_player, keys);
}

void TollgateScene::attack()
{
	//   log("attack in x = %f  y = %f", pos.x, pos.y);
	auto Abullet = BulletBase::create();
	Abullet->bindSprite(Sprite::create("bullet.png"));
	Abullet->setPosition(Point(m_player->x_coord, m_player->y_coord));
	this->addChild(Abullet);

	Abullet->exist = true;
	bubsum.push_back(Abullet);

	Abullet->attacking(m_player, Abullet, pos);
}
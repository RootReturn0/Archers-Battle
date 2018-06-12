#include "Player.h"
#include "GamePlaying.h"
#define k_w (EventKeyboard::KeyCode)146
#define k_a (EventKeyboard::KeyCode)124
#define k_s (EventKeyboard::KeyCode)142
#define k_d (EventKeyboard::KeyCode)127
#define XIEBIAN 0.707

#define RETE (260.0/1599)  //smallplayer��player�ƶ�����ı�
extern bool smallmap_switch;       //С��ͼ���ƿ���,true->��С��ͼ,false->����С��ͼ
bool Player::init()
{

	return true;
}

//////////////////////////////////////////////////
void Player::runway1(std::map<EventKeyboard::KeyCode, bool>keys)
{
	float xchange = 0, ychange = 0;

	if (keys[k_w] && !keys[k_a] && !keys[k_s] && !keys[k_d])
	{
		ychange = speed;
		animationcreate(3);
	}
	else if (!keys[k_w] && keys[k_a] && !keys[k_s] && !keys[k_d])
	{
		xchange = -speed;
		animationcreate(1);
	}
	else if (!keys[k_w] && !keys[k_a] && keys[k_s] && !keys[k_d])
	{
		ychange = -speed;
		animationcreate(0);
	}
	else if (!keys[k_w] && !keys[k_a] && !keys[k_s] && keys[k_d])
	{
		xchange = speed;
		animationcreate(2);
	}
	else if (keys[k_w] && keys[k_a] && !keys[k_s] && !keys[k_d])
	{
		xchange = -XIEBIAN * speed; ychange = XIEBIAN * speed;
		animationcreate(3);
	}
	else if (keys[k_w] && !keys[k_a] && !keys[k_s] && keys[k_d])
	{
		xchange = XIEBIAN * speed; ychange = XIEBIAN * speed;
		animationcreate(3);
	}
	else if (!keys[k_w] && keys[k_a] && keys[k_s] && !keys[k_d])
	{
		xchange = -XIEBIAN * speed; ychange = -XIEBIAN * speed;
		animationcreate(0);
	}
	else if (!keys[k_w] && !keys[k_a] && keys[k_s] && keys[k_d])
	{
		xchange = XIEBIAN * speed; ychange = -XIEBIAN * speed;
		animationcreate(0);
	}
	x_coord += xchange;
	y_coord += ychange;

	//	log("x = %f  y = %f", x_coord, y_coord);
	this->setPosition(ccp(x_coord, y_coord));
}

void Player::runway2(Point point)
{
	float xchange, ychange;
	float distance = sqrt((point.x - x_coord)*(point.x - x_coord) + (point.y - y_coord)*(point.y - y_coord));
	xchange = (point.x - x_coord) / distance * speed;
	ychange = (point.y - y_coord) / distance * speed;

	x_coord += xchange;
	y_coord += ychange;

	if (ychange >= xchange && ychange >= -xchange)
		animationcreate(3);
	else if (ychange <= xchange && ychange <= -xchange)
		animationcreate(0);
	else if (ychange<xchange&&ychange>-xchange)
		animationcreate(2);
	else if (ychange>xchange&&ychange<-xchange)
		animationcreate(1);

	//log("x = %f  y = %f", x_coord, y_coord);
	this->setPosition(ccp(x_coord, y_coord));
}

void Player::hurt(int atk)
{
	p_hp -= atk;
	if (p_hp <= 0)
		die();
}

void Player::die()
{
	this->sprite->setAnchorPoint(Point(0.5, 0));
	this->setPosition(x_coord, y_coord - 35);

	auto * rotateto = RotateTo::create(0.3, 90);
	CCActionInterval * delaytime = CCDelayTime::create(1);

	auto callbackFunc = [&]()
	{
		restart();
	};
	CallFunc* callFunc = CallFunc::create(callbackFunc);

	Action* actions = Sequence::create(rotateto, delaytime, callFunc, NULL);

	this->runAction(actions);
}

void Player::restart()
{
	p_hp = 50;
	unbeat = 1;

	this->sprite->setAnchorPoint(Point(0.5, 0.5));
	x_coord = rand() % 600 + 100;
	y_coord = rand() % 300 + 100;
	this->setPosition(x_coord, y_coord);

	auto * rotateto = RotateTo::create(0, 0);
	Blink *blink = Blink::create(3, 6);

	auto callbackFunc = [&]()
	{
		unbeat = 0;
	};
	CallFunc* callFunc = CallFunc::create(callbackFunc);

	Action* actions = Sequence::create(rotateto, blink, callFunc, NULL);

	this->runAction(actions);
}

void Player::animationcreate(int direct)
{
	if (animating)
		return;
	animating = 1;
	/* ����ͼƬ֡������� */
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("player1run.plist", "player1run.png");

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	/* ��һ���б�������SpriteFrame���� */
	for (int i = 2 + direct * 5; i <= 5 + direct * 5; i++)
	{
		/* ��SpriteFrame������л�ȡSpriteFrame���� */
		frame = frameCache->getSpriteFrameByName(StringUtils::format("A%d.png", i));
		frameVec.pushBack(frame);
	}

	/* ʹ��SpriteFrame�б����������� */
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setDelayPerUnit(0.1f);

	/* ��������װ��һ������ */
	Animate* action = Animate::create(animation);

	auto callbackFunc = [&]()
	{
		animating = 0;
	};
	CallFunc* callFunc = CallFunc::create(callbackFunc);

	Action* actions = Sequence::create(action, callFunc, NULL);

	sprite->runAction(actions);
}
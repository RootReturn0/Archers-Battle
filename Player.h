#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;

class Player : public Entity {
public:
	CREATE_FUNC(Player);
	virtual bool init();

	//void run1(Player *player, std::map<EventKeyboard::KeyCode, bool>keys, Player *smallplayer);
	void runway1(std::map<EventKeyboard::KeyCode, bool>keys, Player *smallplayer);
	void runway2(Point point, Player *smallplayer);

	Size visibleSize = CCDirector::getInstance()->getVisibleSize();
	float x_coord = 80.0f;
	float y_coord = 80.0f;

	int level = 1;
	int exp = 0;

	void hpraise(int num);
	bool expraise(int num);
	int explimit();

	void hurt(int atk);
	Sprite *sprite;
	void animationcreate(int direct);

	bool unbeat = 0;

	//������
	//�����������
	int speed = 3;
	float radius = 30;
	float p_hp = 50.0;//��ǰѪ��
	int hpLimit = 50;//����Ѫ��
	float atkpower = 1.0;
	float atkrange = 1.0;
	float defpower = 1.0;
	//�ӵ�����
	int front = 1;
	int leftside = 0;
	int rightside = 0;
	int back = 0;
	//��������
	int weapon = 1;//1��2�ش�3��4����
				   //��Ѫ����������
	bool hpincrease = 0;
	bool expincrease = 0;

	bool ifcan_breakwall = false;//�ӵ��ܷ�ǽ
	
private:
	bool animating = 0;
	void die();
	void restart();//����
};

#endif
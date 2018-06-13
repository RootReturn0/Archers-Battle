#ifndef _BulletBase_H_
#define _BulletBase_H_

#include "Entity.h"
#include "Player.h"

class BulletBase :public Entity
{
public:
	BulletBase();
	~BulletBase();

	CREATE_FUNC(BulletBase);
	virtual bool init();

	BulletBase *create(Sprite *sprite);
	bool init(Sprite *sprite);

	int atkpower = 5;
	int flyspeed = 500;
	float range = 200;
	Player *comefrom;//�ӵ���Դ

	void attacking(Player *player, BulletBase *Abullet, Point pos);
	bool collidePlayer(Player *player);//�ж���ײ

	void pointChange(float dt);

	bool exist = false;//�ӵ�����

	void hide();
private:
	Point point;//�ӵ���ǰ����
	Point target;//Ԥ����������
	float xcs, ycs, rcs;//x y r��λʱ��ı���
	float flyrange;//�ѷ��о���
};

#endif
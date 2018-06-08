#ifndef _START_H_
#define _START_H_

#include "cocos2d.h"
#include "Player.h"
#include "BulletBase.h"
#include <windows.h>  
#include <vector>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)  
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)  
USING_NS_CC;
class StartScene : public Scene
{
public:
	Size size;
	Sprite* sprite;

	Size mapSize;
	Size tileSize;
	float x_move = 0.0;   //���ڵ�ͼ����֮���������λ������Ӧ����ֵת��
	float y_move = 0.0;
	TMXTiledMap* tiledmap;
	TMXLayer* meta;
	TMXObjectGroup* HP_objects;

	static std::vector<Sprite*> hp_potion;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuHellowWorldScene(Ref* pSender);

	void MapPrinter();
	void ScenePrinter();

	bool up(bool flag); //true��������Ҫ����runEvent����ʵʵ���ڵ��ƶ�
	bool right(bool flag);//false������ֻ�����ж���������ܲ����ߣ���ʵ�����ƶ�
	bool left(bool flag);
	bool down(bool flag);
	bool isCanReach(float x, float y);
	void HPjudge(const Vec2 &pos);

	// implement the "static create()" method manually
	CREATE_FUNC(StartScene);

	virtual void update(float delta);
	void onEnter();
	void runEvent();
	void attack();
private:
	Player * m_player;		//����1
	Player* n_player;       //����2����Ϊ�����У��еĻ�Ҳ���Լ�һ�ײ���ϵͳ���������¶�ս
	std::map<EventKeyboard::KeyCode, bool>keys;//��¼����״̬
	bool touchon = false;//�Ƿ񵥻�
	Point pos;//�������꣬���ڹ���
	std::vector<Player*>plsum;
	std::vector<BulletBase*>bubsum;
};

#endif //_START_H_
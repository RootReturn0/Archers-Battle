#ifndef __TollgateScene_H__
#define __TollgateScene_H__

#include "cocos2d.h"
#include "Player.h"
#include "BulletBase.h"
#include <windows.h>  
#include <vector>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)  
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)  

using namespace cocos2d;

class Player;
class TollgateScene : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);
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

#endif
#ifndef _GAMEPLAYING_H_
#define _GAMEPLAYING_H_

#include "cocos2d.h"
#include "Player.h"
#include "BulletBase.h"
#include "ProgressView.h"
#include <windows.h>  
#include <vector>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)  
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)  
USING_NS_CC;
struct HP_MESS
{
	Sprite* hp_potion;   //����ҩˮͼƬ�ľ���
	int savex, savey;  //�����µ��ߵ�λ�����ڼ���
	HP_MESS(Sprite* buf, int randx, int randy)
		:hp_potion(buf), savex(randx), savey(randy) {}
	//����==�����������Ļ�����std::find()����ʱ���bug
	//std::find()���ڲ�ʵ��Ӧ���ǽ�����==�����
	bool operator==(const HP_MESS &thv)
	{
		if(this->savex==thv.savex && this->savey==thv.savey)
		{
			return true;
		}
		else { return false; }
	}
};
struct EXP_MESS
{
	Sprite* exp_potion;   //����ҩˮͼƬ�ľ���
	int savex, savey;  //�����µ��ߵ�λ�����ڼ���
	EXP_MESS(Sprite* buf, int randx, int randy)
		:exp_potion(buf), savex(randx), savey(randy) {}
	bool operator==(const EXP_MESS &thv)
	{
		if (this->savex == thv.savex && this->savey == thv.savey)
		{
			return true;
		}
		else { return false; }
	}
};
class GamePlaying : public Scene
{
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();

private:
	Size size;
	Sprite* sprite;

	Size mapSize;
	Size tileSize;
	float x_move = 0.0;   //���ڵ�ͼ����֮���������λ������Ӧ����ֵת��
	float y_move = 0.0;
	TMXTiledMap* tiledmap;
	TMXLayer* meta;
	TMXLayer* HP_objects;

	static std::vector<HP_MESS> hp_auto_arise;
	static std::vector<EXP_MESS> exp_auto_arise;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuStartScene(Ref* pSender);

	void MapPrinter();
	void ScenePrinter();
	void MusicPrinter();
	void SmallmapPrinter();
	void ModePrinter();

	void Smallmap_Switch(Ref* pSender);
	void Mode_Switch(Ref* pSender);
	void Music_Switch(Ref* pSender);

	bool up(bool flag); //true��������Ҫ����runEvent����ʵʵ���ڵ��ƶ�
	bool right(bool flag);//false������ֻ�����ж���������ܲ����ߣ���ʵ�����ƶ�
	bool left(bool flag);
	bool down(bool flag);
	bool isCanReach(float x, float y);

	void HPjudge(const Vec2 &pos);
	void HP_grow(float dt);
	void EXPjudge(const Vec2 &pos);
	void EXP_grow(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(GamePlaying);

	virtual void update(float delta);
	void runEvent();
	void onEnter();
	void attack();

private:
	Player * m_player = Player::create();		//����1
	Player* n_player = Player::create();       //����2����Ϊ�����У��еĻ�Ҳ��
	std::map<EventKeyboard::KeyCode, bool>keys;//��¼����״̬
	bool touchon = false;//�Ƿ񵥻�
	Point pos;//�������꣬���ڹ���
	std::vector<Player*>plsum;
	std::vector<BulletBase*>bubsum;

	bool waytorun = false;  //true->�����ƶ���깥��

	Sprite *m_smallmap;
	//LayerColor *m_smallmap;
	Player *m_smallplayer;

	///////////////////////////////
	//Ѫ��
	ProgressView *m_pProgressView;
	ProgressView *n_pProgressView;
};

#endif //_GAMEPLAYING_H_
#pragma once

enum class HermitState
{
	WALK,
	WALK_CANNON,
	DEPLOY_CANNON,
	UNDEPLOY_CANNON,
	BULLETFIRE,
	CANNONFIRE,
	DESTROYED,

};
class Hermit : public GameObject
{
private:
	ObRect* col; //하체
	ObRect* colT; //상체
	ObImage* walk;
	ObImage* walk_cannon;
	ObImage* wave;
	ObImage* deploy_cannon;
	ObImage* undeploy_cannon;
	ObImage* bulletfire;
	ObImage* cannonfire;
	ObImage* destroyed;

	HermitState state;
	float animdelay;
	int hp;


public:
	Hermit();
	~Hermit();
	void Init();
	void Update();
	void Render();

	void Hit(int Damage) { hp -= Damage; };

	ObRect* GetPos() { return col; };
	ObRect* GetPosT() { return colT; };
	int GetHP() { return hp; }
	HermitState Getstate() { return state; };
	
};


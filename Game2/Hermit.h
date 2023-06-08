#pragma once

enum class HermitState
{
	WALK,
	WALK_CANNON,
	DEPLOY_CANNON,
	UNDEPLOY_CANNON
};
class Hermit : public GameObject
{
private:
	ObRect* col; //��ü
	ObRect* colT; //��ü
	ObImage* walk;
	ObImage* walk_cannon;
	ObImage* wave;
	ObImage* deploy_cannon;
	ObImage* undeploy_cannon;

	HermitState state;
	float animdelay;
	int hp;
public:
	Hermit();
	~Hermit();
	void Init();
	void Update();
	void Render();

	ObRect* GetPos() { return col; };
	
};


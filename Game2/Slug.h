#pragma once
#define BULLETMAX 50

enum class SlugState
{
	IDLE,
	DRIVE,
	JUMP,
	CROUCH,
	CROUCH_IDLE,
	CROUCH_DRIVE,
	SHOOTING,
	CROUCH_SHOOTING,
};


class Slug : public GameObject
{
private:
	ObRect* col;
	ObRect* colb;

	ObImage* idle;
	ObImage* drive;
	ObImage* jump;
	ObImage* shooting;
	ObImage* crouch;
	ObImage* crouch_idle;
	ObImage* crouch_drive;
	ObImage* crouch_shooting;
	
	ObImage* gun;
	class Bullet* bullet[BULLETMAX];
	ObImage* cannon;
	ObRect* cannoncol;
	
	int hp;
	int bomb;

	SlugState state;
	float gravity;
	float animdelay;
	float turndelay;
	float firedelay;
	float damagedelay;
	float shootingdelay;

public:
	

	Slug();
	~Slug();	
	void Init();
	void Update();	
	void Render();

	void Hit() ;
	void OnFloor();

	SlugState Getstate() { return state; };
	ObRect* GetPos() { return col; };
	ObRect* Getbottom() { return colb; };
	Bullet* Getbullet(int i) { return bullet[i]; };
	int GetHP() { return hp; };
};


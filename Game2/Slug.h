#pragma once

enum class SlugState
{
	IDLE,
	DRIVE,
	JUMP,
	CROUCH,
	CROUCH_IDLE,
	CROUCH_DRIVE,
};


class Slug : public GameObject
{
private:
	ObRect* col;
	ObImage* idle;
	ObImage* drive;
	ObImage* jump;
	ObImage* crouch;
	ObImage* crouch_idle;
	ObImage* crouch_drive;
	
	ObImage* gun;

	SlugState state;
	float gravity;
	float animdelay;
	float turndelay;

public:
	Slug();
	~Slug();	
	void Init();
	void Update();	
	void Render();

	bool Objectcol(GameObject* ob);
	void OnFloor();

	SlugState Getstate() { return state; };
	ObRect* GetPos() { return col; };
};

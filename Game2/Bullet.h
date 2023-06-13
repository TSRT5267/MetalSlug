#pragma once
class Bullet : public GameObject
{
private:
	ObImage* image;
	ObImage* effect;	
	ObRect* col;

	float life;
	bool isfire;
	Vector2 firedir;

public:
	Bullet();
	~Bullet();
	void Init();
	void Update();
	void Render();

	void Fire(ObImage* Gun);
	bool Getisfire() { return isfire; }
	ObRect* GetPos() { return col; };
	void Hit();
	
};

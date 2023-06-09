#pragma once
class Bullet : public GameObject
{
private:
	float life;
	bool isfire;


public:
	Bullet();
	~Bullet();
	void Init();
	void Update();
	void Render();

};


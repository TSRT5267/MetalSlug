#pragma once
#define SEAMAX 20

class Map
{
private:
	ObImage* sky;
	ObImage* sea1[SEAMAX];
	ObImage* sea2[SEAMAX];
	
	



	ObImage* time[2];
	ObImage* inven;
	ObImage* arms;
	ObImage* cannon[2];

	ObImage* hp;
	ObImage* score[8];



public:
	Map();
	~Map();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

public:
	void Settime(float T);
	void Setcannon(int C);
	void Sethp(int HP);
	void Setscore(int S);
};


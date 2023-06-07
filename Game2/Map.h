#pragma once
#define SEAMAX 15

class Map
{
private:
	ObImage* sky;
	ObImage* sea1[SEAMAX];
	ObImage* sea2[SEAMAX];
	

	ObImage* fish;
	ObRect* fishcol;


public:
	Map();
	~Map();
	void Init();
	void InitFish(Vector2 spwan);
	void Update();
	void LateUpdate();
	void Render();

public:
	ObRect* Getobjectcolfish() { return fishcol; };
	
};


#pragma once
#define SEAMAX 20

class Map
{
private:
	ObImage* sky;
	ObImage* sea1[SEAMAX];
	ObImage* sea2[SEAMAX];
	

	


public:
	Map();
	~Map();
	void Init();
	void InitFish(Vector2 spwan);
	void Update();
	void LateUpdate();
	void Render();

public:
	
	
};


#pragma once
class Ground
{
private:
	ObImage* ground;
public:
	ObRect* col;
	bool    active;

public:

	Ground();
	~Ground();

	void Init(Vector2 spwan, bool active);
	void Update();
	void Render();
	float GetPosX() { return col->GetWorldPos().x; }
};


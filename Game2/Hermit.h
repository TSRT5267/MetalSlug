#pragma once

enum class HermitState
{
	WALK,
	
};
class Hermit : public GameObject
{
private:
	ObRect* col;
	ObImage* walk;

	HermitState state;

public:
	Hermit();
	~Hermit();
	void Init();
	void Update();
	void Render();

	ObRect* GetPos() { return col; };
	
};

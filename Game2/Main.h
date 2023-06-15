#pragma once
#define GROUNDMAX 20
class Main : public Scene
{
private:
	
	class Slug* slug;
	class Hermit* hermit;
	class Map* map;
	class Ground* ground[GROUNDMAX];

	bool gamestart;
	bool gameover;
	int score;
	float time;

	float delay;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

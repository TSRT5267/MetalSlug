#pragma once
#define GROUNDMAX 20
class Main : public Scene
{
private:
	
	class Slug* slug;
	class Hermit* hermit;
	class Map* map;
	class Ground* ground[GROUNDMAX];

	float score;
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

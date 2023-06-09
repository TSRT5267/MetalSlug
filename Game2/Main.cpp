#include "stdafx.h"
#include "Main.h"
#include "Slug.h"
#include "Map.h"
#include "Ground.h"
#include "Hermit.h"

Main::Main()
{
	slug = new Slug();
	map = new Map();
	hermit = new Hermit();
	for (int i = 0; i < GROUNDMAX; i++)
	{
		ground[i] = new Ground();

	}
}

Main::~Main()
{	
	delete slug;
	delete map;
	delete hermit;
}

void Main::Init()
{	
	slug->Init();
	hermit->Init();
	map->Init();
	for (int i = 0; i < GROUNDMAX; i++)
	{
		ground[i]->Init(Vector2(-1280.0 + 128.0f * i, -200.0f), true);
	}
}

void Main::Release()
{
}

void Main::Update()
{
	//ImGui::Text("test: %f\n", cosf(180.0f*ToRadian));

	if (INPUT->KeyPress(VK_RIGHT))
	{
		slug->GetPos()->MoveWorldPos(RIGHT * 300.0f * DELTA);
		//CAM->position += RIGHT * 300.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_LEFT))
	{
		slug->GetPos()->MoveWorldPos(LEFT * 300.0f * DELTA);
		//CAM->position += LEFT * 300.0f * DELTA;
	}

	CAM->position += RIGHT * 100.0f * DELTA;

	map->Update();
	slug->Update();
	hermit->Update();
	for (int i = 0; i < GROUNDMAX; i++)
	{
		ground[i]->Update();
	}

	score += 10 * DELTA;
	ImGui::Text("SCORE: %f\n", score);
	ImGui::Text("\n");
	
}

void Main::LateUpdate()
{	
	//점수 초기화
	
	if (slug->GetPos()->GetWorldPos().y<-400.0f)
	{
		slug->OnFloor();
		for (int i = 0; i < GROUNDMAX; i++)
		{
			ground[i]->active = true;
		}
		score = 0;
	}
		
	
	
	for (int i = 0; i < GROUNDMAX; i++)
	{
		//바닥이 화면 밖으로 벗어났을때 스폰
		if (CAM->position.x - ground[i]->GetPosX() > 800.0f)
		{
			ground[i]->Init(Vector2(ground[i]->GetPosX() + 1536.0f, -200.0f),
			RANDOM->Int(0, 5));
		}
		// 충돌 (슬러그)
		if (ground[i]->active)
		{
			if (ground[i]->col->Intersect(slug->GetPos()))
			{
				slug->OnFloor();
				slug->color = Vector4(1, 1, 1, 1);
			}
		}
		// 충돌 (허밋)
		if (ground[i]->active)
		{
			if (ground[i]->col->Intersect(hermit->GetPos()))
			{
				ground[i]->active = false;
				
			}
		}
	}

	map->LateUpdate();
}

void Main::Render()
{
	map->Render();
	for (int i = 0; i < GROUNDMAX; i++)
	{
		ground[i]->Render();
	}
	slug->Render();
	hermit->Render();
	
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command){
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1280.0f, 640.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}
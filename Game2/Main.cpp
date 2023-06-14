#include "stdafx.h"
#include "Main.h"
#include "Slug.h"
#include "Map.h"
#include "Ground.h"
#include "Hermit.h"
#include "Bullet.h"

Main::Main()
{
	time = 60;

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
	for (int i = 0; i < GROUNDMAX; i++)
	{
		delete ground[i];
	}
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
	ImGui::Text("hermitHP: %i\n",hermit->GetHP() );
	ImGui::Text("hermitstate: %i\n", hermit->Getstate() );
	ImGui::Text("hp: %i\n", slug->GetHP() );

	time -= DELTA*0.5f;
	
	//게임끝 조건
	if (hermit->GetHP() <= 0 or slug->GetHP() <=0) gameover = true;

	if (not gameover)
	{
		hermit->GetPos()->MoveWorldPos(RIGHT * 100 * DELTA);
		CAM->position = hermit->GetPos()->GetWorldPos() + Vector2(480, 280);
	}

	map->Update();
	slug->Update();
	hermit->Update();
	for (int i = 0; i < GROUNDMAX; i++)
	{
		ground[i]->Update();
	}

	
}

void Main::LateUpdate()
{	
	
	


	//떨어짐
	if (slug->GetPos()->GetWorldPos().y<-400.0f)
	{
		slug->OnFloor();
		slug->Hit();
		for (int i = 0; i < GROUNDMAX; i++)
		{
			ground[i]->active = true;
		}
	}
		
	
	//바닥
	for (int i = 0; i < GROUNDMAX; i++)
	{
		//바닥이 화면 밖으로 벗어났을때 스폰
		if (CAM->position.x - ground[i]->GetPosX() > 800.0f)
		{
			ground[i]->Init(Vector2(ground[i]->GetPosX() + 1536.0f, -200.0f),true);
		}
		
		if (ground[i]->active)
		{
			// 충돌 (슬러그)
			if (ground[i]->col->Intersect(slug->Getbottom()))
			{
				slug->OnFloor();			
				//slug->color = Vector4(1, 1, 1, 1);
			}
			// 충돌 (허밋)
			if (ground[i]->col->Intersect(hermit->GetPos()))
			{
				ground[i]->active = false;

			}
			//허밋불릿
			if (ground[i]->col->Intersect(hermit->Getbullet(0)))
			{
				hermit->Setisfire(0, false);
			}
			if (ground[i]->col->Intersect(hermit->Getbullet(1)))
			{
				hermit->Setisfire(1, false);
			}
			//허밋캐논
			if (ground[i]->col->Intersect(hermit->Getbullet(2)))
			{
				ground[i]->active = false;
			}
		}
		
	}
	
	//플레이어의 공격
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (slug->Getbullet(i)->Getisfire())
		{
			if (slug->Getbullet(i)->GetPos()->Intersect(hermit->GetPos())or
				slug->Getbullet(i)->GetPos()->Intersect(hermit->GetPosT()))
			{
				//총은 1데미지
				hermit->Hit(100);
				score += 100;
				slug->Getbullet(i)->Hit();
			}
		}		
	}

	//보스의 공격
	for (int i = 0;i < 3;i++)
	{
		if (hermit->Getbullet(i)->Intersect(slug->GetPos()))
		{
			//slug->GetPos()->color = Vector4(1, 0, 0, 1);
			slug->Hit();
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
	
	hermit->Render();
	slug->Render();
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
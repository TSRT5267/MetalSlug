#include "stdafx.h"
#include "Map.h"


Map::Map()
{

	//¹è°æ
	{
		sky = new ObImage(L"map/sky.gif");
		for (int i = 0;i < SEAMAX;i++)
		{
			sea1[i] = new ObImage(L"map/sea1.gif");
			sea2[i] = new ObImage(L"map/sea2.gif");
		}

		sky->scale.x = app.GetWidth();
		sky->scale.y = app.GetHeight();
		sky->imageSize.x *= 2.0f;
		sky->imageSize.y *= 2.0f;
		sky->SetWorldPos(Vector2(0.0f, 96.0f));

		for (int i = 0;i < SEAMAX;i++)
		{
			sea1[i]->scale.x = sea1[i]->imageSize.x * 2.0f / 8.0f;
			sea1[i]->scale.y = sea1[i]->imageSize.y * 2.0f;
			sea1[i]->imageSize.x *= 2.0f;
			sea1[i]->imageSize.y *= 2.0f;
			sea1[i]->maxFrame.x = 8;
			sea1[i]->pivot = OFFSET_B;
			sea1[i]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			sea1[i]->SetWorldPos(Vector2(0.0f, 16.0f));

			sea2[i]->scale.x = sea2[i]->imageSize.x * 2.0f / 8.0f;
			sea2[i]->scale.y = sea2[i]->imageSize.y * 2.0f;
			sea2[i]->imageSize.x *= 2.0f;
			sea2[i]->imageSize.y *= 2.0f;
			sea2[i]->maxFrame.x = 8;
			sea2[i]->pivot = OFFSET_B;
			sea2[i]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}

		

		sky->space = SPACE::SCREEN;
	}

	//ui
	{
		time[0] = new ObImage(L"map/time.gif");
		time[0]->scale.x = time[0]->imageSize.x * 2.0f / 10.0f;
		time[0]->scale.y = time[0]->imageSize.y * 2.0f;
		time[0]->maxFrame.x = 10;

		time[1] = new ObImage(L"map/time.gif");
		time[1]->scale.x = time[1]->imageSize.x * 2.0f / 10.0f;
		time[1]->scale.y = time[1]->imageSize.y * 2.0f;
		time[1]->maxFrame.x = 10;

		inven = new ObImage(L"map/inven.gif");
		inven->scale.x = inven->imageSize.x * 2.0f;
		inven->scale.y = inven->imageSize.y * 2.0f;

		arms = new ObImage(L"map/infinity.gif");
		arms->scale.x = arms->imageSize.x * 2.0f;
		arms->scale.y = arms->imageSize.y * 2.0f;

		cannon[0] = new ObImage(L"map/number.gif");
		cannon[0]->scale.x = cannon[0]->imageSize.x * 2.0f / 10.0f;
		cannon[0]->scale.y = cannon[0]->imageSize.y * 2.0f;
		cannon[0]->maxFrame.x = 10;

		cannon[1] = new ObImage(L"map/number.gif");
		cannon[1]->scale.x = cannon[1]->imageSize.x * 2.0f / 10.0f;
		cannon[1]->scale.y = cannon[1]->imageSize.y * 2.0f;
		cannon[1]->maxFrame.x = 10;

		hp = new ObImage(L"map/hp.gif");
		hp->scale.x = hp->imageSize.x * 2.0f / 9.0f;
		hp->scale.y = hp->imageSize.y * 2.0f;
		hp->maxFrame.x = 9;

		for (int i = 0;i < 8;i++)
		{
			score[i] = new ObImage(L"map/score.gif");
			score[i]->scale.x = score[i]->imageSize.x * 2.0f / 10.0f;
			score[i]->scale.y = score[i]->imageSize.y * 2.0f;
			score[i]->maxFrame.x = 10;
		}
	}
}

Map::~Map()
{
	delete sky;
	for (int i = 0;i < SEAMAX;i++)
	{
		delete sea1[i];
		delete sea2[i];
	}
	delete time[0];
	delete time[1];
	delete cannon[0];
	delete cannon[1];
	delete inven;
	delete arms;
	delete hp;
	for (int i = 0;i < 8;i++)
	{
		delete score[i];
	}

	TEXTURE->DeleteTexture(L"sky.gif");	
	TEXTURE->DeleteTexture(L"sea1.gif");	
	TEXTURE->DeleteTexture(L"sea2.gif");	
	
}

void Map::Init()
{	
	for (int i = 0; i < SEAMAX; i++)
	{
		sea1[i]->SetWorldPos(Vector2(-1400.0 + 288.0f * i, -288.0f));
		sea2[i]->SetWorldPos(Vector2(-1400.0 + 256.0f * i, -320.0f));



	}
}

void Map::Update()
{
	time[0]->SetWorldPos(CAM->position + Vector2(-18,280));
	time[1]->SetWorldPos(CAM->position + Vector2(18,280));
	cannon[0]->SetWorldPos(CAM->position + Vector2(-78,274));
	cannon[1]->SetWorldPos(CAM->position + Vector2(-62,274));
	inven->SetWorldPos(CAM->position + Vector2(-100, 280));
	arms->SetWorldPos(CAM->position + Vector2(-130, 274));
	hp->SetWorldPos(CAM->position + Vector2(-240, 270));
	for (int i = 0;i < 8;i++)
	{
		score[i]->SetWorldPos(CAM->position + Vector2(-180-i*16, 288));
	}


	sky->uv.x += DELTA * 50.0f / sky->imageSize.x;
	sky->uv.z += DELTA * 50.0f / sky->imageSize.x;

	for (int i = 0;i < SEAMAX;i++)
	{
		sea1[i]->uv.x += DELTA * 100.0f / sea1[i]->imageSize.x;
		sea1[i]->uv.z += DELTA * 100.0f / sea1[i]->imageSize.x;	
		sea2[i]->uv.x += DELTA * 100.0f / sea2[i]->imageSize.x;
		sea2[i]->uv.z += DELTA * 100.0f / sea2[i]->imageSize.x;
	}

	

	sky->Update();
	time[0]->Update();
	time[1]->Update();
	cannon[0]->Update();
	cannon[1]->Update();
	inven->Update();
	arms->Update();
	hp->Update();
	for (int i = 0;i < 8;i++)
	{
		 score[i]->Update();
	}
	
	for (int i = 0;i < SEAMAX;i++)
	{
		sea1[i]->Update();
		sea2[i]->Update();
	}
}

void Map::LateUpdate()
{
	for (int i = 0;i < SEAMAX;i++)
	{
		if (CAM->position.x - sea1[i]->GetWorldPos().x > 1200.0f)
		{
			sea1[i]->SetWorldPos(Vector2(sea1[i]->GetWorldPos().x+1856.0f , -288.0f));			
		}
		if (CAM->position.x - sea2[i]->GetWorldPos().x > 1200.0f)
		{			
			sea2[i]->SetWorldPos(Vector2(sea2[i]->GetWorldPos().x + 2112.0f, -320.0f));
		}
	}
		
}

void Map::Render()
{
	sky->Render();
	for (int i = 0;i < SEAMAX;i++)
	{
		sea1[i]->Render();
		sea2[i]->Render();
	}
	
	time[0]->Render();
	time[1]->Render();
	cannon[0]->Render();
	cannon[1]->Render();
	inven->Render();
	arms->Render();
	hp->Render();
	for (int i = 0;i < 8;i++)
	{
		score[i]->Render();
	}
	
}

void Map::Settime(float T)
{
	int ten = static_cast<int>(T) / 10;
	int one = static_cast<int>(T) % 10;

	time[0]->frame.x = ten;
	time[1]->frame.x = one;
}

void Map::Setcannon(int C)
{
	int ten = C / 10;
	int one = C % 10;

	cannon[0]->frame.x = ten;
	cannon[1]->frame.x = one;
}

void Map::Sethp(int HP)
{
	hp->frame.x = HP;
}

void Map::Setscore(int S)
{
	for (int i = 0;i < 8;i++)
	{
		score[i]->frame.x = S % 10;
		S /= 10;
	}
}



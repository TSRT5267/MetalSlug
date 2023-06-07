#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	sky = new ObImage(L"sky.gif");	
	for (int i = 0;i < SEAMAX;i++)
	{
		sea1[i] = new ObImage(L"sea1.gif");
		sea2[i] = new ObImage(L"sea2.gif");
	}
		
	fish = new ObImage(L"fish.gif");
	fishcol = new ObRect();
	

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

	fish->scale.x = fish->imageSize.x * 2.0f / 12.0f;
	fish->scale.y = fish->imageSize.y * 2.0f;
	fish->maxFrame.x = 12;
	fishcol = new ObRect();
	fishcol->scale = fish->scale;
	fishcol->isFilled = false;
	fish->SetParentRT(*fishcol);

	sky->space = SPACE::SCREEN;
	

	
}

Map::~Map()
{
	delete sky;
	for (int i = 0;i < SEAMAX;i++)
	{
		delete sea1[i];
		delete sea2[i];
	}
	delete fish;
	delete fishcol;

	TEXTURE->DeleteTexture(L"sky.gif");	
	TEXTURE->DeleteTexture(L"sea1.gif");	
	TEXTURE->DeleteTexture(L"sea2.gif");	
	TEXTURE->DeleteTexture(L"fish.gif");
}

void Map::Init()
{	
	for (int i = 0; i < SEAMAX; i++)
	{
		sea1[i]->SetWorldPos(Vector2(-1280.0 + 288.0f * i, -288.0f));
		sea2[i]->SetWorldPos(Vector2(-1280.0 + 256.0f * i, -320.0f));
	}

	fishcol->SetWorldPos(Vector2(700.0f, -70.0f));
	fish->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

}

void Map::InitFish(Vector2 spwan)
{
	fishcol->SetWorldPos(spwan);
}

void Map::Update()
{
	//¸ÊÀÌµ¿
	/*if (INPUT->KeyPress(VK_RIGHT))
	{
		for (int i = 0;i < SEAMAX;i++)
		{
			sea2[i]->uv.x += DELTA * 300.0f / sea2[i]->imageSize.x;
			sea2[i]->uv.z += DELTA * 300.0f / sea2[i]->imageSize.x;
		}
	}
	else if (INPUT->KeyPress(VK_LEFT))
	{
		for (int i = 0;i < SEAMAX;i++)
		{
			sea2[i]->uv.x -= DELTA * 300.0f / sea2[i]->imageSize.x;
			sea2[i]->uv.z -= DELTA * 300.0f / sea2[i]->imageSize.x;
		}
	}*/
	

	sky->uv.x += DELTA * 50.0f / sky->imageSize.x;
	sky->uv.z += DELTA * 50.0f / sky->imageSize.x;

	for (int i = 0;i < SEAMAX;i++)
	{
		sea1[i]->uv.x += DELTA * 100.0f / sea1[i]->imageSize.x;
		sea1[i]->uv.z += DELTA * 100.0f / sea1[i]->imageSize.x;		
	}

	fishcol->MoveWorldPos(Vector2(LEFT * DELTA * 300.0f));

	sky->Update();
	
	fish->Update();
	fishcol->Update();
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
		if (CAM->position.x - sea1[i]->GetWorldPos().x > 800.0f)
		{
			sea1[i]->SetWorldPos(Vector2(sea1[i]->GetWorldPos().x+1856.0f , -288.0f));			
		}
		if (CAM->position.x - sea2[i]->GetWorldPos().x > 800.0f)
		{			
			sea2[i]->SetWorldPos(Vector2(sea2[i]->GetWorldPos().x + 1792.0f, -320.0f));
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
	
	

	fish->Render();
	fishcol->Render();
}



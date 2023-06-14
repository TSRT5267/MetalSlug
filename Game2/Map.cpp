#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	sky = new ObImage(L"map/sky.gif");	
	for (int i = 0;i < SEAMAX;i++)
	{
		sea1[i] = new ObImage(L"map/sea1.gif");
		sea2[i] = new ObImage(L"map/sea2.gif");
	}

	time[0] = new ObImage(L"map/time.gif");
	time[0]->scale.x = time[0]->imageSize.x * 2.0f / 10.0f;
	time[0]->scale.y = time[0]->imageSize.y * 2.0f ;
	time[0]->maxFrame.x = 10;
	

	time[1] = new ObImage(L"map/time.gif");
	time[1]->scale.x = time[1]->imageSize.x * 2.0f / 10.0f;
	time[1]->scale.y = time[1]->imageSize.y * 2.0f;
	time[1]->maxFrame.x = 10;
	

	inven = new ObImage(L"map/inven.gif");
	inven->scale.x = inven->imageSize.x * 2.0f;
	inven->scale.y = inven->imageSize.y * 2.0f;
	
	



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
	delete inven;

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

void Map::InitFish(Vector2 spwan)
{
	
}

void Map::Update()
{
	time[0]->SetWorldPos(CAM->position + Vector2(-20,280));
	time[1]->SetWorldPos(CAM->position + Vector2(20,280));
	inven->SetWorldPos(CAM->position + Vector2(-150, 280));

	sky->uv.x += DELTA * 50.0f / sky->imageSize.x;
	sky->uv.z += DELTA * 50.0f / sky->imageSize.x;

	for (int i = 0;i < SEAMAX;i++)
	{
		sea1[i]->uv.x += DELTA * 100.0f / sea1[i]->imageSize.x;
		sea1[i]->uv.z += DELTA * 100.0f / sea1[i]->imageSize.x;		
	}

	

	sky->Update();
	time[0]->Update();
	time[1]->Update();
	inven->Update();

	
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
	
	time[0]->Render();
	time[1]->Render();
	inven->Render();

	
}



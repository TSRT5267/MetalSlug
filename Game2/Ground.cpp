#include "stdafx.h"
#include "Ground.h"

Ground::Ground()
{
	ground = new ObImage(L"ground.gif");
	ground->scale.x = ground->imageSize.x*2.0f;
	ground->scale.y = ground->imageSize.y*2.0f;
	ground->pivot = OFFSET_LT;
	ground->SetLocalPosY(20.0f);


	col = new ObRect();
	col->scale = ground->scale;
	col->scale.y = 5.0f;


	col->isFilled = false;
	col->pivot = OFFSET_LT;
	//col->hasAxis = true;
	col->color.x = 1.0f;
	col->color.y = 1.0f;
	col->color.z = 1.0f;
	col->SetWorldPosY(-200.0f);

	ground->SetParentRT(*col);
}

Ground::~Ground()
{
	delete ground;
	delete col;	
	TEXTURE->DeleteTexture(L"ground.gif");
}

void Ground::Init(Vector2 spwan, bool active)
{
	col->SetWorldPos(spwan);
	this->active = active;
}

void Ground::Update()
{
	ground->Update();
	col->Update();
}

void Ground::Render()
{
	if (not active) return;

	ground->Render();
	col->Render();
}

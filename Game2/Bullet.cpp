#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	image = new ObImage(L"slug/bullet.gif");
	image->scale.x = image->imageSize.x * 2.0f / 17.0f;
	image->scale.y = image->imageSize.y * 2.0f;
	image->maxFrame.x = 17;
	pivot = OFFSET_R;

	col = new ObRect();
	col->scale = image->scale;
	col->isFilled = false;

	isfire = false;

	image->SetParentRT(*col);
}

Bullet::~Bullet()
{
	delete image;
	delete col;
	TEXTURE->DeleteTexture(L"slug/bullet.gif.gif");
}

void Bullet::Init()
{
}

void Bullet::Update()
{
	if (not isfire) return;


	life -= DELTA;
	if (life == 0) isfire = false;



	col->MoveWorldPos(GetRight() * DELTA * 200);
	image->Update();
	col->Update();
}

void Bullet::Render()
{
	image->Render();
	col->Render();
}

void Bullet::Fire(ObImage* Gun)
{
	isfire = true;
	life = 3.0f;
	col->SetWorldPos(Gun->GetWorldPos());
	col->rotation.z = 180.0f - 180.0f / Gun->frame.x;
	col->SetWorldPos(col->GetRight() * 60.0f);	
}

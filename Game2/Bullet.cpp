#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	image = new ObImage(L"slug/bullet.gif");
	image->scale.x = image->imageSize.x * 1.0f / 17.0f;
	image->scale.y = image->imageSize.y * 1.0f;
	image->maxFrame.x = 17;
	pivot = OFFSET_R;

	col = new ObRect();
	col->scale = image->scale;
	col->isFilled = false;
	col->SetWorldPos(Vector2(0, 1000));
	isfire = false;
	life = 0.0f;

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


	col->MoveWorldPos(firedir * DELTA * 1000);
	image->Update();
	col->Update();

	life -= DELTA;
	if (life < 0) isfire = false;
}

void Bullet::Render()
{
	if (not isfire) return;
	image->Render();
	col->Render();
}

void Bullet::Fire(ObImage* Gun)
{
	isfire = true;
	life = 2.0f;
	float dig = (180.0f - 180.0f / 17.0f * Gun->frame.x) * ToRadian;
	firedir = Vector2(cosf(dig),sinf(dig));	
	col->SetWorldPos(Gun->GetWorldPos()+firedir*60);
	
	image->frame.x = Gun->frame.x;
	
	

	
	
}



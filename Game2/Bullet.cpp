#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	image = new ObImage(L"slug/bullet.gif");
	image->scale.x = image->imageSize.x * 1.0f / 17.0f;
	image->scale.y = image->imageSize.y * 1.0f;
	image->maxFrame.x = 17;

	effect = new ObImage(L"slug/bulletEF.gif");
	effect->scale.x = effect->imageSize.x * 2.5f / 11.0f;
	effect->scale.y = effect->imageSize.y * 2.5f;
	effect->maxFrame.x = 11;

	col = new ObRect();
	col->scale = image->scale;
	col->scale -= Vector2(30, 30);
	col->isFilled = false;
	col->SetWorldPos(Vector2(0, 1000));
	col->color = Vector4(0, 0, 0, 0);
	isfire = false;
	ishit = false;
	life = 0.0f;

	image->SetParentRT(*col);
	effect->SetParentRT(*col);
}

Bullet::~Bullet()
{
	delete image;
	delete effect;
	delete col;
	TEXTURE->DeleteTexture(L"slug/bullet.gif.gif");
	TEXTURE->DeleteTexture(L"slug/bulletEF.gif.gif");
}

void Bullet::Init()
{
}

void Bullet::Update()
{

	if (ishit) effect->Update();
	if (effect->frame.x == 10) ishit = false;
	if (not isfire) return;


	col->MoveWorldPos(firedir * DELTA * 800);
	image->Update();
	col->Update();

	life -= DELTA;
	if (life < 0) isfire = false;

}

void Bullet::Render()
{
	if (ishit) effect->Render();
	if (not isfire) return;
	image->Render();
	col->Render();
}

void Bullet::Fire(ObImage* Gun)
{
	isfire = true;
	life = 5.0f;
	float dig = (180.0f - 180.0f / 16.0f * Gun->frame.x) * ToRadian;
	firedir = Vector2(cosf(dig),sinf(dig));	
	col->SetWorldPos(Gun->GetWorldPos()+firedir*60);
	
	image->frame.x = Gun->frame.x;

}

void Bullet::Hit()
{
	ishit = true;
	effect->frame.x = 0;
	effect->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
	isfire = false;
}





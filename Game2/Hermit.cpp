#include "stdafx.h"
#include "Hermit.h"

Hermit::Hermit()
{
	hp = 600;

	//이미지
	{
		walk = new ObImage(L"hermit/walk.gif");
		walk->scale.x = walk->imageSize.x * 2.0f / 12.0f;
		walk->scale.y = walk->imageSize.y * 2.0f;
		walk->maxFrame.x = 12;
		walk->pivot = OFFSET_B;

		walk_cannon = new ObImage(L"hermit/walk_cannon.gif");
		walk_cannon->scale.x = walk_cannon->imageSize.x * 2.0f / 12.0f;
		walk_cannon->scale.y = walk_cannon->imageSize.y * 2.0f;
		walk_cannon->maxFrame.x = 12;
		walk_cannon->pivot = OFFSET_B;

		deploy_cannon = new ObImage(L"hermit/deploy_cannon.gif");
		deploy_cannon->scale.x = deploy_cannon->imageSize.x * 2.0f / 12.0f;
		deploy_cannon->scale.y = deploy_cannon->imageSize.y * 2.0f;
		deploy_cannon->maxFrame.x = 12;
		deploy_cannon->pivot = OFFSET_B;

		undeploy_cannon = new ObImage(L"hermit/undeploy_cannon.gif");
		undeploy_cannon->scale.x = undeploy_cannon->imageSize.x * 2.0f / 12.0f;
		undeploy_cannon->scale.y = undeploy_cannon->imageSize.y * 2.0f;
		undeploy_cannon->maxFrame.x = 12;
		undeploy_cannon->pivot = OFFSET_B;

		bulletfire = new ObImage(L"hermit/bulletfire.gif");
		bulletfire->scale.x = bulletfire->imageSize.x * 2.0f / 12.0f;
		bulletfire->scale.y = bulletfire->imageSize.y * 2.0f;
		bulletfire->maxFrame.x = 12;
		bulletfire->pivot = OFFSET_B;

		cannonfire = new ObImage(L"hermit/cannonfire.gif");
		cannonfire->scale.x = cannonfire->imageSize.x * 2.0f / 12.0f;
		cannonfire->scale.y = cannonfire->imageSize.y * 2.0f;
		cannonfire->maxFrame.x = 12;
		cannonfire->pivot = OFFSET_B;

		destroyed = new ObImage(L"hermit/destroyed.gif");
		destroyed->scale.x = destroyed->imageSize.x * 2.0f / 12.0f;
		destroyed->scale.y = destroyed->imageSize.y * 2.0f;
		destroyed->maxFrame.x = 12;
		destroyed->pivot = OFFSET_B;

		wave = new ObImage(L"hermit/wave.gif");
		wave->scale.x = wave->imageSize.x * 2.0f / 12.0f;
		wave->scale.y = wave->imageSize.y * 2.0f;
		wave->maxFrame.x = 12;
		wave->SetLocalPos(Vector2(80, -40));
		wave->pivot = OFFSET_B;
	}

	col = new ObRect();
	col->scale = walk->scale;
	col->scale.x -= 200;
	col->scale.y -= 210;
	col->isFilled = false;
	col->pivot = OFFSET_B;

	colT = new ObRect();
	colT->scale = col->scale;
	colT->scale.x -= 100;
	colT->scale.y -= 20;
	colT->SetLocalPos(Vector2(-70, 190));
	colT->isFilled = false;
	colT->pivot = OFFSET_B;

	walk->SetParentRT(*col);
	wave->SetParentRT(*col);
	walk_cannon->SetParentRT(*col);
	deploy_cannon->SetParentRT(*col);
	undeploy_cannon->SetParentRT(*col);
	bulletfire->SetParentRT(*col);
	cannonfire->SetParentRT(*col);
	destroyed->SetParentRT(*col);
	colT->SetParentRT(*col);
}

Hermit::~Hermit()
{
	delete walk;
	delete wave;
	delete walk_cannon;
	delete deploy_cannon;
	delete undeploy_cannon;
	delete bulletfire;
	delete cannonfire;
	delete destroyed;

	TEXTURE->DeleteTexture(L"hermit/walk.gif");
	TEXTURE->DeleteTexture(L"hermit/walk_cannon.gif");
	TEXTURE->DeleteTexture(L"hermit/deploy_cannon.gif");
	TEXTURE->DeleteTexture(L"hermit/undeploy_cannon.gif");
	TEXTURE->DeleteTexture(L"hermit/bulletfire.gif");
	TEXTURE->DeleteTexture(L"hermit/cannonfire.gif");
	TEXTURE->DeleteTexture(L"hermit/destroyed.gif");
	TEXTURE->DeleteTexture(L"hermit/wave.gif");
}

void Hermit::Init()
{
	col->SetWorldPos(Vector2(-480.0f, -280.0f));
	state = HermitState::WALK;
	walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	wave->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}

void Hermit::Update()
{
	//WALK로 시작
	if (state == HermitState::WALK)
	{

		if (walk->frame.x == 11 and hp < 300)
		{
			walk->frame.x = 0;
			state = HermitState::DEPLOY_CANNON;
			deploy_cannon->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
		if (walk->frame.x==11 and hp<590)
		{
			walk->frame.x = 0;
			state = HermitState::BULLETFIRE;
			bulletfire->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
		
	}
	else if (state == HermitState::WALK_CANNON)
	{
		
		if (walk_cannon->frame.x==11 and hp<0)
		{
			walk_cannon->frame.x = 0;
			state = HermitState::DESTROYED;
			destroyed->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
		if (walk_cannon->frame.x == 11 )
		{
			walk_cannon->frame.x = 0;
			state = HermitState::CANNONFIRE;
			cannonfire->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
		
	}
	else if (state == HermitState::DEPLOY_CANNON)
	{
		if (deploy_cannon->frame.x==11)
		{
			deploy_cannon->frame.x = 0;
			state = HermitState::WALK_CANNON;
			walk_cannon->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	else if (state == HermitState::UNDEPLOY_CANNON)
	{
		if (TIMER->GetTick(animdelay, 1.2f))
		{
			state = HermitState::WALK;
			walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	else if (state == HermitState::CANNONFIRE)
	{
		
		
		if (cannonfire->frame.x == 11 )
		{
			cannonfire->frame.x = 0;
			state = HermitState::WALK_CANNON;
			walk_cannon->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}

	}
	else if (state == HermitState::BULLETFIRE)
	{
		
		
		if ( bulletfire->frame.x==11)
		{
			bulletfire->frame.x = 0;
			state = HermitState::WALK;
			walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	else if (state == HermitState::DESTROYED)
	{


		
	}


	//col->MoveWorldPos(RIGHT * 100 * DELTA);

	col->Update();
	colT->Update();
	walk->Update();
	wave->Update();
	walk_cannon->Update();
	deploy_cannon->Update();
	undeploy_cannon->Update();
	bulletfire->Update();
	cannonfire->Update();
	destroyed->Update();
}

void Hermit::Render()
{
	col->Render();
	colT->Render();

	switch (state)
	{
	case HermitState::WALK:
		walk->Render();
		break;
	case HermitState::WALK_CANNON:
		walk_cannon->Render();
		break;
	case HermitState::DEPLOY_CANNON:
		deploy_cannon->Render();
		break;
	case HermitState::UNDEPLOY_CANNON:
		undeploy_cannon->Render();
		break;
	case HermitState::BULLETFIRE:
		bulletfire->Render();
		break;
	case HermitState::CANNONFIRE:
		cannonfire->Render();
		break;
	case HermitState::DESTROYED:
		destroyed->Render();
		break;
	}

	wave->Render();
}


#include "stdafx.h"
#include "Hermit.h"

Hermit::Hermit()
{
	walk = new ObImage(L"Walk.gif");
	walk->scale.x = walk->imageSize.x * 2.0f / 12.0f;
	walk->scale.y = walk->imageSize.y * 2.0f;
	walk->maxFrame.x = 12;
	walk->pivot = OFFSET_LB;

	wave = new ObImage(L"wave.gif");
	wave->scale.x = wave->imageSize.x * 2.0f / 12.0f;
	wave->scale.y = wave->imageSize.y * 2.0f;
	wave->maxFrame.x = 12;
	wave->SetLocalPos(Vector2(20, -50));
	wave->pivot = OFFSET_LB;

	col = new ObRect();
	col->scale = walk->scale;
	col->scale.x -= 100;
	col->scale.y -= 210;
	col->isFilled = false;
	col->pivot = OFFSET_LB;

	walk->SetParentRT(*col);
	wave->SetParentRT(*col);
}

Hermit::~Hermit()
{
	delete walk;
	delete wave;
}

void Hermit::Init()
{
	col->SetWorldPos(Vector2(-630.0f, -280.0f));
	state = HermitState::WALK;
	walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	wave->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}

void Hermit::Update()
{
	col->MoveWorldPos(RIGHT * 100 * DELTA);


	col->Update();
	walk->Update();
	wave->Update();
}

void Hermit::Render()
{
	col->Render();

	switch (state)
	{
	case HermitState::WALK:
		walk->Render();
		break;
	}

	wave->Render();
}

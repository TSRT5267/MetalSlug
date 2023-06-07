#include "stdafx.h"
#include "Hermit.h"

Hermit::Hermit()
{
	walk = new ObImage(L"Hermit_Walk.gif");
	walk->scale.x = walk->imageSize.x * 2.0f / 12.0f;
	walk->scale.y = walk->imageSize.y * 2.0f;
	walk->maxFrame.x = 12;
	walk->pivot = OFFSET_LB;

	col = new ObRect();
	col->scale = walk->scale;
	col->isFilled = false;
	col->pivot = OFFSET_LB;

	walk->SetParentRT(*col);
}

Hermit::~Hermit()
{
	delete walk;
}

void Hermit::Init()
{
	col->SetWorldPos(Vector2(-630.0f, -300.0f));
	state = HermitState::WALK;
	walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}

void Hermit::Update()
{
	col->MoveWorldPos(RIGHT * 100 * DELTA);


	col->Update();
	walk->Update();
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
}

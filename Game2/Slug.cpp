#include "stdafx.h"
#include "Slug.h"
#include "Map.h"
#include "Bullet.h"
#include "Hermit.h"

Slug::Slug()
{
	hp = 4;

	//행동
	{
		idle = new ObImage(L"slug/idle.gif");
		idle->scale.x = idle->imageSize.x * 2.0f / 3.0f;
		idle->scale.y = idle->imageSize.y * 2.0f;
		idle->maxFrame.x = 3;
		idle->pivot = OFFSET_RB;

		drive = new ObImage(L"slug/drive.gif");
		drive->scale.x = drive->imageSize.x * 2.0f / 20.0f;
		drive->scale.y = drive->imageSize.y * 2.0f;
		drive->maxFrame.x = 20;
		drive->pivot = OFFSET_RB;

		jump = new ObImage(L"slug/jump.gif");
		jump->scale.x = jump->imageSize.x * 2.0f / 10.0f;
		jump->scale.y = jump->imageSize.y * 2.0f;
		jump->maxFrame.x = 10;
		jump->pivot = OFFSET_RB;

		shooting = new ObImage(L"slug/shooting.gif");
		shooting->scale.x = shooting->imageSize.x * 2.0f / 20.0f;
		shooting->scale.y = shooting->imageSize.y * 2.0f;
		shooting->maxFrame.x = 20;
		shooting->pivot = OFFSET_RB;

		crouch = new ObImage(L"slug/crouch.gif");
		crouch->scale.x = crouch->imageSize.x * 2.0f / 9.0f;
		crouch->scale.y = crouch->imageSize.y * 2.0f;
		crouch->maxFrame.x = 9;
		crouch->pivot = OFFSET_RB;

		crouch_idle = new ObImage(L"slug/crouch_idle.gif");
		crouch_idle->scale.x = crouch_idle->imageSize.x * 2.0f / 3.0f;
		crouch_idle->scale.y = crouch_idle->imageSize.y * 2.0f;
		crouch_idle->maxFrame.x = 3;
		crouch_idle->pivot = OFFSET_RB;

		crouch_drive = new ObImage(L"slug/crouch_drive.gif");
		crouch_drive->scale.x = crouch_drive->imageSize.x * 2.0f / 20.0f;
		crouch_drive->scale.y = crouch_drive->imageSize.y * 2.0f;
		crouch_drive->maxFrame.x = 20;
		crouch_drive->pivot = OFFSET_RB;

		crouch_shooting = new ObImage(L"slug/crouch_shooting.gif");
		crouch_shooting->scale.x = crouch_shooting->imageSize.x * 2.0f / 8.0f;
		crouch_shooting->scale.y = crouch_shooting->imageSize.y * 2.0f;
		crouch_shooting->maxFrame.x = 8;
		crouch_shooting->pivot = OFFSET_RB;
	}

	col = new ObRect();
	col->scale = idle->scale;
	col->isFilled = false;
	col->pivot = OFFSET_RB;
	col->pivot += Vector2(-0.1, 0);

	colb = new ObRect();
	colb->scale = idle->scale;
	colb->scale -= Vector2(50, 110);
	colb->color = Vector4(0, 0, 0, 1);
	colb->isFilled = false;
	colb->pivot = OFFSET_RB;

	gun = new ObImage(L"slug/gun.gif");
	gun->scale.x = gun->imageSize.x * 2.0f / 17.0f;
	gun->scale.y = gun->imageSize.y * 2.0f;
	gun->SetLocalPos(Vector2(-19, 42));
	gun->maxFrame.x = 17;

	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i] = new Bullet;		
	}
	
	idle->SetParentRT(*col);
	drive->SetParentRT(*col);
	jump->SetParentRT(*col);
	shooting->SetParentRT(*col);
	crouch->SetParentRT(*col);
	crouch_idle->SetParentRT(*col);
	crouch_drive->SetParentRT(*col);
	crouch_shooting->SetParentRT(*col);
	gun->SetParentRT(*col);
	colb->SetParentRT(*col);
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i]->SetParentRT(*gun);
	}
}

Slug::~Slug()
{
	delete idle;
	delete drive;
	delete jump;
	delete crouch;
	delete crouch_idle;
	delete crouch_drive;
	delete col;
	delete colb;
	for (int i = 0; i < BULLETMAX; i++)
	{
		delete bullet[i];
	}

	TEXTURE->DeleteTexture(L"slug/idle.gif");
}

void Slug::Init()
{
	col->SetWorldPos(Vector2(0.0f, -200.0f));
	state = SlugState::IDLE;
	idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}

void Slug::Update()
{
	//모든행동에 처음은 idle
	if (state == SlugState::IDLE)
	{
		col->scale = idle->scale;

		//drive(->)
		if (INPUT->KeyPress(VK_RIGHT))
		{
			state = SlugState::DRIVE;			
			drive->ChangeAnim(ANIMSTATE::REVERSE_LOOP, 0.05f);
		}
		//drive(<-)
		else if (INPUT->KeyPress(VK_LEFT))
		{
			state = SlugState::DRIVE;
			drive->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
		}
		//jump
		if (INPUT->KeyPress('X') )
		{
			state = SlugState::JUMP;
			gravity = -300.0f;
			col->MoveWorldPos(UP);
			jump->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
		}
		//crouch
		if (INPUT->KeyDown(VK_DOWN))
		{
			state = SlugState::CROUCH;
			crouch->ChangeAnim(ANIMSTATE::ONCE, 0.02f);
		}
		//shooting
		if (INPUT->KeyDown('C'))
		{
			state = SlugState::SHOOTING;
			shooting->ChangeAnim(ANIMSTATE::ONCE, 0.02f);
		}
	}
	else if (state == SlugState::DRIVE)
	{
		col->scale = drive->scale;
		
		if (INPUT->KeyPress('X'))
		{
			state = SlugState::JUMP;
			gravity = -300.0f;
			col->MoveWorldPos(UP);
			jump->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
		}
		if (INPUT->KeyUp(VK_LEFT))
		{
			state = SlugState::IDLE;
		}
		else if (INPUT->KeyUp(VK_RIGHT))
		{
			state = SlugState::IDLE;
		}
		
		if (INPUT->KeyDown(VK_DOWN))
		{
			state = SlugState::CROUCH;						
			crouch->ChangeAnim(ANIMSTATE::ONCE, 0.02f);
		}
		if (INPUT->KeyDown('C'))
		{
			state = SlugState::SHOOTING;
			shooting->ChangeAnim(ANIMSTATE::ONCE, 0.02f);
		}
	}
	else if (state == SlugState::JUMP)
	{
		col->scale = jump->scale;
		gravity += 500.0f * DELTA;
		col->MoveWorldPos(DOWN * gravity * DELTA);
		gun->SetLocalPosY(65);

		if (colb->GetWorldPos().y <= -200.0f)
		{
			col->SetWorldPosY(-200.0f);
			gun->SetLocalPosY(42);
			if (INPUT->KeyPress(VK_DOWN))
			{
				state = SlugState::CROUCH;
				crouch->ChangeAnim(ANIMSTATE::ONCE, 0.02f);
			}
			else state = SlugState::IDLE;
		}
		
	}
	else if (state == SlugState::CROUCH)
	{
		col->scale = crouch->scale;
		col->scale.y -= 36.0f;
		if (TIMER->GetTick(animdelay, 0.2f))
		{
			if (INPUT->KeyPress(VK_DOWN))
			{
				state = SlugState::CROUCH_IDLE;
				crouch_idle->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
			}
			if (INPUT->KeyUp(VK_DOWN))
			{
				state = SlugState::IDLE;
			}
			//crouch_drive(->)
			if (INPUT->KeyPress(VK_RIGHT))
			{
				state = SlugState::CROUCH_DRIVE;
				crouch_drive->ChangeAnim(ANIMSTATE::REVERSE_LOOP, 0.05f);
			}
			//crouch_drive(<-)
			if (INPUT->KeyPress(VK_LEFT))
			{
				state = SlugState::CROUCH_DRIVE;
				crouch_drive->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
			}
		}
		if (INPUT->KeyUp(VK_DOWN))
		{
			state = SlugState::IDLE;
		}
		if (INPUT->KeyDown('C'))
		{
			state = SlugState::CROUCH_SHOOTING;
			crouch_shooting->ChangeAnim(ANIMSTATE::ONCE, 0.02f);
		}
	}
	else if (state == SlugState::CROUCH_IDLE)
	{
		col->scale = crouch_idle->scale;

		if (INPUT->KeyUp(VK_DOWN))
		{
			state = SlugState::IDLE;
		}
		//crouch_drive(->)
		if (INPUT->KeyPress(VK_RIGHT))
		{
			state = SlugState::CROUCH_DRIVE;
			crouch_drive->ChangeAnim(ANIMSTATE::REVERSE_LOOP, 0.05f);
		}
		//crouch_drive(<-)
		if (INPUT->KeyPress(VK_LEFT))
		{
			state = SlugState::CROUCH_DRIVE;
			crouch_drive->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
		}
		if (INPUT->KeyDown('C'))
		{
			state = SlugState::CROUCH_SHOOTING;
			crouch_shooting->ChangeAnim(ANIMSTATE::ONCE, 0.02f);
		}
	}
	else if (state == SlugState::CROUCH_DRIVE)
	{
		col->scale = crouch_drive->scale;

		if (INPUT->KeyUp(VK_DOWN))
		{
			state = SlugState::DRIVE;
		}
		if (INPUT->KeyUp(VK_RIGHT))
		{
			state = SlugState::CROUCH_IDLE;
		}
		if (INPUT->KeyUp(VK_LEFT))
		{
			state = SlugState::CROUCH_IDLE;
		}
		if (INPUT->KeyDown('C'))
		{
			state = SlugState::CROUCH_SHOOTING;
			crouch_shooting->ChangeAnim(ANIMSTATE::ONCE, 0.02f);
		}
	}
	else if (state == SlugState::SHOOTING)
	{
		col->scale = shooting->scale;
		if (shooting->frame.x == 19)
		{
			state = SlugState::IDLE;
			idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	else if (state == SlugState::CROUCH_SHOOTING)
	{
		col->scale = crouch_shooting->scale;
		if (crouch_shooting->frame.x == 7)
		{
			state = SlugState::CROUCH_IDLE;
			crouch_idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	
	//슬러그이동
	if (INPUT->KeyPress(VK_LEFT))
	{
		col->MoveWorldPos(LEFT * 400.0f * DELTA);		
	}
	if (INPUT->KeyPress(VK_RIGHT))
	{
		col->MoveWorldPos(RIGHT * 400.0f * DELTA);		
	}

	//총구회전
	{
		
		if (INPUT->KeyPress(VK_UP))
		{
			if (gun->frame.x > 8)
			{
				if (TIMER->GetTick(turndelay, 0.05f)) gun->frame.x -= 1;
			}
			else if ((gun->frame.x < 8))
			{
				if (TIMER->GetTick(turndelay, 0.05f)) gun->frame.x += 1;
			}
		}
		else if (INPUT->KeyPress(VK_RIGHT))
		{
			if (gun->frame.x > 0)
			{
				if (TIMER->GetTick(turndelay, 0.05f)) gun->frame.x -= 1;
			}
		}
		else if (INPUT->KeyPress(VK_LEFT))
		{
			if (gun->frame.x < 16)
			{
				if (TIMER->GetTick(turndelay, 0.05f)) gun->frame.x += 1;
			}
		}
	}

	//총알발사
	{
		if (INPUT->KeyPress('Z') and TIMER->GetTick(firedelay, 0.1f))
		{			
			for (int i = 0; i < BULLETMAX; i++)
			{
				if (not (bullet[i]->Getisfire() or bullet[i]->Getishit()))
				{
					bullet[i]->Fire(gun);
					break;
				}
			}		
		}
	}
	
	
	if (damagedelay > 0.0f) damagedelay -= DELTA;	


	gravity += 500.0f * DELTA;
	col->MoveWorldPos(DOWN * gravity * DELTA);
	
	col->scale -= Vector2(30,30);	
	
	col->	Update();
	colb->	Update();
	idle->	Update();
	drive->	Update();
	jump->	Update();
	crouch->Update();
	crouch_idle->Update();
	crouch_drive->Update();
	shooting->Update();
	crouch_shooting->Update();
	gun->Update();
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i]->Update();
	}
}



void Slug::Hit()
{
	if (damagedelay <= 0.0f)
	{
		hp--;
		damagedelay = 3.0f;
	}
}

void Slug::OnFloor()
{		
	gravity = 0.0f;
	col->SetWorldPosY( -200.0f);
	col->Update();
}

void Slug::Render()
{
	col->Render();
	colb->Render();

	switch (state)
	{
	case SlugState::IDLE: 
		idle->Render();
		break;
	case SlugState::DRIVE:
		drive->Render();
		break;	
	case SlugState::JUMP:
		jump->Render();
		break;
	case SlugState::CROUCH:
		crouch->Render();
		break;
	case SlugState::CROUCH_IDLE:
		crouch_idle->Render();
		break;
	case SlugState::CROUCH_DRIVE:
		crouch_drive->Render();
		break;
	case SlugState::SHOOTING:
		shooting->Render();
		break;
	case SlugState::CROUCH_SHOOTING:
		crouch_shooting->Render();
		break;
	}

	gun->Render();
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i]->Render();
	}
}

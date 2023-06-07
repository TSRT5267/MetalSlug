#include "framework.h"

ObLine* GameObject::axisObject = nullptr;
ID3D11Buffer* GameObject::WVPBuffer = nullptr;
ID3D11Buffer* GameObject::colorBuffer = nullptr;
Shader* GameObject::basicShader = nullptr;
Shader* GameObject::imageShader = nullptr;

void GameObject::CreateStaticMember()
{
	//CreateConstantBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(Matrix);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &WVPBuffer);
		assert(SUCCEEDED(hr));
	}
	D3D->GetDC()->VSSetConstantBuffers(0, 1, &WVPBuffer);

	//CreateConstantBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(Color);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &colorBuffer);
		assert(SUCCEEDED(hr));
	}
	D3D->GetDC()->VSSetConstantBuffers(1, 1, &colorBuffer);

	basicShader = new Shader(L"1.Basic");
	imageShader = new Shader(L"2.Image");

	//char 문자형 -> 아스키코드
	// r d  ㄱㅇㄷ
	//wchar_t 2byte
	//wchar_t a;

	//"dfa";
	//"감사함";
	////c 스타일 문자열
	//char arr[4];
	//arr[0] = 'd';

	////c++ 스타일 문자열
	//string a;
	//a = "a";
	//wstring b;
	//b = L"a";

	axisObject = new ObLine();
}

void GameObject::DeleteStaticMember()
{
	delete axisObject;
	delete basicShader;
	delete imageShader;
	WVPBuffer->Release();
	colorBuffer->Release();
}


GameObject::GameObject()
{
	position.x = 0;
	position.y = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;

	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;

	rotation2.x = 0.0f;
	rotation2.y = 0.0f;
	rotation2.z = 0.0f;

	hasAxis = false;
	color = Color(0.5, 0.5, 0.5, 0.5);
	isVisible = true;
	isFilled = true;
	P = nullptr;
	pivot = OFFSET_N;
	space = SPACE::WORLD;
	colOnOff = true;
}

void GameObject::Update()
{
	Pi = Matrix::CreateTranslation(pivot.x, pivot.y, 0.0f);
	S = Matrix::CreateScale(scale.x, scale.y,1.0f);
	T = Matrix::CreateTranslation(position.x, position.y,0.0f);
	R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	R2 = Matrix::CreateFromYawPitchRoll(rotation2.y, rotation2.x, rotation2.z);
	//Y = Matrix::CreateFromYawPitchRoll(,);

	RT =  R * T * R2;
	
	//P의 주소가 있으면
	if (P)
	{
		RT *= *P;
	}
	W = Pi * S * RT;
}

void GameObject::Render()
{
	if (hasAxis)
	{
		//right
		axisObject->SetWorldPos(GetWorldPos());
		axisObject->rotation.z = Utility::DirToRadian(GetRight());
		axisObject->scale.x = scale.x * 2.0f;
		axisObject->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		axisObject->Update();
		axisObject->Render();
		//up
		axisObject->rotation.z= Utility::DirToRadian(GetUp());
		axisObject->scale.x = scale.y * 2.0f;
		axisObject->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
		axisObject->Update();
		axisObject->Render();
	}

	switch (space)
	{
	case SPACE::WORLD:
		WVP = W * CAM->GetVP();
		break;
	case SPACE::SCREEN:
		WVP = W * CAM->GetP();
		break;
	}

	WVP = WVP.Transpose();
	//wvp 바인딩
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(WVPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Matrix), &WVP, sizeof(Matrix));
		D3D->GetDC()->Unmap(WVPBuffer, 0);
	}
	//color 바인딩
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(colorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Color), &color, sizeof(Color));
		D3D->GetDC()->Unmap(colorBuffer, 0);
	}
}

bool GameObject::Intersect(Vector2 coord)
{
	if (collider == COLLIDER::RECT)
	{
		//회전 X
		if (GetRight() == RIGHT)
		{
			Utility::RECT rc(GetWorldPivot(), scale);
			return IntersectRectCoord(rc, coord);
		}
		else
		{
			Vector2 rcPivot = Vector2::Transform(pivot, S);
			Utility::RECT rc(rcPivot, scale);

			Matrix rcInvert = RT.Invert();
			coord = Vector2::Transform(coord, rcInvert);

			return IntersectRectCoord(rc, coord);
		}
	}
	else if (collider == COLLIDER::CIRCLE)
	{
		Utility::CIRCLE cc(GetWorldPivot(), scale);
		return Utility::IntersectCircleCoord(cc, coord);
	}

	return false;
}

bool GameObject::Intersect(GameObject* ob)
{
	if (collider == COLLIDER::RECT)
	{
		if (ob->collider == COLLIDER::RECT)
		{
			//회전 X
			if ((GetRight() == RIGHT) && (ob->GetRight() == RIGHT))
			{
				Utility::RECT rc1(GetWorldPivot(), scale);
				Utility::RECT rc2(ob->GetWorldPivot(), ob->scale);
				return Utility::IntersectRectRect(rc1, rc2);
			}
			else
			{
				return Utility::IntersectRectRect(this, ob);
			}
			
		}
		else if (ob->collider == COLLIDER::CIRCLE)
		{
			//회전 X
			if (GetRight() == RIGHT)
			{
				Utility::RECT rc(GetWorldPivot(), scale);
				Utility::CIRCLE cc(ob->GetWorldPivot(), ob->scale);
				return Utility::IntersectRectCircle(rc, cc);
			}
			else
			{
				Vector2 rcPivot = Vector2::Transform(pivot, S);
				Utility::RECT rc(rcPivot, scale);

				Matrix rcInvert = RT.Invert();
				Vector2 ccpivot = Vector2::Transform(ob->GetWorldPivot(), rcInvert);
				Utility::CIRCLE cc(ccpivot, ob->scale);

				return IntersectRectCircle(rc, cc);
			}
			
		}
	}
	else if (collider == COLLIDER::CIRCLE)
	{
		if (ob->collider == COLLIDER::RECT)
		{
			//회전 X
			if (ob->GetRight() == RIGHT)
			{
				Utility::RECT rc(ob->GetWorldPivot(), ob->scale);
				Utility::CIRCLE cc(GetWorldPivot(), scale);
				return Utility::IntersectRectCircle(rc, cc);
			}
			else
			{
				Vector2 rcPivot = Vector2::Transform(ob->pivot, ob->S);
				Utility::RECT rc(rcPivot, ob->scale);

				Matrix rcInvert = ob->RT.Invert();
				Vector2 ccpivot = Vector2::Transform(GetWorldPivot(), rcInvert);
				Utility::CIRCLE cc(ccpivot, scale);

				return IntersectRectCircle(rc, cc);
			}
		}
		else if (ob->collider == COLLIDER::CIRCLE)
		{
			Utility::CIRCLE cc1(GetWorldPivot(), scale);
			Utility::CIRCLE cc2(ob->GetWorldPivot(), ob->scale);
			return Utility::IntersectCircleCircle(cc1, cc2);
		}
	}

	return false;
}

bool GameObject::IntersectScreenMouse(Vector2 coord)
{
	coord.y = app.GetHalfHeight() - coord.y;
	coord.x = coord.x - app.GetHalfWidth();

	return Intersect(coord);
}

void GameObject::SetWorldPos(Vector2 worldPos)
{
	if (!P)
	{
		position = worldPos;
	}
	else
	{
		Vector2 location = Vector2::Transform(worldPos, (*P).Invert());
		position = location;
	}
}
void GameObject::SetWorldPosX(float worldPosX)
{
	if (!P)
	{
		position.x = worldPosX;
	}
	else
	{
		Vector2 location = Vector2::Transform(Vector2(worldPosX, 0), (*P).Invert());
		position.x = location.x;
	}
}
void GameObject::SetWorldPosY(float worldPosY)
{
	if (!P)
	{
		position.y = worldPosY;
	}
	else
	{
		Vector2 location = Vector2::Transform(Vector2(0, worldPosY), (*P).Invert());
		position.y = location.y;
	}
}
void GameObject::MoveWorldPos(Vector2 Velocity)
{
	if (!P)
	{
		position += Velocity;
	}
	else
	{
		Vector2 locVelocity = Vector2::TransformNormal(Velocity, (*P).Invert());
		position += locVelocity;
	}
}

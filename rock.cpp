#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "shader.h"
#include "model.h"
#include "rock.h"
#include "scene.h"
#include "shadow.h"
#include "obb.h"
#include "camera.h"
#include "ImGUI/imgui.h"


Rock::Rock(Scene * scene, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int drawPriority)
	: Obstancle(scene, drawPriority)
{
	SetPosition(pos);
	SetRotation(rot);
	SetScale(scale);

	m_Size = ResourceData::GetInstance()->GetModelResource(ResourceTag::mRock)->GetSize();
	m_Adjust = D3DXVECTOR3(0.0f, -0.27, 0.0f) * m_Scale;

	m_Obb = new OBB(m_Position, m_Size * m_Scale, m_Adjust, m_Rotation);
	m_Shadow = new Shadow(scene, { pos.x, 0.f,pos.z }, { 1.0f * scale.x,1.0f * scale.z }, 2);

	m_Visble = true;
}

void Rock::Update()
{
	//ImGui::Begin("RockState");

	//ImGui::Text("Visible");
	//ImGui::SameLine;
	//ImGui::Text("%d", m_Visble);
	//ImGui::End();
}

void Rock::Draw()
{
	Camera* camera = GetScene()->GetGameObject<Camera>(ObjectType::eObCamera);
	if (!camera->CheckView(m_Position, GetRight(), m_Scale)) {
		//m_Visble = true;
		return;
	}
	else
	{
		//m_Visble = false;
	}

	
	// 入力レイアウト設定 fvfs
	Renderer::GetInstance()->GetDeviceContext()->IASetInputLayout(Shader::GetInstance()->GetVertexLayout(ShaderType::LIGHTING));

	// シェーダー設定
	Renderer::GetInstance()->GetDeviceContext()->VSSetShader(Shader::GetInstance()->GetVertexShader(ShaderType::LIGHTING), NULL, 0);		// 描画するものごとに変えられる
	Renderer::GetInstance()->GetDeviceContext()->PSSetShader(Shader::GetInstance()->GetPixelShader(ShaderType::LIGHTING), NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixRotationYawPitchRoll(&rot, GetRotation().y, GetRotation().x, GetRotation().z);
	D3DXMatrixTranslation(&trans, GetPosition().x, GetPosition().y, GetPosition().z);
	world = scale * rot * trans;
	Renderer::GetInstance()->SetWorldMatrix(&world);

	ResourceData::GetInstance()->GetModelResource(ResourceTag::mRock)->Draw();
}

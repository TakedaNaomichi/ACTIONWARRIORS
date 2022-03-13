#pragma once

#include "resource.h"

// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// ���f���\����
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


class Model : public ResourceData
{
private:
	ID3D11Buffer*	m_VertexBuffer;
	ID3D11Buffer*	m_IndexBuffer;

	SUBSET*	m_SubsetArray;
	unsigned int	m_SubsetNum;

	D3DXVECTOR3 m_Size;

	void LoadObj(const char *FileName, MODEL *Model);
	void LoadMaterial(const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum);

public:
	Model() = delete;
	Model(const char *FileName);
	~Model();

	void Draw();

	void Load(const char *FileName);
	void Unload();

	D3DXVECTOR3 GetSize()const { return m_Size; }

};
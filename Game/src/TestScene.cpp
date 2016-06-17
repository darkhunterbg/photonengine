#include <photon\Services\Scene.h>
#include <photon\Services\AssetsService.h>

#include <photon\Math\Matrix.h>
#include <photon\Math\Vector.h>

#include "TestScene.h"

using namespace photon;

struct Vertex {
	Vector4 position;
	float texCoordX;
	float texCoordY;
} vertices[] = {
	{ { -1.0f, -1.f, 0.0f, 1.0f }, 0.0f, 1.0f },
	{ { 1.f, -1.f, 0.0f, 1.0f }, 1.0f, 1.0f },
	{ { 1.f,  1.f, 0.0f, 1.0f }, 1.0f, 0.0f },
	{ { -1.f,  1.f, 0.0f, 1.0f }, 0.0f, 0.0f },
};
unsigned short indices[] = {
	0,1,3,2
};


int geometry = -1;

void TestScene::Initialize()
{
	//photon::TextureAsset& texture = photon::gl_AssetsService->GetTextureAsset("texture.dds");
	//photon::TextureAsset& texture = photon::gl_AssetsService->GetTextureAsset("texture.bmp");

	VertexBufferLayout layout;
	layout.attributesCount = 2;
	layout.instance = 0;
	VertexAttribute attr0[] = { { 0, VertexParamType::FLOAT4 },{ 1 , VertexParamType::FLOAT2 } };
	layout.attributes = attr0;

	int ib = gl_GraphicsService->GetDevice().LoadIndexBuffer(indices, 4, IndiceType::USHORT);
	int vb = gl_GraphicsService->GetDevice().LoadVertexBuffer(VertexBufferType::STATIC, vertices, 4, sizeof(Vertex));
	geometry = gl_GraphicsService->CreateGeometry(vb, ib, layout);
}

void TestScene::Update()
{
	int texture = gl_AssetsService->GetTextureAsset("texture.dds").textureID;
	int texture2 = gl_AssetsService->GetTextureAsset("texture2.dds").textureID;

	for (int i = 0; i < 10; ++i)
	{
		Matrix m = Matrix::Translation({ (float)i - 5.0f,0.0f }) * photon::Matrix::Scale({ 0.5f,0.5f, 1 });
		gl_GraphicsService->RenderObject(m, geometry, texture );

		m = photon::Matrix::Translation({ (float)i - 5.0f,1.0f }) * photon::Matrix::Scale({ 0.5f,0.5f, 1 });
		gl_GraphicsService->RenderObject(m, geometry, texture2);
	}
}

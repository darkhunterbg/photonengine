#include <photon\Services\Scene.h>
#include <photon\Services\AssetsService.h>
#include <photon\Services\Vertex.h>

#include <photon\Math\Matrix.h>
#include <photon\Math\Vector.h>

#include "TestScene.h"

using namespace photon;

 Vertex vertices[] = {
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


	int ib = gl_GraphicsService->CreateIndexBuffer(indices, 4);
	int vb = gl_GraphicsService->CreateVertexBuffer(VertexType::VERTEX, vertices, 4);
	geometry = gl_GraphicsService->CreateGeometry(vb, ib, VertexType::VERTEX);
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

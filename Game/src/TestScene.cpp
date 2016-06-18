#include <photon\Services\Scene.h>
#include <photon\Services\AssetsService.h>
#include <photon\Services\Vertex.h>
#include <photon\Services\GraphicsData.h>

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
Indice indices[] = {
	0,1,3,2
};


GeometryHandler geometry = -1;
MaterialHandler t0;
MaterialHandler t1;

void TestScene::Initialize()
{
	 t0 = gl_AssetsService->GetMaterialAsset("texture.dds").material;
	 t1 = gl_AssetsService->GetMaterialAsset("texture2.dds").material;

	int ib = gl_GraphicsService->CreateIndexBuffer(indices, 4);
	int vb = gl_GraphicsService->CreateVertexBuffer(VertexType::VERTEX, vertices, 4);
	geometry = gl_GraphicsService->CreateGeometry(vb, ib, VertexType::VERTEX);
}

void TestScene::Update()
{
	for (int i = 0; i < 10; ++i)
	{
		Matrix m = Matrix::Translation({ (float)i - 5.0f,0.0f }) * photon::Matrix::Scale({ 0.5f,0.5f, 1 });
		gl_GraphicsService->RenderGeometry(m, geometry, t0 );

		m = photon::Matrix::Translation({ (float)i - 5.0f,1.0f }) * photon::Matrix::Scale({ 0.5f,0.5f, 1 });
		gl_GraphicsService->RenderGeometry(m, geometry, t1);
	}
}

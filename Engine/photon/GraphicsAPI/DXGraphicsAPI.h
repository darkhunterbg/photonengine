#pragma once

#include "../PE.h"

#if defined(DIRECTX)
#include "GraphicsAPI.h"

#pragma comment (lib,"d3d11.lib")

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11Debug;

namespace photon
{
	struct EXPORT DXAPIParam
	{
		void* hWindow;
	};

	class DXGraphicsAPI : public GraphicsAPI
	{
		friend class GraphicsAPI;
	private:
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;
		IDXGISwapChain* swapChain = nullptr;

		ID3D11Debug* d3d11Debug = nullptr;

	protected:
		DXGraphicsAPI(const DXAPIParam* apiParam);
	public:
		virtual ~DXGraphicsAPI() override;


		virtual void SwapBuffers() override;
	};
}

#endif
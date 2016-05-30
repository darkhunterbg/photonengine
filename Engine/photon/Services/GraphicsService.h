#pragma once

#include "../PE.h"
#include "MemoryStack.h"
#include "../GraphicsAPI/GraphicsAPI.h"

namespace photon
{


	class EXPORT GraphicsService
	{
		DISABLE_NEW_DELETE(GraphicsService);
		DISABLE_COPY(GraphicsService);

	private:
		GraphicsAPI* api;

		GraphicsService(GraphicsAPI* api);
	

	public:
		static GraphicsService* Initialize(GraphicsAPIType apiType,const void* apiParam, MemoryStack& stack);
		static void Uninitialize();

		void PresentFrame();
	};

	EXPORT extern GraphicsService* gl_GraphicsService;
}
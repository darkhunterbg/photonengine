#include "GraphicsService.h"
#include "../Platform/OpenGL.h"

namespace photon
{
	namespace graphics
	{
		GraphicsService* glGraphicsService = nullptr;

		GraphicsService* GraphicsService::Initialize(platform::OpenGLContext* context)
		{
			GraphicsService* glGraphicsService = new GraphicsService();
			glGraphicsService->context = context;

			return glGraphicsService;
		}
		void GraphicsService::Uninitialize()
		{
			delete glGraphicsService;
			glGraphicsService = nullptr;
		}

	/*	void GraphicsService::SetCurrentWindow(photon::platform::Window window)
		{

		}*/
	}
}
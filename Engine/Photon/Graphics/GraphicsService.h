#pragma once

#include "../PE.h"


namespace photon
{
	namespace platform
	{
		struct OpenGLContext;
	}

	namespace graphics
	{

		class EXPORT GraphicsService
		{
		private:
			GraphicsService() = default;
			~GraphicsService() = default;

			platform::OpenGLContext* context;
		public:
			static GraphicsService* Initialize(platform::OpenGLContext* context);
			static void Uninitialize();

			//void SetCurrentWindow(photon::platform::Window window);
		};

		EXPORT extern GraphicsService* glGraphicsService;
	}
}
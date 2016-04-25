#pragma once

#include "../PE.h"
#include "../Memory/MemoryStack.h"

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
			DISABLE_NEW_DELETE(GraphicsService);
			DISABLE_COPY(GraphicsService);

		private:
			GraphicsService(platform::OpenGLContext* context);
			~GraphicsService() = default;


			platform::OpenGLContext* context;
		public:
			static GraphicsService* Initialize(platform::OpenGLContext* context, memory::MemoryStack& stack);
			static void Uninitialize();

			//void SetCurrentWindow(photon::platform::Window window);
		};
	}

	EXPORT extern graphics::GraphicsService* glGraphicsService;
}
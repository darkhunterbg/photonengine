#pragma once

#include "../PE.h"

#if defined(OPENGL)
#include "GraphicsAPI.h"

#include "../OpenGL.h"

namespace photon
{
	struct EXPORT GLAPIParam
	{
		GLCreateParam createParam;
	};

	class GLGraphicsAPI : public GraphicsAPI
	{
		friend class GraphicsAPI;
	protected:
		GLContext context;
		GLGraphicsAPI(const GLAPIParam* apiParam);
	public:
		virtual ~GLGraphicsAPI() override;


		virtual void SwapBuffers() override;
	};
}

#endif
#pragma once

#include "../Macro.h"
#include "MemoryStack.h"
#include "../GraphicsAPI/GraphicsAPI.h"
#include "../GraphicsAPI/GraphicsAPITypes.h"

namespace photon
{
	struct Technique
	{
		ShaderProgramHandler handler;
		bool hasVS : 1;
		bool hasFS : 1;
	};

	class EXPORT GraphicsService
	{
		DISABLE_COPY(GraphicsService);

	private:
		static const int MAX_SHADER_PROGRAMS = 128;
		GraphicsAPI* api;
		Technique techniques[MAX_SHADER_PROGRAMS];
		int techniquesCount = 0;

		GraphicsService(GraphicsAPI* api);
		~GraphicsService();


		void InitializeTechniques();
	public:
		static GraphicsService* Initialize(GraphicsAPI* api, MemoryStack& stack);
		static void Uninitialize();


		void PresentFrame();
	};

	EXPORT extern GraphicsService* gl_GraphicsService;
}
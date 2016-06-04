#pragma once


#include "../Macro.h"

namespace photon
{
	class EXPORT Scene
	{
		DISABLE_COPY(Scene)

	public:
		Scene();
		virtual ~Scene() = 0;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
	};
}
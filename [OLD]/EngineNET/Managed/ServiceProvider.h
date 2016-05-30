#pragma once

#using <mscorlib.dll>

#include "Memory/MemoryService.h"
#include "Graphics/GraphicsService.h"

#include <Photon/Memory/MemoryStack.h>

namespace Photon
{
	///<summary>
	///Manages engine's services
	///</summary>
	public ref class ServiceProvider abstract sealed
	{
	private:
		static photon::memory::MemoryStack* memstack;
	public:
		///<summary>
		///Initialize all services
		///</summary>
		static void InitializeServices(System::IntPtr winHandle);

		///<summary>
		///Uninitialize all services
		///</summary>
		static void UninitializeServices();

		///<summary>
		///Gets the Memory Service
		///</summary>
		static property Photon::Memory::MemoryService^ MemoryService
		{
			Photon::Memory::MemoryService^ get();
		}

		///<summary>
		///Gets the Graphics Service
		///</summary>
		static property Photon::Graphics::GraphicsService^ GraphicsService
		{
			Photon::Graphics::GraphicsService^ get();
		}

		static void SetCurrentWindow(System::IntPtr winHandle);

		static void SwapBackBuffer();
	};

}
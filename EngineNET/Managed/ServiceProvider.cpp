#include "ServiceProvider.h"
#include <Photon/Memory/MemoryStack.h>
#include <Photon/Memory/MemoryService.h>
#include <Photon/Graphics/GraphicsService.h>
#include <Photon/Platform/OpenGL.h>

namespace Photon
{
	photon::platform::OpenGLContext openGLContext;

	void ServiceProvider::InitializeServices(System::IntPtr winHandle)
	{
		auto nativeService = photon::memory::MemoryService::Initialize();
		void* memory = photon::glMemoryService->AllocatePage(Megabytes(1));
		memstack = photon::memory::MemoryStack::New(memory, Megabytes(1));

		Photon::Memory::MemoryService::Instance = gcnew Photon::Memory::MemoryService(nativeService);



		openGLContext = photon::platform::CreateOpenGLContext((HWND)winHandle.ToPointer());
		auto nativeGraphics = photon::graphics::GraphicsService::Initialize( *memstack);

		Photon::Graphics::GraphicsService::Instance = gcnew Photon::Graphics::GraphicsService(nativeGraphics);
		SetCurrentWindow(winHandle);

	}

	void ServiceProvider::UninitializeServices()
	{
		Photon::Graphics::GraphicsService::Instance = nullptr;
		Photon::Memory::MemoryService::Instance = nullptr;
	
		photon::graphics::GraphicsService::Uninitialize();
		photon::platform::DeleteOpenGLContext(openGLContext);
		memstack->Clear();
		photon::memory::MemoryService::Uninitialize();

	}

	Photon::Memory::MemoryService^ ServiceProvider::MemoryService::get()
	{
		return Photon::Memory::MemoryService::Instance;
	}

	Photon::Graphics::GraphicsService^ ServiceProvider::GraphicsService::get()
	{
		return Photon::Graphics::GraphicsService::Instance;
	}

	void ServiceProvider::SetCurrentWindow(System::IntPtr winHandle)
	{
		photon::platform::SetCurrentOpenGLWindow((HWND)winHandle.ToPointer(), openGLContext);
	}

	void ServiceProvider::SwapBackBuffer()
	{
		photon::platform::SwapOpenGLBuffers(openGLContext);
	}

}
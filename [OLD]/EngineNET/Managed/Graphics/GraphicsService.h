#pragma once

#using <mscorlib.dll>

namespace photon
{
	namespace graphics
	{
		class GraphicsService;
	}
}


namespace Photon
{
	namespace Graphics
	{
		///<summary>
		/// Service for managing graphics
		///</summary>
		public ref class GraphicsService  sealed
		{
		private:
			static GraphicsService^ instance;

			photon::graphics::GraphicsService* native;
		internal:
			GraphicsService(photon::graphics::GraphicsService* native);
			~GraphicsService();
		public:

			///<summary>
			///Gets the singleton instance of the GraphicsService
			///</summary>
			static property GraphicsService^ Instance
			{
				GraphicsService^ get();
			internal:
				void set(GraphicsService^ value);
			}
		};
	}
}
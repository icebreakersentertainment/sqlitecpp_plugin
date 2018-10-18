#include "SqliteCppFactory.hpp"

#include "SqliteCpp.hpp"

namespace ice_engine
{
namespace sqlitecpp
{

SqliteCppFactory::SqliteCppFactory()
{
}

SqliteCppFactory::~SqliteCppFactory()
{
}

std::unique_ptr<IScriptingEngineBinding> SqliteCppFactory::create(
	utilities::Properties* properties,
	fs::IFileSystem* fileSystem,
	logger::ILogger* logger,
	graphics::IGraphicsEngine* graphicsEngine,
	pathfinding::IPathfindingEngine* pathfindingEngine,
	physics::IPhysicsEngine* physicsEngine,
	scripting::IScriptingEngine* scriptingEngine,
	audio::IAudioEngine* audioEngine,
	networking::INetworkingEngine* networkingEngine,
	GameEngine* gameEngine
)
{
	std::unique_ptr<IScriptingEngineBinding> ptr = std::make_unique< SqliteCpp >(
		properties,
		fileSystem,
		logger,
		graphicsEngine,
		pathfindingEngine,
		physicsEngine,
		scriptingEngine,
		audioEngine,
		networkingEngine,
		gameEngine
	);
	
	return std::move( ptr );
}

}
}

#ifndef SQLITECPPFACTORY_H_
#define SQLITECPPFACTORY_H_

#include <memory>

#include "IScriptingEngineBindingFactory.hpp"

namespace ice_engine
{
namespace sqlitecpp
{

class SqliteCppFactory : public IScriptingEngineBindingFactory
{
public:
	SqliteCppFactory();
	virtual ~SqliteCppFactory();

	virtual std::unique_ptr<IScriptingEngineBinding> create(
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
	) override;

};

}
}

#endif /* SQLITECPPFACTORY_H_ */

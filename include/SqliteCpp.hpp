#ifndef SQLITECPP_H_
#define SQLITECPP_H_

#include <vector>

#include "IScriptingEngineBindingPlugin.hpp"

#include "utilities/Properties.hpp"
#include "logger/ILogger.hpp"
#include "fs/IFileSystem.hpp"

namespace ice_engine
{

namespace scripting
{
class IScriptingEngine;
}
namespace networking
{
class INetworkingEngine;
}
namespace graphics
{
class IGraphicsEngine;
}
namespace pathfinding
{
class IPathfindingEngine;
}
namespace physics
{
class IPhysicsEngine;
}
namespace audio
{
class IAudioEngine;
}
namespace logger
{
class ILogger;
}

class GameEngine;

namespace sqlitecpp
{

class SqliteCpp : public IScriptingEngineBinding
{
public:
	SqliteCpp(
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
	);
	virtual ~SqliteCpp();

	virtual void bind() override;
	
private:
	logger::ILogger* logger_;
	GameEngine* gameEngine_;
	scripting::IScriptingEngine* scriptingEngine_;
};

}
}

#endif /* SQLITECPP_H_ */


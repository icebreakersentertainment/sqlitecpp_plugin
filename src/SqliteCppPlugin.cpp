#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT

#include "SqliteCppPlugin.hpp"

#include "SqliteCppFactory.hpp"

namespace ice_engine
{

SqliteCppPlugin::SqliteCppPlugin()
{
}

SqliteCppPlugin::~SqliteCppPlugin()
{
}

std::string SqliteCppPlugin::getName() const
{
	return std::string("sqlitecpp");
}

std::unique_ptr<IScriptingEngineBindingFactory> SqliteCppPlugin::createFactory() const
{
	std::unique_ptr<IScriptingEngineBindingFactory> ptr = std::make_unique< sqlitecpp::SqliteCppFactory >();
	
	return std::move( ptr );
}

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT SqliteCppPlugin plugin;
SqliteCppPlugin plugin;

}

#ifndef SQLITECPPPLUGIN_H_
#define SQLITECPPPLUGIN_H_

#include <memory>

#include "IScriptingEngineBindingPlugin.hpp"

namespace ice_engine
{

class SqliteCppPlugin : public IScriptingEngineBindingPlugin
{
public:
	SqliteCppPlugin();
	virtual ~SqliteCppPlugin();

	virtual std::string getName() const override;

	virtual std::unique_ptr<IScriptingEngineBindingFactory> createFactory() const override;

};

}

#endif /* SQLITECPPPLUGIN_H_ */

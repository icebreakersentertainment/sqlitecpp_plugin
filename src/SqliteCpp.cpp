#include "Platform.hpp"
#include "Types.hpp"

#include "SQLiteCpp/SQLiteCpp.h"

#include "SqliteCpp.hpp"
#include "BindingDelegateUtilities.hpp"

#include "scripting/IScriptingEngine.hpp"

//#include "GameEngine.hpp"

namespace ice_engine
{

class GameEngine;

namespace sqlitecpp
{

namespace databasebinding
{
void DatabaseInitConstructor(const std::string& filename, void* memory) { new(memory) SQLite::Database(filename); }
void StatementInitConstructor(SQLite::Database& aDatabase, const std::string& apQuery, void* memory) { new(memory) SQLite::Statement(aDatabase, apQuery); }
}
/*
class DatabaseWrapper : public SQLite::Database
{
public:
	using SQLite::Database::Database;

	static DatabaseWrapper* DatabaseWrapperFactory(const std::string& databaseName)
	{
	    return new DatabaseWrapper(databaseName);
	}

	void Addref()
	{
	    // Increase the reference counter
	    refCount++;
	}

	void Release()
	{
	    // Decrease ref count and delete if it reaches 0
	    if( --refCount == 0 ) delete this;
	}

private:
	int refCount = 0;
};
*/
SqliteCpp::SqliteCpp(
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
	:
	logger_(logger),
	scriptingEngine_(scriptingEngine),
	gameEngine_(gameEngine)
{
}

SqliteCpp::~SqliteCpp()
{
}

template<class A, class B>
B valueCastString(A& a)
{
    return std::string(static_cast<const char*>(a));
}

void SqliteCpp::bind()
{
	/*
	scriptingEngine_->registerObjectType("Database", 0, asOBJ_REF);
	scriptingEngine_->registerObjectBehaviour("Database", asBEHAVE_FACTORY, "Database@ f(const string& in)", asFUNCTION(DatabaseWrapper::DatabaseWrapperFactory), asCALL_CDECL);
	scriptingEngine_->registerObjectBehaviour("Database", asBEHAVE_ADDREF, "void f()", asMETHOD(DatabaseWrapper,Addref), asCALL_THISCALL);
	scriptingEngine_->registerObjectBehaviour("Database", asBEHAVE_RELEASE, "void f()", asMETHOD(DatabaseWrapper,Release), asCALL_THISCALL);
	*/
	scriptingEngine_->registerObjectType("Database", sizeof(SQLite::Database), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<SQLite::Database>());
	scriptingEngine_->registerObjectBehaviour("Database", asBEHAVE_CONSTRUCT, "void f(const string& in)", asFUNCTION(databasebinding::DatabaseInitConstructor), asCALL_CDECL_OBJLAST);
	scriptingEngine_->registerObjectBehaviour("Database", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DefaultDestructor<SQLite::Database>), asCALL_CDECL_OBJFIRST);

	scriptingEngine_->registerObjectType("Column", sizeof(SQLite::Column), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<SQLite::Column>());
	scriptingEngine_->registerObjectBehaviour("Column", asBEHAVE_CONSTRUCT, "void f(const Column& in)", asFUNCTION(CopyConstructor<SQLite::Column>), asCALL_CDECL_OBJLAST);
	scriptingEngine_->registerObjectBehaviour("Column", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DefaultDestructor<SQLite::Column>), asCALL_CDECL_OBJFIRST);
	//auto assignmentOperatorFunctionString = "Column" + std::string("& opAssign(const ") + "Column" + "& in)";
	//scriptingEngine_->registerObjectMethod("Column", assignmentOperatorFunctionString.c_str(), asFUNCTION(defaultAssignmentOperator<SQLite::Column>), asCALL_CDECL_OBJLAST);
	scriptingEngine_->registerClassMethod("Column", "int getInt()", asMETHOD(SQLite::Column, getInt));
	scriptingEngine_->registerObjectMethod("Column", "int opConv()", asFUNCTION((valueCast<SQLite::Column,int>)), asCALL_CDECL_OBJLAST);
	scriptingEngine_->registerObjectMethod("Column", "int opImplConv()", asFUNCTION((valueCast<SQLite::Column,int>)), asCALL_CDECL_OBJLAST);
	scriptingEngine_->registerObjectMethod("Column", "string opConv()", asFUNCTION((valueCastString<SQLite::Column,std::string>)), asCALL_CDECL_OBJLAST);
	scriptingEngine_->registerObjectMethod("Column", "string opImplConv()", asFUNCTION((valueCastString<SQLite::Column,std::string>)), asCALL_CDECL_OBJLAST);

	scriptingEngine_->registerObjectType("Statement", sizeof(SQLite::Statement), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<SQLite::Statement>());
	scriptingEngine_->registerObjectBehaviour("Statement", asBEHAVE_CONSTRUCT, "void f(const Database& in, const string& in)", asFUNCTION(databasebinding::StatementInitConstructor), asCALL_CDECL_OBJLAST);
	scriptingEngine_->registerObjectBehaviour("Statement", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DefaultDestructor<SQLite::Statement>), asCALL_CDECL_OBJFIRST);
	scriptingEngine_->registerClassMethod("Statement", "bool executeStep()", asMETHOD(SQLite::Statement, executeStep));
	scriptingEngine_->registerClassMethod(
		"Statement",
		"Column getColumn(const int)",
		asMETHODPR(SQLite::Statement, getColumn, (const int), SQLite::Column)
	);
	scriptingEngine_->registerClassMethod(
		"Statement",
		"void bind(const int, const int)",
		asMETHODPR(SQLite::Statement, bind, (const int, const int), void)
	);

	/*
	scriptingEngine_->registerClassMethod(
		"Database",
		"void setDatabase(const Database& in)",
		asMETHODPR(Database, setDatabase, (const database::Database&), void)
	);
	scriptingEngine_->registerClassMethod(
		"Database",
		"const Database& database() const",
		asMETHODPR(Database, database, () const, const database::Database&)
	);
	*/
	/*
	// Open a database file
	SQLite::Database    db("example.db3");

	// Compile a SQL query, containing one parameter (index 1)
	SQLite::Statement   query(db, "SELECT * FROM test WHERE size > ?");
	
	// Bind the integer value 6 to the first parameter of the SQL query
	query.bind(1, 6);
	
	// Loop to execute the query step by step, to get rows of result
	while (query.executeStep())
	{
		// Demonstrate how to get some typed column value
		int         id      = query.getColumn(0);
		std::string value   = query.getColumn(1);
		int         size    = query.getColumn(2);

		std::cout << "row: " << id << ", " << value << ", " << size << std::endl;
	}
	*/
}
	
}
};

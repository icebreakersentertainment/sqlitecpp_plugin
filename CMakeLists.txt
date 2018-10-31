cmake_minimum_required(VERSION 3.1.0)

project(sqlitecpp_plugin)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SQLITECPP_PLUGIN_COMPILER_FLAGS "")
if(MSVC)
  set(SQLITECPP_PLUGIN_COMPILER_FLAGS "/EHsc /MP")
  if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(SQLITECPP_PLUGIN_COMPILER_FLAGS "/EHsc /MP")
  endif()
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(SQLITECPP_RUN_CPPCHECK "Run cppcheck C++ static analysis tool." OFF)
option(SQLITECPP_RUN_CPPLINT "Run cpplint.py tool for Google C++ StyleGuide." OFF)

add_subdirectory(./SQLiteCpp/SQLiteCpp)

#include_directories(ice_engine/ice_engine/deps/boost/include)
#include_directories(ice_engine/ice_engine/deps/angelscript/include)
#include_directories(ice_engine/ice_engine/deps/glew/include)
#include_directories(ice_engine/ice_engine/deps/glm/include)
#include_directories(ice_engine/ice_engine/deps/freeimage/include)
#include_directories(ice_engine/ice_engine/deps/sdl/include)
#include_directories(ice_engine/ice_engine/deps/ctpl/include)

# Headers
include_directories(include)

# Source
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(sqlitecpp_plugin SHARED ${SOURCES})

target_include_directories(sqlitecpp_plugin PRIVATE ${ICEENGINE_INCLUDE_DIRS})
target_include_directories(sqlitecpp_plugin PRIVATE ${BOOST_INCLUDE_DIRS})
target_include_directories(sqlitecpp_plugin PRIVATE ${ANGELSCRIPT_INCLUDE_DIRS})
target_include_directories(sqlitecpp_plugin PRIVATE ${GLM_INCLUDE_DIRS})
#target_include_directories(sqlitecpp_plugin PRIVATE ${GLEW_INCLUDE_DIRS})

target_compile_options(sqlitecpp_plugin PRIVATE ${SQLITECPP_PLUGIN_COMPILER_FLAGS})

if(UNIX AND NOT APPLE)
  target_link_libraries(sqlitecpp_plugin -Wl,--whole-archive sqlite3 -Wl,--no-whole-archive)
else()
  target_link_libraries(sqlitecpp_plugin sqlite3)
endif()

target_link_libraries(sqlitecpp_plugin SQLiteCpp)
target_link_libraries(sqlitecpp_plugin ${BOOST_SYSTEM_LIBRARY} )
target_link_libraries(sqlitecpp_plugin ${BOOST_CHRONO_LIBRARY} )
target_link_libraries(sqlitecpp_plugin ${BOOST_THREAD_LIBRARY} )
target_link_libraries(sqlitecpp_plugin ${BOOST_DATE_TIME_LIBRARY} )
target_link_libraries(sqlitecpp_plugin ${BOOST_SERIALIZATION_LIBRARY} )

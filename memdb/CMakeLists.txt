file(GLOB memdb_sources
	"*.cpp"
	"*.h"
)

file(GLOB memdb_unittests
	"*_unittest.cpp"
	"*_unittest.h"
)

list(REMOVE_ITEM memdb_sources ${memdb_unittests})

add_library(memdb STATIC ${memdb_sources})

target_include_directories(memdb PUBLIC "..")

target_link_libraries(memdb PUBLIC scada_base)

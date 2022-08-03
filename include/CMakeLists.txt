file(GLOB_RECURSE _headers ${CMAKE_CURRENT_LIST_DIR}/*.h ${CMAKE_CURRENT_LIST_DIR}/*.hpp CONFIGURE_DEPEND)
target_sources(ellipsoid PRIVATE ${_headers})
unset(_headers)

target_include_directories(ellipsoid PUBLIC ${CMAKE_CURRENT_LIST_DIR})
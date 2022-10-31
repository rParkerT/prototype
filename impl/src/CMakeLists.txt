include_directories(${prototype_SOURCE_DIR}/impl/inc)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS serialization filesystem)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(prototype main.cpp)
    target_link_libraries(prototype ${Boost_LIBRARIES})
endif()

# CMakeList.txt : CMake project for sfml, include source and define
# project specific logic here.
#

# Add source to this project's executable.
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
add_executable (sfml "sfml.cpp" "sfml.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sfml PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(sfml PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(sfml PRIVATE sfml-main)

target_link_libraries(sfml PRIVATE ImGui-SFML::ImGui-SFML)

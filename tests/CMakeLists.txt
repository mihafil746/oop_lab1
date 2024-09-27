find_package(Catch2 3 REQUIRED)

add_compile_options(--coverage)

add_link_options(--coverage)

add_executable(testing testing.cpp)

target_link_libraries(testing lib_xml Catch2::Catch2WithMain)

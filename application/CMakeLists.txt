
set(NAME application)
add_executable(${NAME})

file(GLOB_RECURSE
    PROJECT_SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.c"
)
file(GLOB_RECURSE
    PROJECT_HEADER_FILES CONFIGURE_DEPENDS
    "src/*.hpp" "src/*.h"
)

target_compile_features(${NAME} PUBLIC c_std_11)
target_compile_definitions(${NAME} PUBLIC _CRT_SECURE_NO_WARNINGS)

target_sources(${NAME} PRIVATE
    ${PROJECT_SOURCE_FILES}
    ${PROJECT_HEADER_FILES}
)

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake_targets")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PREFIX "sources"
    FILES ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES}
)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(${NAME} PUBLIC ${MATH_LIBRARY})
endif()

#-------------------------------------------------------------------------------
# Other include directories

target_include_directories(
    ${NAME} PUBLIC
    "src"
)

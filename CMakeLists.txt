cmake_minimum_required(VERSION 3.12)

project(SpaceCraze)

# Använd C++ 17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_USE_RELATIVE_PATHS TRUE)

# Välj vilka delar av SFML som ska användas.
set(SFML_MODULES network graphics window system audio)

# Lägg till lämpliga bibliotek till kompileringen. Man kan använda 'find_package ',
# men det kräver att SFML är installerat på ett annat sätt.
foreach(i ${SFML_MODULES})
	list(APPEND SFML_LIBRARIES "sfml-${i}")
endforeach(i)

find_library(LIBJSONCPP jsoncpp "/dependencies/jsoncpp/")

# Ange källfiler
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cc")

include_directories("src" "dependencies/jsoncpp/include/")

# -Wextra -pedantic -Weffc++ -Wold-style-cast -fmax-errors=3
set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_OPTIONS "-std=c++17;-Wextra;-pedantic;-Weffc++;-Wold-style-cast;-fmax-errors=3")

add_executable(game ${SOURCE_FILES})

# Länka med biblioteken som vi hittade tidigare.
target_link_libraries(game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${LIBJSONCPP})

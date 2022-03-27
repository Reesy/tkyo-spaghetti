cmake_minimum_required(VERSION 3.17.3) 

set(EXECUTABLE_NAME TkyoSpaghetti)

project(TkyoSpaghetti LANGUAGES CXX) #set the project name and to use C++

set(CMAKE_BUILD_TYPE Debug)

set(MY_SOURCES 
        src/main.cpp
        src/Platform.cpp
        src/Player.cpp
        src/Text.cpp
        src/Score.cpp
        include/IAnimatable.hpp
        include/ICollidable.hpp
        include/IMovable.hpp
        include/IPlatform.hpp
        include/IPlayer.hpp
        include/IVisible.hpp
        include/IText.hpp
        include/IScore.hpp
)

set(MY_RESOURCES resources)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    find_package(SDL2 REQUIRED)

    find_package(SDL2_IMAGE REQUIRED)

    find_package(SDL2_TTF REQUIRED)

    find_package(SDL2_mixer REQUIRED)

    include_directories(${SDL2_IMAGE_INCLUDE_DIR})

    include_directories(${SDL2_INCLUDE_DIR})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (MINGW)
    link_directories("${PROJECT_SOURCE_DIR}/libs/mingw/SDL2-2.0.14/i686-w64-mingw32/lib/" "${PROJECT_SOURCE_DIR}/libs/mingw/SDL2_image-2.0.5/i686-w64-mingw32/lib/")
endif()

add_executable(${EXECUTABLE_NAME} ${MY_SOURCES})

file(COPY ${MY_RESOURCES} DESTINATION ${CMAKE_BINARY_DIR})

message(STATUS "######------ CMAKE_SOURCE_DIR set to: ${CMAKE_SOURCE_DIR}   ------######")

message(STATUS "######------ CMAKE_BINARY_DIR set to: ${CMAKE_BINARY_DIR}   ------######")



if (MSVC)
    add_custom_target(setup
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/vs2019/SDL2-2.0.14/lib/x64/SDL2.dll ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/vs2019/SDL2_image-2.0.5/lib/x64/SDL2_image.dll ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/vs2019/SDL2_image-2.0.5/lib/x64/libjpeg-9.dll ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/vs2019/SDL2_image-2.0.5/lib/x64/libpng16-16.dll ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/vs2019/SDL2_image-2.0.5/lib/x64/libtiff-5.dll ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/vs2019/SDL2_image-2.0.5/lib/x64/libwebp-7.dll ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/vs2019/SDL2_image-2.0.5/lib/x64/zlib1.dll ${CMAKE_BINARY_DIR}/Debug
    )
elseif (MINGW)
    add_custom_target(setup
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/mingw/SDL2-2.0.14/i686-w64-mingw32/bin/SDL2.dll ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/mingw/SDL2_image-2.0.5/i686-w64-mingw32/bin/SDL2_image.dll ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/mingw/SDL2_image-2.0.5/i686-w64-mingw32/bin/libjpeg-9.dll  ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/mingw/SDL2_image-2.0.5/i686-w64-mingw32/bin/libpng16-16.dll ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/mingw/SDL2_image-2.0.5/i686-w64-mingw32/bin/libtiff-5.dll ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/mingw/SDL2_image-2.0.5/i686-w64-mingw32/bin/libwebp-7.dll ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/libs/mingw/SDL2_image-2.0.5/i686-w64-mingw32/bin/zlib1.dll ${CMAKE_BINARY_DIR}/dist
    )
    add_dependencies(${EXECUTABLE_NAME} setup)
endif()

message(STATUS "######------ Checking environment ------######")

if (MSVC)
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-O3 -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\",\"jpg\"]' -s USE_SDL_MIXER=2 -s USE_FREETYPE=1 -s ALLOW_MEMORY_GROWTH=1 --preload-file resources/")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    file(COPY "tkyospaghetti.html" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "resources/sam_icon_2.png" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "server.py" DESTINATION ${CMAKE_BINARY_DIR})
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_libraries(${EXECUTABLE_NAME})
else()
    target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
endif()
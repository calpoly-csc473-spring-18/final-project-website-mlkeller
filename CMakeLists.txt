cmake_minimum_required(VERSION 2.8)

project(part4)

if(WIN32)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(PARSER
	lib/parser/Objects.hpp
	lib/parser/parse_error.hpp
	lib/parser/Parser.cpp
	lib/parser/Parser.hpp
	lib/parser/Tokenizer.cpp
	lib/parser/Tokenizer.hpp
	lib/parser/TokenStream.cpp
	lib/parser/TokenStream.hpp
)

set(SOURCES
	src/Application/Application.cpp
	src/Application/main.cpp
	src/Application/RayInfo.cpp
	src/Application/Renderer.cpp
	src/Application/SceneInfo.cpp
	src/Objects/Box.cpp
	src/Objects/Plane.cpp
	src/Objects/Sphere.cpp
	src/Objects/Triangle.cpp
	src/RayTracer/Pixel.cpp
	src/RayTracer/RayTracer.cpp
	src/RayTracer/Util.cpp
	src/Scene/AABB.cpp
	src/Scene/BoundingVolumeNode.cpp
	src/Scene/Camera.cpp
	src/Scene/Object.cpp
	src/Scene/Scene.cpp
	src/Shading/BlinnPhongBRDF.cpp
	src/Shading/CookTorranceBRDF.cpp
)

set(HEADERS
	src/Application/Application.hpp
	src/Application/RayInfo.hpp
	src/Application/Renderer.hpp
	src/Application/SceneInfo.hpp
	src/Objects/Box.hpp
	src/Objects/Plane.hpp
	src/Objects/Sphere.hpp
	src/Objects/Triangle.hpp
	src/RayTracer/Params.hpp
	src/RayTracer/Pixel.hpp
	src/RayTracer/PixelContext.hpp
	src/RayTracer/Ray.hpp
	src/RayTracer/RayTracer.hpp
	src/RayTracer/RayTraceResults.hpp
	src/RayTracer/Util.hpp
	src/Scene/AABB.hpp
	src/Scene/BoundingVolumeNode.hpp
	src/Scene/Camera.hpp
	src/Scene/Light.hpp
	src/Scene/Object.hpp
	src/Scene/Scene.hpp
	src/Shading/BlinnPhongBRDF.hpp
	src/Shading/BRDF.hpp
	src/Shading/CookTorranceBRDF.hpp
)

add_library(parser ${PARSER})

add_executable(raytrace ${SOURCES} ${HEADERS})
target_include_directories(raytrace PUBLIC "ext/")
target_include_directories(raytrace PUBLIC "lib/")
target_include_directories(raytrace PUBLIC "src/")
target_link_libraries(raytrace parser)

find_package(Threads)
target_link_libraries(raytrace ${CMAKE_THREAD_LIBS_INIT})

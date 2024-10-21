# Version minimale de CMake
cmake_minimum_required(VERSION 3.10)

# Spécifier le compilateur C et C++
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Nom du projet
project(projetGL)

# Définir le nom de l'exécutable via une variable
set(EXECUTABLE_NAME "projetGL")

# Ajouter tous les fichiers source dans le dossier src/ récursivement
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# Définir l'exécutable avec les sources trouvées
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Inclure GLEW
include_directories(deps/glew-cmake/include)

# Inclure le chemin de la bibliothèque GLEW
set(GLEW_LIBRARY "${CMAKE_SOURCE_DIR}/deps/glew-cmake/build/lib/libglew.a")  # Ajuste le chemin si nécessaire

# Définir les options de compilation pour GLEW
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE GLEW_STATIC)  # Utiliser la version statique de GLEW

# GLFW : désactiver la construction des exemples, tests et documentation
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

# Inclure GLFW
add_subdirectory(deps/glfw)
include_directories(deps/glfw/include)

# GLM : bibliothèque header-only
include_directories(deps/glm)

# ImGUI : ajouter les sources d'ImGui et créer une bibliothèque statique
include_directories(deps/imgui)
file(GLOB IMGUI_SOURCES deps/imgui/*.cpp deps/imgui/backends/imgui_impl_glfw.cpp deps/imgui/backends/imgui_impl_opengl3.cpp)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC deps/imgui deps/imgui/backends)

# Lier les bibliothèques à l'exécutable
target_link_libraries(${EXECUTABLE_NAME} PRIVATE glfw ${GLEW_LIBRARY} imgui)

# Pour OpenGL : trouver la bibliothèque OpenGL et lier à l'exécutable
find_package(OpenGL REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE OpenGL::GL)

cmake_minimum_required(VERSION 3.15)
project(XSmall-HMI-Player)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к SFML
set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

# Директории с исходниками
include_directories(include)
include_directories(${SFML_INCLUDE_DIR})

# Явно перечисляем ВСЕ файлы для компиляции
set(SOURCES
    src/main.cpp
    src/VariableDatabase.cpp
    src/VisualObject.cpp
    src/Rectangle.cpp
    src/Text.cpp
    src/Line.cpp
    src/Polyline.cpp
    src/InputField.cpp
    src/Button.cpp
    src/Image.cpp
    src/XmlLoader.cpp
    src/HmiPlayer.cpp
    src/HistoryGraph.cpp
)

add_executable(HMI_Player ${SOURCES})

target_link_libraries(HMI_Player sfml-graphics sfml-window sfml-system)

install(TARGETS HMI_Player DESTINATION bin)

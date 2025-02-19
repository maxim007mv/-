cmake_minimum_required(VERSION 3.12)
project(travel_planner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим необходимые библиотеки
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# Добавляем директории с заголовочными файлами
include_directories(${CMAKE_SOURCE_DIR}/core/include)

# Собираем основное приложение
add_executable(travel_planner 
    core/src/main.cpp
)

# Линкуем библиотеки
target_link_libraries(travel_planner 
    PRIVATE CURL::libcurl
    PRIVATE nlohmann_json::nlohmann_json
)

# Добавляем определения для компилятора
target_compile_definitions(travel_planner 
    PRIVATE CURL_STATICLIB
) 
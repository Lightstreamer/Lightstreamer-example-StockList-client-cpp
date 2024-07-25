cmake_minimum_required(VERSION 3.10)

project(StockListDemo VERSION 1.0)

# the full path of the Lighstreamer C++ static library with debug symbols
# set(LIGHTSTREAMER_BASE_DIR "~/git/lib-client-haxe/bin/cpp/mac/static-debug")
if (NOT LIGHTSTREAMER_BASE_DIR)
    message(FATAL_ERROR "LIGHTSTREAMER_BASE_DIR is undefined")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(StockListDemo src/stock_list_demo.cpp)

target_include_directories(StockListDemo PRIVATE 
  "${LIGHTSTREAMER_BASE_DIR}/include"
)

target_link_directories(StockListDemo PRIVATE 
  "${LIGHTSTREAMER_BASE_DIR}"
)

target_link_libraries(StockListDemo PRIVATE lightstreamer_clientd)

if (APPLE)
    find_library(LS_APPLE_SECURITY Security)
    find_library(LS_APPLE_CORE CoreFoundation)
    target_link_libraries(StockListDemo PRIVATE ${LS_APPLE_SECURITY} ${LS_APPLE_CORE})
endif()
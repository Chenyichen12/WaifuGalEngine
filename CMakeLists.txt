cmake_minimum_required(VERSION 3.20)

project(WaifuGalEngine LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
add_subdirectory(engine)
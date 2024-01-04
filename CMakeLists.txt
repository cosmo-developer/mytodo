cmake_minimum_required(VERSION 3.10)
project(mytodo)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM4 REQUIRED gtkmm-4.0)
pkg_check_modules(LIBRSVG REQUIRED librsvg-2.0)

include_directories(${GTKMM4_INCLUDE_DIRS} ${LIBRSVG_INCLUDE_DIRS} "include")

add_executable(mytodo "./src/TodoMainMediaQueryProcessors.cc" "./src/main.cc" "./src/TodoMainWindow.cc" "./src/ImageButton.cc" "./src/UButton.cc")

target_link_libraries(mytodo ${GTKMM4_LIBRARIES} ${LIBRSVG_LIBRARIES})

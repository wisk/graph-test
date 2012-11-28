cmake_minimum_required(VERSION 2.8)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
project(GraphTest)

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${Boost_INCLUDE_DIRS})

set(INCROOT ${CMAKE_SOURCE_DIR}/inc)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src)
set(UIROOT  ${CMAKE_SOURCE_DIR}/ui )

include_directories(${INCROOT})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(OGDF REQUIRED)

include_directories(${OGDF_INCLUDE_DIRS})
message(${OGDF_INCLUDE_DIRS})

set(INC
  ${INCROOT}/Arrow.hpp
  ${INCROOT}/BasicBlockItem.hpp
  ${INCROOT}/ControlFlowGraphScene.hpp
  ${INCROOT}/ControlFlowGraphView.hpp
  ${INCROOT}/dialog.hpp
  ${INCROOT}/graph.hpp
)

set(SRC
  ${SRCROOT}/Arrow.cpp
  ${SRCROOT}/BasicBlockItem.cpp
  ${SRCROOT}/ControlFlowGraphScene.cpp
  ${SRCROOT}/ControlFlowGraphView.cpp
  ${SRCROOT}/dialog.cpp
  ${SRCROOT}/graph.cpp
  ${SRCROOT}/main.cpp
)

set(MOCINC
  ${INCROOT}/dialog.hpp
  ${INCROOT}/BasicBlockItem.hpp
  ${INCROOT}/ControlFlowGraphScene.hpp
  ${INCROOT}/ControlFlowGraphView.hpp
)

set(UI
  ${UIROOT}/graph.ui
)

qt4_wrap_cpp(MOC ${MOCINC})
qt4_wrap_ui(UIINC ${UI})

#if(WIN32)
#  set(GUI_TYPE WIN32)
#endif()

add_executable(graph-test ${GUI_TYPE}
  ${INC}
  ${SRC}
  ${MOC}
  ${UIINC}
)

target_link_libraries(graph-test ${QT_LIBRARIES} ${OGDF_LIBRARIES})

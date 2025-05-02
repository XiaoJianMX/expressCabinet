cmake_minimum_required(VERSION 3.10)

project(untitled LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)
if(ANDROID)
  add_library(expressCabinet SHARED
      cun/cun.cpp
      ji/ji.cpp
      ji/jidialog.cpp
      main/main.cpp
      main/mainwindow.cpp
      qu/qu.cpp
      cun/cun.h
      ji/ji.h
      ji/jidialog.h
      main/mainwindow.h
      qu/qu.h
      cun/cun.ui
      ji/ji.ui
      ji/jidialog.ui
      main/mainwindow.ui
      qu/qu.ui
  )
else()
  add_executable(expressCabinet
      cun/cun.cpp
      ji/ji.cpp
      ji/jidialog.cpp
      main/main.cpp
      main/mainwindow.cpp
      qu/qu.cpp
      cun/cun.h
      ji/ji.h
      ji/jidialog.h
      main/mainwindow.h
      qu/qu.h
      cun/cun.ui
      ji/ji.ui
      ji/jidialog.ui
      main/mainwindow.ui
      deliveryman/deliveryman.cpp
      deliveryman/deliveryman.h
      deliveryman/deliveryman.ui
      deliveryman/deliverymanopt.cpp
      deliveryman/deliverymanopt.h
      deliveryman/deliverymanopt.ui
      qu/qu.ui
      icons.qrc
  )
endif()

target_link_libraries(expressCabinet PRIVATE Qt5::Widgets)
target_link_libraries(expressCabinet PRIVATE Qt5::Sql)
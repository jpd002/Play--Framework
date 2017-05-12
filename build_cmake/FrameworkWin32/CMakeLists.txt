cmake_minimum_required(VERSION 2.8)
project(Framework_Win32)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None Debug Release"
		FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
	add_definitions(-D_UNICODE -DUNICODE)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_LIB)
endif (WIN32)

if (NOT TARGET Boost::boost)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/boost-cmake
		${CMAKE_CURRENT_BINARY_DIR}/boost-cmake
	)
endif()

include_directories(../../include)

set(SRC_FILES
	../../src/directinput/Device.cpp 
	../../src/directinput/Joystick.cpp
	../../src/directinput/Keyboard.cpp
	../../src/directinput/Manager.cpp
	../../src/win32/AcceleratorTableGenerator.cpp
	../../src/win32/ActiveXHost.cpp
	../../src/win32/Button.cpp
	../../src/win32/ClientDeviceContext.cpp
	../../src/win32/ColumnTreeView.cpp
	../../src/win32/ComboBox.cpp
	../../src/win32/ComStreamAdapter.cpp
	../../src/win32/CustomDrawn.cpp
	../../src/win32/DefaultFonts.cpp
	../../src/win32/DefaultWndClass.cpp
	../../src/win32/DeviceContext.cpp
	../../src/win32/Dialog.cpp
	../../src/win32/DpiUtils.cpp
	../../src/win32/Edit.cpp
	../../src/win32/FileDialog.cpp
	../../src/win32/FindFile.cpp
	../../src/win32/Font.cpp
	../../src/win32/Header.cpp
	../../src/win32/HorizontalSplitter.cpp
	../../src/win32/InputBox.cpp
	../../src/win32/LayoutWindow.cpp
	../../src/win32/ListBox.cpp
	../../src/win32/ListView.cpp
	../../src/win32/MDIChild.cpp
	../../src/win32/MDIClient.cpp
	../../src/win32/MDIFrame.cpp
	../../src/win32/MemoryDeviceContext.cpp
	../../src/win32/MenuItem.cpp
	../../src/win32/ModalWindow.cpp
	../../src/win32/Progress.cpp
	../../src/win32/PropertyGrid.cpp
	../../src/win32/PropertyGridEdit.cpp
	../../src/win32/PropertyGridListBox.cpp
	../../src/win32/Rect.cpp
	../../src/win32/RichTextEdit.cpp
	../../src/win32/ScrollBar.cpp
	../../src/win32/Splitter.cpp
	../../src/win32/Static.cpp
	../../src/win32/StatusBar.cpp
	../../src/win32/Tab.cpp
	../../src/win32/TaskBarList.cpp
	../../src/win32/ToolBar.cpp
	../../src/win32/ToolTip.cpp
	../../src/win32/TrayIcon.cpp
	../../src/win32/TrayIconServer.cpp
	../../src/win32/TreeView.cpp
	../../src/win32/VerticalSplitter.cpp
	../../src/win32/WebBrowser.cpp
	../../src/win32/Window.cpp
)

add_library(Framework_Win32 ${SRC_FILES})
target_link_libraries(Framework_Win32 PUBLIC Boost::boost)
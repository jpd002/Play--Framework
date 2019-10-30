cmake_minimum_required(VERSION 2.8)
project(Framework_Win32)

include(../Framework_Common.cmake)

set(SRC_FILES
	../../include/direct3d9/D3D9TextureUtils.h
	../../src/directinput/Device.cpp 
	../../include/directinput/Device.h
	../../src/directinput/Joystick.cpp
	../../include/directinput/Joystick.h
	../../src/directinput/Keyboard.cpp
	../../include/directinput/Keyboard.h
	../../src/directinput/Manager.cpp
	../../include/directinput/Manager.h
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
target_link_libraries(Framework_Win32 PUBLIC comctl32)
target_include_directories(Framework_Win32 PUBLIC ${FRAMEWORK_INCLUDE_DIR})

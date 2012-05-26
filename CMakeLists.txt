#
# KDevelop-WebBrowser/CMakeLists.txt
# Builds the KDevelop WebBrowser plugin
#

project (KDevelopWebBrowser)
	set (QT_USE_QTNETWORK true)
	set (QT_USE_QTWEBKIT true)
	
	find_package (KDE4)
	find_package (KDevPlatform)
	
	include (${QT_USE_FILE})
	include_directories (${KDEVPLATFORM_INCLUDE_DIR})
	include_directories (${KDevelopWebBrowser_BINARY_DIR})
	include_directories (${QT_QTNETWORK_INCLUDE_DIR})
	include_directories (${QT_QTWEBKIT_INCLUDE_DIR})
	
	set (KDevelopWebBrowser_HEADERS_MOC
		${KDevelopWebBrowser_SOURCE_DIR}/WebBrowserPlugin.h
		${KDevelopWebBrowser_SOURCE_DIR}/WebBrowserView.h
	)

	set (KDevelopWebBrowser_HEADERS
	)

	set (KDevelopWebBrowser_SOURCES
		${KDevelopWebBrowser_SOURCE_DIR}/WebBrowserPlugin.cpp
		${KDevelopWebBrowser_SOURCE_DIR}/WebBrowserView.cpp
	)

	kde4_add_plugin (KDevelopWebBrowser
		${KDevelopWebBrowser_HEADERS} ${KDevelopWebBrowser_SOURCES}
		${KDevelopWebBrowser_HEADERS_MOC}
	)

	target_link_libraries (KDevelopWebBrowser
		${KDEVPLATFORM_INTERFACES_LIBRARIES}
		${KDEVPLATFORM_PROJECT_LIBRARIES}
		
		${QT_QTWEBKIT_LIBRARIES}
	)

	install (TARGETS KDevelopWebBrowser DESTINATION ${PLUGIN_INSTALL_DIR})
	install (FILES KDevelopWebBrowser.desktop DESTINATION ${SERVICES_INSTALL_DIR})
	
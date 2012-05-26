//
/// \file KDevelop-WebBrowser/WebBrowserView.h
/// \brief Main view for the plugin
//
// Copyright (C) 2012 Kenneth Perry (thothonegan@gmail.com)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//

#ifndef KDEVELOPWEBBROWSER_WEBBROWSERVIEW_H
#define KDEVELOPWEBBROWSER_WEBBROWSERVIEW_H

#include <QSslError>
#include <QWebView>
#include <QWidget>

class KLineEdit;
class WebBrowserPlugin;

class WebBrowserView : public QWidget
{
	Q_OBJECT
	public:
		//
		/// \brief Create the view
		//
		WebBrowserView (WebBrowserPlugin* plugin, QWidget* parent);
		
		//
		/// \brief List of actions for the toolbar
		//
		QList<QAction*> toolBarActions (void) const;
		
	private slots:
		//
		/// \brief Back pressed
		//
		void slotBackPressed (void);
		
		//
		/// \brief Forward pressed
		//
		void slotForwardPressed (void);
		
		//
		/// \brief Refresh pressed
		//
		void slotRefreshPressed (void);
		
		//
		/// \brief Go to the currently typed url
		//
		void slotGotoCurrentURL();
		
		//
		/// \brief The URL changed
		//
		void slotURLChanged (QUrl url);
		
		//
		/// \brief SSL errors occurred
		//
		void slotSSLError (QNetworkReply* reply,QList<QSslError> errors);
	private:
		//
		/// \brief Setup the toolbar actions
		//
		void setupActions (void);
		
		//
		/// \brief Toolbar actions
		//
		QList<QAction*> m_toolbarActions;
		
		//
		/// \brief The plugin we're attached to
		//
		WebBrowserPlugin* m_plugin;
		
		//
		/// \brief The main webbrowser node
		//
		QWebView* m_webView;
		
		//
		/// \brief The URL bar
		//
		KLineEdit* m_urlBar;
};

#endif // KDEVELOPWEBBROWSER_WEBBROWSERVIEW_H

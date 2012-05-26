//
/// \file KDevelop-WebBrowser/WebBrowserPlugin.h
/// \brief Plugin for a simple toolbar webbrowser in KDevelop
//
// Copyright (C) 2012  Kenneth Perry (thothonegan@gmail.com)
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

#ifndef KDEVELOPWEBBROWSER_WEBBROWSERPLUGIN_H
#define KDEVELOPWEBBROWSER_WEBBROWSERPLUGIN_H

#include <interfaces/iplugin.h>

#include <QVariant>

class WebBrowserPlugin : public KDevelop::IPlugin
{
	Q_OBJECT
	public:
		//
		/// \brief Create the plugin
		//
		WebBrowserPlugin (QObject* parent, const QVariantList& args = QVariantList());
		
		//
		/// \brief Destroy the plugin
		//
		virtual ~WebBrowserPlugin (void);
		
		//
		/// \brief Unload the plugin
		//
		virtual void unload (void);
		
	private slots:
		//
		/// \brief Init the plugin
		//
		void init (void);
		
		
	private:
		//
		/// \brief The factory used to create stuff
		//
		class WebBrowserViewFactory* m_factory;
};

#endif // KDEVELOPWEBBROWSER_WEBBROWSERPLUGIN_H

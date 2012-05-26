//
/// \file KDevelop-WebBrowser/WebBrowserPlugin.cpp
/// \brief Plugin for a simple webbrowser in KDevelop
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

#include "WebBrowserPlugin.h"

#include <kaboutdata.h>
#include <kpluginfactory.h>
#include <kpluginloader.h>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>

#include "WebBrowserView.h"

K_PLUGIN_FACTORY (WebBrowserFactory, registerPlugin<WebBrowserPlugin>(); )
K_EXPORT_PLUGIN (WebBrowserFactory (KAboutData ("WebBrowser", "WebBrowser",
	ki18n("WebBrowser Plugin"), "1.0", ki18n("Simple webbrowser for KDevelop"),
	KAboutData ::License_GPL)))

class WebBrowserViewFactory : public KDevelop::IToolViewFactory
{
	public:
		WebBrowserViewFactory (WebBrowserPlugin* plugin)
		: m_plugin (plugin)
		{}
		
		virtual QWidget* create (QWidget* parent = NULL)
		{ return new WebBrowserView (m_plugin, parent); }
		
		QList<QAction*> toolBarActions (QWidget* w) const
		{
			WebBrowserView* view = qobject_cast<WebBrowserView*> (w);
			if (view)
				return view->toolBarActions();
			
			return KDevelop::IToolViewFactory::toolBarActions(w);
		}
		
		virtual Qt::DockWidgetArea defaultPosition (void)
		{ return Qt::RightDockWidgetArea; }
		
		virtual QString id() const
		{ return "com.hackerguild.KDevelop.WebBrowser"; }
		
	private:
		WebBrowserPlugin* m_plugin;
};

WebBrowserPlugin::WebBrowserPlugin (QObject* parent, const QVariantList& args)
: IPlugin(WebBrowserFactory::componentData(), parent)
{
	init();
}

WebBrowserPlugin::~WebBrowserPlugin (void)
{}

void WebBrowserPlugin::unload (void)
{}

// --- private slots ---

void WebBrowserPlugin::init (void)
{
	m_factory = new WebBrowserViewFactory (this);
	core()->uiController()->addToolView("WebBrowser", m_factory);
}

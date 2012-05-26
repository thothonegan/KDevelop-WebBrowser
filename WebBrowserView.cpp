//
/// \file KDevelop-WebBrowser/WebBrowserView.cpp
/// \brief Main view for the plugin
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

#include "WebBrowserView.h"

#include <kaction.h>
#include <kmessagebox.h>
#include <klineedit.h>
#include <klocale.h>
#include <kurlcompletion.h>

#include <QNetworkReply>
#include <QSslError>
#include <QVBoxLayout>
#include <QWidgetAction>

WebBrowserView::WebBrowserView (WebBrowserPlugin* plugin, QWidget* parent)
: QWidget(parent), m_plugin (plugin), m_webView (NULL), m_urlBar (NULL)
{
	setObjectName ("WebBrowser");
	setWindowIcon(SmallIcon("internet-web-browser"));
	setWindowTitle(i18n("WebBrowser"));
	setWhatsThis(i18n("WebBrowser"));
	
	m_webView = new QWebView;
	
	connect (m_webView, SIGNAL(urlChanged(QUrl)), this, SLOT(slotURLChanged(QUrl)));
	connect (m_webView->page()->networkAccessManager(),
		SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
		this, SLOT(slotSSLError(QNetworkReply*,QList<QSslError>))
	);
	
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget (m_webView);
	setLayout (layout);
	
	m_webView->load (QUrl("http://www.google.com/"));
	
	setupActions();
}

QList<QAction*> WebBrowserView::toolBarActions(void ) const
{ return m_toolbarActions; }

// --- private slots ---

void WebBrowserView::slotBackPressed (void)
{ m_webView->back(); }

void WebBrowserView::slotForwardPressed (void)
{ m_webView->forward(); }

void WebBrowserView::slotRefreshPressed (void)
{ m_webView->reload(); }

void WebBrowserView::slotGotoCurrentURL (void)
{
	QString url = m_urlBar->text();
	
	if (!url.contains("://"))
		url = "http://" + url;
	
	m_webView->load(QUrl (url));
}

void WebBrowserView::slotURLChanged(QUrl url)
{
	m_urlBar->setText(url.toString());
}

void WebBrowserView::slotSSLError(QNetworkReply* reply, QList< QSslError > errors)
{
#if 0
	foreach (QSslError e, errors)
	{
		KMessageBox::messageBox(this, KMessageBox::Information, "SSL Error - Ignoring", e.errorString());
	}
#endif
	reply->ignoreSslErrors();
}

// --- private ---

void WebBrowserView::setupActions(void )
{
	#define BUTTON(name, icon, slot) \
	{ \
		KAction* action = new KAction (this); \
		action->setShortcutContext(Qt::WidgetWithChildrenShortcut); \
		action->setText (i18n (name)); \
		action->setIcon (icon); \
		connect (action, SIGNAL(triggered()), this, slot); \
		m_toolbarActions.push_back (action); \
	}
	
	BUTTON("Back", KIcon ("go-previous"), SLOT(slotBackPressed()));
	BUTTON("Forward", KIcon ("go-next"), SLOT(slotForwardPressed()));
	BUTTON("Refresh", KIcon ("view-refresh"), SLOT(slotRefreshPressed()));
	
	
	// URL bar
	m_urlBar = new KLineEdit;
	m_urlBar->setClearButtonShown(true);
	
	QWidgetAction* urlBarAction = new QWidgetAction (this);
	urlBarAction->setDefaultWidget(m_urlBar);
	connect (m_urlBar, SIGNAL(returnPressed(QString)), this, SLOT(slotGotoCurrentURL()));
	m_toolbarActions.push_back(urlBarAction);
	
	#undef BUTTON
	
	
}

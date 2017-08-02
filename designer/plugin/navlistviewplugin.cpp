#include "../src/navlistview.h"
#include "navlistviewplugin.h"

#include <QtPlugin>

NavListViewPlugin::NavListViewPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void NavListViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavListViewPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavListViewPlugin::createWidget(QWidget *parent)
{
    return new NavListView(parent);
}

QString NavListViewPlugin::name() const
{
    return QLatin1String("NavListView");
}

QString NavListViewPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavListViewPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/navlistview.png"));
}

QString NavListViewPlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavListViewPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavListViewPlugin::isContainer() const
{
    return false;
}

QString NavListViewPlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavListView\" name=\"navListView\">\n</widget>\n");
}

QString NavListViewPlugin::includeFile() const
{
    return QLatin1String("navlistview.h");
}


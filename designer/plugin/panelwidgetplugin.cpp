#include "../src/panelwidget.h"
#include "panelwidgetplugin.h"

#include <QtPlugin>

PanelWidgetPlugin::PanelWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void PanelWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool PanelWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PanelWidgetPlugin::createWidget(QWidget *parent)
{
    return new PanelWidget(parent);
}

QString PanelWidgetPlugin::name() const
{
    return QLatin1String("PanelWidget");
}

QString PanelWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon PanelWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/panelwidget.png"));
}

QString PanelWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString PanelWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool PanelWidgetPlugin::isContainer() const
{
    return true;
}

QString PanelWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"PanelWidget\" name=\"panelWidget\">\n</widget>\n");
}

QString PanelWidgetPlugin::includeFile() const
{
    return QLatin1String("panelwidget.h");
}


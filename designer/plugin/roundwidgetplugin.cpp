#include "../src/roundwidget.h"
#include "roundwidgetplugin.h"

#include <QtPlugin>

RoundWidgetPlugin::RoundWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void RoundWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RoundWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RoundWidgetPlugin::createWidget(QWidget *parent)
{
    return new RoundWidget(parent);
}

QString RoundWidgetPlugin::name() const
{
    return QLatin1String("RoundWidget");
}

QString RoundWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RoundWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/roundwidget.png"));
}

QString RoundWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RoundWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RoundWidgetPlugin::isContainer() const
{
    return false;
}

QString RoundWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"RoundWidget\" name=\"roundWidget\">\n</widget>\n");
}

QString RoundWidgetPlugin::includeFile() const
{
    return QLatin1String("roundwidget.h");
}


#include "../src/navprogressbar.h"
#include "navprogressbarplugin.h"

#include <QtPlugin>

NavProgressBarPlugin::NavProgressBarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void NavProgressBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavProgressBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavProgressBarPlugin::createWidget(QWidget *parent)
{
    return new NavProgressBar(parent);
}

QString NavProgressBarPlugin::name() const
{
    return QLatin1String("NavProgressBar");
}

QString NavProgressBarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavProgressBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/navprogressbar.png"));
}

QString NavProgressBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavProgressBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavProgressBarPlugin::isContainer() const
{
    return false;
}

QString NavProgressBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavProgressBar\" name=\"navProgressBar\">\n</widget>\n");
}

QString NavProgressBarPlugin::includeFile() const
{
    return QLatin1String("navprogressbar.h");
}


#include "../src/progressbarpercent.h"
#include "progressbarpercentplugin.h"

#include <QtPlugin>

ProgressBarPercentPlugin::ProgressBarPercentPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ProgressBarPercentPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressBarPercentPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressBarPercentPlugin::createWidget(QWidget *parent)
{
    return new ProgressBarPercent(parent);
}

QString ProgressBarPercentPlugin::name() const
{
    return QLatin1String("ProgressBarPercent");
}

QString ProgressBarPercentPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressBarPercentPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressbarpercent.png"));
}

QString ProgressBarPercentPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressBarPercentPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressBarPercentPlugin::isContainer() const
{
    return false;
}

QString ProgressBarPercentPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressBarPercent\" name=\"progressBarPercent\">\n</widget>\n");
}

QString ProgressBarPercentPlugin::includeFile() const
{
    return QLatin1String("progressbarpercent.h");
}


#include "../src/progressbarround.h"
#include "progressbarroundplugin.h"

#include <QtPlugin>

ProgressBarRoundPlugin::ProgressBarRoundPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ProgressBarRoundPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressBarRoundPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressBarRoundPlugin::createWidget(QWidget *parent)
{
    return new ProgressBarRound(parent);
}

QString ProgressBarRoundPlugin::name() const
{
    return QLatin1String("ProgressBarRound");
}

QString ProgressBarRoundPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressBarRoundPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressbarround.png"));
}

QString ProgressBarRoundPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressBarRoundPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressBarRoundPlugin::isContainer() const
{
    return false;
}

QString ProgressBarRoundPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressBarRound\" name=\"progressBarRound\">\n</widget>\n");
}

QString ProgressBarRoundPlugin::includeFile() const
{
    return QLatin1String("progressbarround.h");
}


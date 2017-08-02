#include "../src/progressbarwait.h"
#include "progressbarwaitplugin.h"

#include <QtPlugin>

ProgressBarWaitPlugin::ProgressBarWaitPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ProgressBarWaitPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressBarWaitPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressBarWaitPlugin::createWidget(QWidget *parent)
{
    return new ProgressBarWait(parent);
}

QString ProgressBarWaitPlugin::name() const
{
    return QLatin1String("ProgressBarWait");
}

QString ProgressBarWaitPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressBarWaitPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressbarwait.png"));
}

QString ProgressBarWaitPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressBarWaitPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressBarWaitPlugin::isContainer() const
{
    return false;
}

QString ProgressBarWaitPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressBarWait\" name=\"progressBarWait\">\n</widget>\n");
}

QString ProgressBarWaitPlugin::includeFile() const
{
    return QLatin1String("progressbarwait.h");
}


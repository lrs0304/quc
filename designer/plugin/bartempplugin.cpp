#include "../src/bartemp.h"
#include "bartempplugin.h"

#include <QtPlugin>

BarTempPlugin::BarTempPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void BarTempPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BarTempPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BarTempPlugin::createWidget(QWidget *parent)
{
    return new BarTemp(parent);
}

QString BarTempPlugin::name() const
{
    return QLatin1String("BarTemp");
}

QString BarTempPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon BarTempPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/bartemp.png"));
}

QString BarTempPlugin::toolTip() const
{
    return QLatin1String("");
}

QString BarTempPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BarTempPlugin::isContainer() const
{
    return false;
}

QString BarTempPlugin::domXml() const
{
    return QLatin1String("<widget class=\"BarTemp\" name=\"barTemp\">\n</widget>\n");
}

QString BarTempPlugin::includeFile() const
{
    return QLatin1String("bartemp.h");
}


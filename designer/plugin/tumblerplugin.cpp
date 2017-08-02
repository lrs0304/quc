#include "../src/tumbler.h"
#include "tumblerplugin.h"

#include <QtPlugin>

TumblerPlugin::TumblerPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void TumblerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TumblerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TumblerPlugin::createWidget(QWidget *parent)
{
    return new Tumbler(parent);
}

QString TumblerPlugin::name() const
{
    return QLatin1String("Tumbler");
}

QString TumblerPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon TumblerPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/tumbler.png"));
}

QString TumblerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString TumblerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TumblerPlugin::isContainer() const
{
    return false;
}

QString TumblerPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Tumbler\" name=\"tumbler\">\n</widget>\n");
}

QString TumblerPlugin::includeFile() const
{
    return QLatin1String("tumbler.h");
}


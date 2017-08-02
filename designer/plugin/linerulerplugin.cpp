#include "../src/lineruler.h"
#include "linerulerplugin.h"

#include <QtPlugin>

LineRulerPlugin::LineRulerPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LineRulerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LineRulerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LineRulerPlugin::createWidget(QWidget *parent)
{
    return new LineRuler(parent);
}

QString LineRulerPlugin::name() const
{
    return QLatin1String("LineRuler");
}

QString LineRulerPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon LineRulerPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/lineruler.png"));
}

QString LineRulerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LineRulerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LineRulerPlugin::isContainer() const
{
    return false;
}

QString LineRulerPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LineRuler\" name=\"lineRuler\">\n</widget>\n");
}

QString LineRulerPlugin::includeFile() const
{
    return QLatin1String("lineruler.h");
}


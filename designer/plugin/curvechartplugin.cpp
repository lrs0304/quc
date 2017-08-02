#include "../src/curvechart.h"
#include "curvechartplugin.h"

#include <QtPlugin>

CurveChartPlugin::CurveChartPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CurveChartPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CurveChartPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CurveChartPlugin::createWidget(QWidget *parent)
{
    return new CurveChart(parent);
}

QString CurveChartPlugin::name() const
{
    return QLatin1String("CurveChart");
}

QString CurveChartPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon CurveChartPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/curvechart.png"));
}

QString CurveChartPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CurveChartPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CurveChartPlugin::isContainer() const
{
    return false;
}

QString CurveChartPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CurveChart\" name=\"curveChart\">\n</widget>\n");
}

QString CurveChartPlugin::includeFile() const
{
    return QLatin1String("curvechart.h");
}


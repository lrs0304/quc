#include "../src/cpumemorylabel.h"
#include "cpumemorylabelplugin.h"

#include <QtPlugin>

CpuMemoryLabelPlugin::CpuMemoryLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CpuMemoryLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CpuMemoryLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CpuMemoryLabelPlugin::createWidget(QWidget *parent)
{
    return new CpuMemoryLabel(parent);
}

QString CpuMemoryLabelPlugin::name() const
{
    return QLatin1String("CpuMemoryLabel");
}

QString CpuMemoryLabelPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon CpuMemoryLabelPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/cpumemorylabel.png"));
}

QString CpuMemoryLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CpuMemoryLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CpuMemoryLabelPlugin::isContainer() const
{
    return false;
}

QString CpuMemoryLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CpuMemoryLabel\" name=\"cpuMemorylabel\">\n</widget>\n");
}

QString CpuMemoryLabelPlugin::includeFile() const
{
    return QLatin1String("cpumemorylabel.h");
}


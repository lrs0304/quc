#include "../src/navlabel.h"
#include "navlabelplugin.h"

#include <QtPlugin>

NavLabelPlugin::NavLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void NavLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavLabelPlugin::createWidget(QWidget *parent)
{
    return new NavLabel(parent);
}

QString NavLabelPlugin::name() const
{
    return QLatin1String("NavLabel");
}

QString NavLabelPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavLabelPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/navlabel.png"));
}

QString NavLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavLabelPlugin::isContainer() const
{
    return false;
}

QString NavLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavLabel\" name=\"navLabel\">\n</widget>\n");
}

QString NavLabelPlugin::includeFile() const
{
    return QLatin1String("navlabel.h");
}


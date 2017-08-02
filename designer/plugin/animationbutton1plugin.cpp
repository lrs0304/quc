#include "../src/animationbutton1.h"
#include "animationbutton1plugin.h"

#include <QtPlugin>

AnimationButton1Plugin::AnimationButton1Plugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void AnimationButton1Plugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool AnimationButton1Plugin::isInitialized() const
{
    return m_initialized;
}

QWidget *AnimationButton1Plugin::createWidget(QWidget *parent)
{
    return new AnimationButton1(parent);
}

QString AnimationButton1Plugin::name() const
{
    return QLatin1String("AnimationButton1");
}

QString AnimationButton1Plugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon AnimationButton1Plugin::icon() const
{
    return QIcon(QLatin1String(":/ico/animationbutton1.png"));
}

QString AnimationButton1Plugin::toolTip() const
{
    return QLatin1String("");
}

QString AnimationButton1Plugin::whatsThis() const
{
    return QLatin1String("");
}

bool AnimationButton1Plugin::isContainer() const
{
    return false;
}

QString AnimationButton1Plugin::domXml() const
{
    return QLatin1String("<widget class=\"AnimationButton1\" name=\"animationButton1\">\n</widget>\n");
}

QString AnimationButton1Plugin::includeFile() const
{
    return QLatin1String("animationbutton1.h");
}


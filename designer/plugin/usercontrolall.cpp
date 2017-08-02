#include "gaugearcplugin.h"
#include "gaugecarplugin.h"
#include "gaugeclockplugin.h"
#include "gaugecompassplugin.h"
#include "gaugedialplugin.h"
#include "gaugeprogressbarplugin.h"
#include "gaugerangeplugin.h"
#include "gaugeroundplugin.h"
#include "gaugesimpleplugin.h"
#include "gaugewatchplugin.h"
#include "gaugenetplugin.h"
#include "gaugespeedplugin.h"

#include "sliderrangeplugin.h"
#include "sliderbarplugin.h"
#include "sliderrulerplugin.h"
#include "linerulerplugin.h"
#include "barrulerplugin.h"
#include "barscaleplugin.h"
#include "bartempplugin.h"
#include "barvolumeplugin.h"

#include "datetimelcdplugin.h"
#include "lcdnumberplugin.h"
#include "lednumberplugin.h"
#include "ledtextplugin.h"

#include "batteryplugin.h"
#include "tumblerplugin.h"
#include "lightbuttonplugin.h"
#include "switchbuttonplugin.h"
#include "curvechartplugin.h"
#include "devicesizetableplugin.h"
#include "cpumemorylabelplugin.h"

#include "animationbutton1plugin.h"
#include "animationbutton2plugin.h"
#include "roundcircleplugin.h"
#include "roundwidgetplugin.h"
#include "colorcomboboxplugin.h"
#include "textmovewidgetplugin.h"
#include "panelwidgetplugin.h"

#include "imagecalendarplugin.h"
#include "imageclockplugin.h"
#include "imagepilotplugin.h"
#include "imagepowerplugin.h"
#include "imageswitchplugin.h"
#include "imageviewplugin.h"

#include "progressbarcolorplugin.h"
#include "progressbarpercentplugin.h"
#include "progressbarroundplugin.h"
#include "progressbarwaitplugin.h"

#include "navlabelplugin.h"
#include "navlistviewplugin.h"
#include "navprogressbarplugin.h"

#include "wavebarplugin.h"
#include "wavedoubleplugin.h"
#include "wavelineplugin.h"
#include "waveplotplugin.h"
#include "verifiedcodeplugin.h"
#include "adswidgetplugin.h"
#include "iconeditorplugin.h"

#include "usercontrolall.h"

UserControlAll::UserControlAll(QObject *parent)
    : QObject(parent)
{
    widgets.append(new GaugeArcPlugin(this));
    widgets.append(new GaugeCarPlugin(this));
    widgets.append(new GaugeClockPlugin(this));
    widgets.append(new GaugeCompassPlugin(this));
    widgets.append(new GaugeDialPlugin(this));
    widgets.append(new GaugeProgressBarPlugin(this));
    widgets.append(new GaugeRoundPlugin(this));
    widgets.append(new GaugeRangePlugin(this));
    widgets.append(new GaugeSimplePlugin(this));
    widgets.append(new GaugeWatchPlugin(this));
    widgets.append(new GaugeNetPlugin(this));
    widgets.append(new GaugeSpeedPlugin(this));

    widgets.append(new SliderRangePlugin(this));
    widgets.append(new SliderBarPlugin(this));
    widgets.append(new SliderRulerPlugin(this));
    widgets.append(new LineRulerPlugin(this));
    widgets.append(new BarRulerPlugin(this));
    widgets.append(new BarScalePlugin(this));
    widgets.append(new BarTempPlugin(this));
    widgets.append(new BarVolumePlugin(this));

    widgets.append(new DateTimeLcdPlugin(this));
    widgets.append(new LcdNumberPlugin(this));
    widgets.append(new LedNumberPlugin(this));
    widgets.append(new LedTextPlugin(this));

    widgets.append(new BatteryPlugin(this));
    widgets.append(new TumblerPlugin(this));
    widgets.append(new LightButtonPlugin(this));
    widgets.append(new SwitchButtonPlugin(this));
    widgets.append(new CurveChartPlugin(this));
    widgets.append(new DeviceSizeTablePlugin(this));
    widgets.append(new CpuMemoryLabelPlugin(this));

    widgets.append(new AnimationButton1Plugin(this));
    widgets.append(new AnimationButton2Plugin(this));
    widgets.append(new RoundCirclePlugin(this));
    widgets.append(new RoundWidgetPlugin(this));
    widgets.append(new ColorComboBoxPlugin(this));
    widgets.append(new TextMoveWidgetPlugin(this));
    widgets.append(new PanelWidgetPlugin(this));

    widgets.append(new ImageCalendarPlugin(this));
    widgets.append(new ImageClockPlugin(this));
    widgets.append(new ImagePilotPlugin(this));
    widgets.append(new ImagePowerPlugin(this));
    widgets.append(new ImageSwitchPlugin(this));
    widgets.append(new ImageViewPlugin(this));

    widgets.append(new ProgressBarColorPlugin(this));
    widgets.append(new ProgressBarPercentPlugin(this));
    widgets.append(new ProgressBarRoundPlugin(this));
    widgets.append(new ProgressBarWaitPlugin(this));

    widgets.append(new NavLabelPlugin(this));
    widgets.append(new NavListViewPlugin(this));
    widgets.append(new NavProgressBarPlugin(this));

    widgets.append(new WaveBarPlugin(this));
    widgets.append(new WaveDoublePlugin(this));
    widgets.append(new WaveLinePlugin(this));
    widgets.append(new WavePlotPlugin(this));
    widgets.append(new VerifiedCodePlugin(this));
    widgets.append(new AdsWidgetPlugin(this));
    widgets.append(new IconEditorPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> UserControlAll::customWidgets() const
{
    return widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(usercontrolallplugin, UserControlAll)
#endif // QT_VERSION < 0x050000

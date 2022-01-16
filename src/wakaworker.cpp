#include "wakaworker.h"

#include <QDir>
#include <QDirIterator>
#include <QProcess>
#include <waka_plugin.h>

using namespace Wakatime::Constants;

namespace Wakatime::Internal
{
    WakaWorker::WakaWorker(QObject *parent) : QObject(parent)
    {
    }

    void WakaWorker::startHearBeat(const QString &file, bool isSave)
    {
        qDebug() << file;
        if (_wakaCliExecutablePath.isEmpty())
        {
            // get the executable path
            const auto dir = WakaPlugin::getWakaCLILocation();
            auto iterator = QDirIterator(dir.absolutePath());
            while (iterator.hasNext())
            {
                const auto f = iterator.next();
                if (iterator.fileInfo().isFile() && iterator.fileName().contains("wakatime-cli"))
                {
                    _wakaCliExecutablePath = f;
                }
            }
        }

        const auto now = QTime::currentTime();
        if (now < _previous_heartbeat.addSecs(120) && !isSave)
        {
            // do nothing if not passed 2 minutes
            return;
        }
        _previous_heartbeat = now;

        const static auto wakaVersion = u"QtCreator/%1 QtCreator-wakatime/%2"_qs.arg("6").arg(WAKATIME_PLUGIN_VERSION);
        QStringList cmd = { "--plugin", wakaVersion, "--entity", file };
        if (isSave)
            cmd.append(u"--write"_qs);

        emit promptMessage("Command: " + _wakaCliExecutablePath + " " + cmd.join(" "));

        QProcess process;
        process.start(_wakaCliExecutablePath, cmd);
        process.waitForFinished();
    }

} // namespace Wakatime::Internal

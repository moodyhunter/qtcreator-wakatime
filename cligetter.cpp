#include "cligetter.h"

#include <QDir>
#include <QDirIterator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QProcess>
#include <coreplugin/coreplugin.h>
#include <coreplugin/messagemanager.h>
#include <waka_plugin.h>

namespace Wakatime
{
    namespace Internal
    {

        CliGetter::CliGetter()
        {
            _netMan = new QNetworkAccessManager(this);
            _sslConfig = QSslConfiguration::defaultConfiguration();
            _sslConfig.setProtocol(QSsl::TlsV1_3);
        }

        void CliGetter::startHearBeat(const QString file)
        {
            if (_wakaCliExecutablePath.isEmpty())
            {
                // get the executable path
                auto dir = WakaPlugin::getWakaCLILocation();
                auto iterator = QDirIterator(dir.absolutePath());
                while (iterator.hasNext())
                {
                    auto f = iterator.next();
                    if (iterator.fileInfo().isFile() && iterator.fileName().contains("wakatime-cli"))
                    {
                        _wakaCliExecutablePath = f;
                    }
                }
            }

            auto now = QTime::currentTime();
            if (now < _previous_heartbeat.addSecs(120))
            {
                // do nothing if not passed 2 minutes
                return;
            }
            _previous_heartbeat = now;

            QString cmd = _wakaCliExecutablePath + " --plugin QtCreator-wakatime/" + QString(WAKATIME_PLUGIN_VERSION) + " --entity " + file;
            // run the hearbeat here
            emit promptMessage("Command: " + _wakaCliExecutablePath);
            int x = system(cmd.toStdString().c_str());
            Q_UNUSED(x);
        }

    } // namespace Internal
} // namespace Wakatime

#ifndef WAKATIME_INTERNAL_CLIGETTER_H
#define WAKATIME_INTERNAL_CLIGETTER_H

#include "waka_constants.h"
#include "waka_options.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QTime>

namespace Wakatime
{
    namespace Internal
    {

        using namespace Wakatime::Constants;

        class CliGetter : public QObject
        {
            Q_OBJECT

            QNetworkAccessManager *_netMan;
            QSslConfiguration _sslConfig;
            const WakaOptions *_wakaOptions;
            OSInfo _osInfo;
            QString _wakaCliExecutablePath;
            QTime _previous_heartbeat;

          public:
            CliGetter();

            const QSslConfiguration getSslConfiguration() const;

          public slots:
            void startHearBeat(QString file);

          signals:
            void promptMessage(QString url);
        };

    } // namespace Internal
} // namespace Wakatime

#endif // WAKATIME_INTERNAL_CLIGETTER_H

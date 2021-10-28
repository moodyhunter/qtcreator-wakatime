#ifndef WAKATIME_INTERNAL_CLIGETTER_H
#define WAKATIME_INTERNAL_CLIGETTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include "waka_constants.h"
#include "waka_options.h"

namespace Wakatime {
namespace Internal {

using namespace Wakatime::Constants;

class CliGetter: public QObject
{
    Q_OBJECT

    QNetworkAccessManager *_netMan;
    QSslConfiguration _sslConfig;
    const WakaOptions *_wakaOptions;
    OSInfo _osInfo;
    QString _wakaCliExecutablePath;
public:
    CliGetter();

    const QSslConfiguration getSslConfiguration()const;
public slots:
    void startGettingAssertUrl();
    void startGettingZipDownloadUrl(QString url);
    void startDownloadingZip(QString url);
    void startUnzipping(QString file);
    void startHearBeat(QString file);
signals:
    void doneGettingAssetsUrl(QString url);
    void doneGettingZipDownloadUrl(QString url);
    void doneDownloadingZip(QString file);
    void promptMessage(QString url);
    void doneSettingWakaTimeCli();
};

} // namespace Internal
} // namespace Wakatime

#endif // WAKATIME_INTERNAL_CLIGETTER_H

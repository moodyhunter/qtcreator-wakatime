#pragma once

#include "waka_options.h"

#include <QTime>

namespace Wakatime::Internal
{
    class WakaWorker : public QObject
    {
        Q_OBJECT

      public:
        WakaWorker(QObject *parent = nullptr);

      public slots:
        void startHearBeat(const QString &file, bool isSave);

      signals:
        void promptMessage(QString url);

      private:
        const WakaOptions *_wakaOptions = nullptr;
        QString _wakaCliExecutablePath;
        QTime _previous_heartbeat;
    };
} // namespace Wakatime::Internal

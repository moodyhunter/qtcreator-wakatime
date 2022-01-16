#pragma once

#include "waka_constants.h"
#include "waka_global.h"
#include "wakaworker.h"

#include <QDir>
#include <QPointer>
#include <extensionsystem/iplugin.h>

class QNetworkAccessManager;
class QNetworkReply;
class QToolButton;

namespace Core
{
    class IEditor;
    class IDocument;
} // namespace Core

namespace Wakatime::Internal
{

    class WakaOptions;
    class WakaOptionsPage;
    class WakaWorker;

    class WakaPlugin : public ExtensionSystem::IPlugin
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Wakatime.json")

      public:
        WakaPlugin();
        ~WakaPlugin();
        void showMessagePrompt(const QString &str);

        bool initialize(const QStringList &arguments, QString *errorString);
        void extensionsInitialized();
        ShutdownFlag aboutToShutdown();

        void trySendHeartbeat(const QString &entry, bool isSaving);
        static QDir getWakaCLILocation();

      private:
        bool checkIfWakaCLIExist();

      private slots:
        void onEditorAboutToChange(Core::IEditor *editor);
        void onEditorChanged(Core::IEditor *editor);
        void onAboutToSave(Core::IDocument *document);
        void onEditorStateChanged();

        void onInStatusBarChanged();

        void onDoneSettingUpCLI();

      signals:
        void doneGettingCliAndSettingItUp();
        void sendHeartBeat(QString file, bool isSave = false);

      private:
        WakaWorker *_cliGetter = nullptr; // managing accessing wakatime-cli

        QString _ignore_patern;
        QThread *_cliGettingThread;
        QPointer<QToolButton> _heartBeatButton;
        QSharedPointer<WakaOptions> _wakaOptions;
        QSharedPointer<WakaOptionsPage> _page;
    };

} // namespace Wakatime::Internal

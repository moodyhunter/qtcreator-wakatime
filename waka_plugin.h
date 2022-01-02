#pragma once

#include "cligetter.h"
#include "waka_constants.h"
#include "waka_global.h"

#include <QFile>
#include <QPointer>
#include <extensionsystem/iplugin.h>
#include <memory>

class QNetworkAccessManager;
class QNetworkReply;
class QToolButton;

namespace Core
{
    class IEditor;
    class IDocument;
} // namespace Core

namespace Wakatime
{
    namespace Internal
    {

        class WakaOptions;
        class WakaOptionsPage;
        class CliGetter;

        // For using OSInfo
        using namespace Wakatime::Constants;

        class WakaPlugin : public ExtensionSystem::IPlugin
        {
            Q_OBJECT
            Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Wakatime.json")

          public:
            WakaPlugin();
            ~WakaPlugin();
            void showMessagePrompt(const QString str);

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
            void sendHeartBeat(QString file);

          private:
            qint64 _lastTime = 0;
            QString _lastEntry{ "" };

            CliGetter *_cliGetter; // managing accessing wakatime-cli
            bool _cliIsSetup;

            QString _ignore_patern;
            QThread *_cliGettingThread;
            QPointer<QToolButton> _heartBeatButton;
            QSharedPointer<WakaOptions> _wakaOptions;
            QSharedPointer<WakaOptionsPage> _page;
        };

    } // namespace Internal
} // namespace Wakatime

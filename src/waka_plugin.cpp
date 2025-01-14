#include "waka_plugin.h"

#include "ui/waka_options_page.h"
#include "waka_constants.h"
#include "waka_options.h"

#include <QThread>
#include <QToolButton>
#include <coreplugin/messagemanager.h>
#include <coreplugin/statusbarmanager.h>
#include <texteditor/texteditor.h>

namespace Wakatime::Internal
{
    WakaPlugin::WakaPlugin()
    {
    }

    WakaPlugin::~WakaPlugin()
    {
        // Unregister objects from the plugin manager's object pool
        // Delete members
    }

    void WakaPlugin::showMessagePrompt(const QString &str)
    {
        if (_wakaOptions.isNull())
            return;

        if (_wakaOptions->isDebug())
            Core::MessageManager::writeDisrupting(str);
    }

    QDir WakaPlugin::getWakaCLILocation()
    {
        const static auto default_path = QDir::homePath().append("/.wakatime");
        return default_path;
    }

    bool WakaPlugin::checkIfWakaCLIExist()
    {
        return getWakaCLILocation().entryList().filter("wakatime-cli").isEmpty() == false;
    }

    bool WakaPlugin::initialize(const QStringList &arguments, QString *errorString)
    {
        // Register objects in the plugin manager's object pool
        // Load settings
        // Add actions to menus
        // Connect to other plugins' signals
        // In the initialize function, a plugin can be sure that the plugins it
        // depends on have initialized their members.

        Q_UNUSED(arguments)
        Q_UNUSED(errorString)

        _cliGetter = new WakaWorker();

        _cliGettingThread = new QThread(this);
        _cliGetter->moveToThread(_cliGettingThread);

        connect(this, &WakaPlugin::doneGettingCliAndSettingItUp, this, &WakaPlugin::onDoneSettingUpCLI);

        // Heartbeat sending signal slot combo
        connect(this, &WakaPlugin::sendHeartBeat, _cliGetter, &WakaWorker::startHearBeat);
        // for showing prompts
        connect(_cliGetter, &WakaWorker::promptMessage, this, &WakaPlugin::showMessagePrompt);

        // check if has wakatime-cli in path
        // if not then try download it based of the users operating system
        if (checkIfWakaCLIExist())
        {
            emit this->doneGettingCliAndSettingItUp();
        }

        _cliGettingThread->start();
        return true;
    }

    void WakaPlugin::onDoneSettingUpCLI()
    {

        // check if is latest version
        // check if user has asked for updated version
        // if so, then try update the version of wakatime-cli

        _wakaOptions.reset(new WakaOptions);
        if (_page.isNull())
        {
            _page.reset(new WakaOptionsPage(_wakaOptions, this));
        }

        showMessagePrompt("WakatimeCLI setup");

        connect(_wakaOptions.data(), &WakaOptions::inStatusBarChanged, this, &WakaPlugin::onInStatusBarChanged);

        connect(Core::EditorManager::instance(), &Core::EditorManager::aboutToSave, this, &WakaPlugin::onAboutToSave);
        connect(Core::EditorManager::instance(), &Core::EditorManager::currentEditorAboutToChange, this, &WakaPlugin::onEditorAboutToChange);
        connect(Core::EditorManager::instance(), &Core::EditorManager::currentEditorChanged, this, &WakaPlugin::onEditorChanged);

        onInStatusBarChanged();

        showMessagePrompt("Waka plugin initialized!");
    }

    void WakaPlugin::extensionsInitialized()
    {
        // Retrieve objects from the plugin manager's object pool
        // In the extensionsInitialized function, a plugin can be sure that all
        // plugins that depend on it are completely initialized.
    }

    ExtensionSystem::IPlugin::ShutdownFlag WakaPlugin::aboutToShutdown()
    {
        // Save settings
        // Disconnect from signals that are not needed during shutdown
        // Hide UI (if you add UI that is not in the main window directly)
        if (_cliGettingThread->isRunning() == true)
        {
            _cliGettingThread->quit();
        }
        _cliGettingThread->terminate();
        return SynchronousShutdown;
    }

    void WakaPlugin::onInStatusBarChanged()
    {
        if (_heartBeatButton.data())
        {
            Core::StatusBarManager::destroyStatusBarWidget(_heartBeatButton.data());
        }
        if (_wakaOptions->inStatusBar())
        {
            _heartBeatButton = new QToolButton();
            _heartBeatButton->setIcon(QIcon(":/heartbeat.png"));
            connect(_heartBeatButton, &QToolButton::clicked, this, &WakaPlugin::onEditorStateChanged);

            Core::StatusBarManager::addStatusBarWidget(_heartBeatButton, Core::StatusBarManager::RightCorner);
        }
    }

    void WakaPlugin::onEditorAboutToChange(Core::IEditor *editor)
    {
        if (!editor)
            return;

        disconnect(TextEditor::TextEditorWidget::currentTextEditorWidget(), &TextEditor::TextEditorWidget::textChanged, this, &WakaPlugin::onEditorStateChanged);
    }

    void WakaPlugin::onEditorChanged(Core::IEditor *editor)
    {
        if (!editor)
            return;

        connect(TextEditor::TextEditorWidget::currentTextEditorWidget(), &TextEditor::TextEditorWidget::textChanged, this, &WakaPlugin::onEditorStateChanged);
        emit this->sendHeartBeat(editor->document()->filePath().toString(), true);
    }

    void WakaPlugin::onAboutToSave(Core::IDocument *document)
    {
        // emit signal for sending here.
        emit sendHeartBeat(document->filePath().toString(), true);
    }

    void WakaPlugin::onEditorStateChanged()
    {
        if (const auto doc = Core::EditorManager::currentDocument(); doc)
            emit sendHeartBeat(doc->filePath().toString());
    }

} // namespace Wakatime::Internal

#include "waka_options_widget.h"

#include "ui_waka_options.h"
#include "waka_options.h"

namespace Wakatime::Internal
{
    WakaOptionsWidget::WakaOptionsWidget(const QSharedPointer<WakaOptions> &options, QWidget *parent) : QWidget(parent), _ui(new Ui::WakaOptionsForm), _options(options)
    {
        _ui->setupUi(this);

        connect(_ui->shToolButton, &QToolButton::clicked, this,
                [this]()
                {
                    const auto hasShown = _ui->apiKeyLineEdit->echoMode() == QLineEdit::Normal;
                    _ui->apiKeyLineEdit->setEchoMode(hasShown ? QLineEdit::Password : QLineEdit::Normal);
                    _ui->shToolButton->setText(hasShown ? u"hide"_qs : u"show"_qs);
                });
    }

    WakaOptionsWidget::~WakaOptionsWidget()
    {
        delete _ui;
    }

    void WakaOptionsWidget::restore()
    {
        _ui->apiKeyLineEdit->setText(_options->apiKey());
        _ui->excludePaternLineEdit->setText(_options->excludePattern());
        _ui->inStatusBarCheckBox->setChecked(_options->inStatusBar());
        _ui->debugCheckBox->setChecked(_options->isDebug());
        _ui->enabledCheckBox->setChecked(_options->isEnabled());
    }

    void WakaOptionsWidget::apply()
    {
        _options->setApiKey(_ui->apiKeyLineEdit->text());
        _options->setExcludePatern(_ui->excludePaternLineEdit->text());
        _options->setStatusBar(_ui->inStatusBarCheckBox->isChecked());
        _options->setDebug(_ui->debugCheckBox->isChecked());
        _options->setEnabled(_ui->enabledCheckBox->isChecked());
        _options->save();
    }

} // namespace Wakatime::Internal

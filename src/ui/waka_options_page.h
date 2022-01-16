#ifndef WAKA_OPTIONS_PAGE_H
#define WAKA_OPTIONS_PAGE_H

#include "waka_options_widget.h"

#include <QPointer>
#include <QWidget>
#include <coreplugin/dialogs/ioptionspage.h>

namespace Wakatime
{
    namespace Internal
    {

        class WakaOptionsPage : public Core::IOptionsPage
        {
            Q_OBJECT

          public:
            explicit WakaOptionsPage(const QSharedPointer<WakaOptions> &options, QObject *parent = nullptr);
            virtual ~WakaOptionsPage() override = default;

          private:
            QWidget *widget() override;
            void apply() override;
            void finish() override;

          private:
            QPointer<WakaOptionsWidget> _widget;
            QSharedPointer<WakaOptions> _options;
        };

    } // namespace Internal
} // namespace Wakatime

#endif // WAKA_OPTIONS_PAGE_H

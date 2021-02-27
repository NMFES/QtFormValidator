#pragma once
#include <QHash>
#include <QJsonObject>
#include "rule.h"

namespace QtFormValidator {
    class Validator {
        private:
            QList<QPair<QString, QList<Rule*>>> rules;
            QJsonObject                         data;
            QString                             error;

        public:
            Validator(QJsonObject data, QList<QPair<QString, QList<Rule*>>> rules);
            ~Validator();
            bool valid();
            QString getError();
            void    setError(const QString& error);
    };
}

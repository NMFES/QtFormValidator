#pragma once
#include <QHash>
#include <QJsonObject>
#include "rule.h"

namespace QtFormValidator {
    class Validator {
        private:
            QHash<QString, QList<Rule*>>    rules;
            QJsonObject                     data;
            QString                         error;

        public:
            Validator(QJsonObject data, QHash<QString, QList<Rule*>> rules);
            ~Validator();
            bool valid();
            QString getError();
            void    setError(const QString& error);
    };
}

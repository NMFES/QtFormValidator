#pragma once
#include <QHash>
#include <QJsonObject>
#include "rule.h"

namespace QtFormValidator {
    class Validator {
        private:
            QList<QPair<QString, QList<Rule*>>> rules;
            QJsonObject                         data;
            QPair<QString, QString>             error;

        public:
            Validator(QJsonObject data = {}, QList<QPair<QString, QList<Rule*>>> rules = {});
            ~Validator();
            bool                    validate();
            QPair<QString, QString> getError();
            void                    setError(QPair<QString, QString> error);
    };
}

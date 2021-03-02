#pragma once
#include <QString>
#include <QJsonObject>
#include "rule.h"
#include "validator.h"

namespace QtFormValidator {
    class Form {
        protected:
            Validator*                  validator = nullptr;
            const QJsonObject&          data;
            QHash<QString, QVariant>    extra;

            Form(const QJsonObject& data, const QHash<QString, QVariant>& extra = {});
            ~Form();

        public:
            bool validate();
            QString getError();
    };
}

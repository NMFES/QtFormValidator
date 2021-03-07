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
            QString                     error;
            static inline const QString INVALID_REQUEST = "Invalid Request";

            Form(const QJsonObject& data, const QHash<QString, QVariant>& extra = {});
            ~Form();
            virtual bool                after();
            bool                        failed(const QString& message = INVALID_REQUEST);

        public:
            virtual bool                validate();
            virtual QString             getError();
    };
}

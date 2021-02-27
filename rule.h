#pragma once
#include <QString>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>

namespace QtFormValidator {
    class Rule {
        protected:
            QHash<QString, QVariant>    params;
            QString                     error;

            Rule(QHash<QString, QVariant> params = {});

        public:
            virtual bool    validate(QString name, QJsonObject data) = 0;
            virtual         ~Rule();
            void            setError(const QString& name, const QVariant& message);
            QString         getError();
    };
}

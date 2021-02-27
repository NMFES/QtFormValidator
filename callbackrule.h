#pragma once
#include "rule.h"

namespace QtFormValidator {
    class CallbackRule : public Rule {
        private:
            std::function<bool(const QString& name, const QJsonObject& data, QString& message)> callback;

        public:
            CallbackRule(std::function<bool(const QString& name, const QJsonObject& data, QString& message)> callback);
            virtual ~CallbackRule();
            virtual bool validate(QString name, QJsonObject data);
    };
}

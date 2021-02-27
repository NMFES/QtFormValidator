#pragma once
#include "rule.h"

namespace QtFormValidator {
    class JsonRule : public Rule {
        public:
            JsonRule(QHash<QString, QVariant> params = {});
            virtual ~JsonRule();
            virtual bool validate(QString name, QJsonObject data);
    };
}

#pragma once
#include "rule.h"

namespace QtFormValidator {
    class ArrayRule : public Rule {
        public:
            ArrayRule(QHash<QString, QVariant> params = {});
            virtual ~ArrayRule();
            virtual bool validate(QString name, QJsonObject data);
    };
}

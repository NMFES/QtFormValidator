#pragma once
#include "rule.h"

namespace QtFormValidator {
    class NumericRule : public Rule {
        public:
            NumericRule(QHash<QString, QVariant> params = {});
            virtual ~NumericRule();
            virtual bool validate(QString name, QJsonObject data);
    };
}

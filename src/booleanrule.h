#pragma once
#include "rule.h"

namespace QtFormValidator {
    class BooleanRule : public Rule {
        public:
            BooleanRule(QHash<QString, QVariant> params = {});
            virtual ~BooleanRule();
            virtual bool validate(QString name, QJsonObject data);
    };
}

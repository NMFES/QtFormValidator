#pragma once
#include "rule.h"

namespace QtFormValidator {
    class RegexRule : public Rule {
        public:
            RegexRule(QHash<QString, QVariant> params = {});
            virtual ~RegexRule();
            virtual bool validate(QString name, QJsonObject data);
    };
}

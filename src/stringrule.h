#pragma once
#include "rule.h"

namespace QtFormValidator {
    class StringRule : public Rule {
        public:
            StringRule(QHash<QString, QVariant> params = {});
            virtual ~StringRule();
            virtual bool validate(QString name, QJsonObject data);
    };
}

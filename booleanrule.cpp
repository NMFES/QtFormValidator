#include "booleanrule.h"

namespace QtFormValidator {
    BooleanRule::BooleanRule(QHash<QString, QVariant> params): Rule {params} {}

    BooleanRule::~BooleanRule() {}

    bool BooleanRule::validate(QString name, QJsonObject data) {
        auto value = data.value(name);
        auto message = params.value("message");
        setError(name, message);

        if (value.isBool()) {
            if (params.contains("equals")) {
                if (value.toBool() != params.value("equals").toBool()) {
                    return false;
                }
            }
        } else if (value.isDouble()) {
            QList<QVariant> allowed {1, 0};
            // the value is not in the allowed list
            if (!allowed.contains(value.toDouble())) {
                return false;
            }

            if (params.contains("equals")) {
                if (QVariant(value.toDouble()).toBool() != params.value("equals").toBool()) {
                    return false;
                }
            }
        } else if (value.isString()) {
            QList<QVariant> allowed {"true", "false", "1", "0"};
            // the value is not in the allowed list
            if (!allowed.contains(value.toString())) {
                return false;
            }

            if (params.contains("equals")) {
                if (QVariant(value.toString()).toBool() != params.value("equals").toBool()) {
                    return false;
                }
            }
        } else {
            return false;
        }

        return true;
    }

}

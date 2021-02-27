#include "jsonrule.h"

namespace QtFormValidator {
    JsonRule::JsonRule(QHash<QString, QVariant> params): Rule {params} {}

    JsonRule::~JsonRule() {}

    bool JsonRule::validate(QString name, QJsonObject data) {
        setError(name, params.value("message"));
        return data.value(name).isObject();
    }
}

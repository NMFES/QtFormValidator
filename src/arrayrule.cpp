#include "arrayrule.h"

namespace QtFormValidator {
    ArrayRule::ArrayRule(QHash<QString, QVariant> params): Rule {params} {}

    ArrayRule::~ArrayRule() {}

    bool ArrayRule::validate(QString name, QJsonObject data) {
        setError(name, params.value("message"));
        return data.value(name).isArray();
    }
}

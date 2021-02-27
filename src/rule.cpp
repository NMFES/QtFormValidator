#include "rule.h"

namespace QtFormValidator {
    Rule::Rule(QHash<QString, QVariant> params) {}

    Rule::~Rule() {}

    void Rule::setError(const QString& name, const QVariant& message) {
        error = message.isNull() ? "\"" + name + "\" is invalid" :  message.toString();
    }

    QString Rule::getError() {
        return error;
    }

}

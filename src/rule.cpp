#include "rule.h"

namespace QtFormValidator {
    Rule::Rule(QHash<QString, QVariant> params): params(params) {}

    Rule::~Rule() {}

    void Rule::setError(const QString& name, const QVariant& message) {
        error.first     = name;
        error.second    = message.isNull() ? "Invalid field" :  message.toString();
    }

    QPair<QString, QString> Rule::getError() {
        return error;
    }
}

#include "regexrule.h"

namespace QtFormValidator {
    RegexRule::RegexRule(QHash<QString, QVariant> params): Rule {params} {}

    RegexRule::~RegexRule() {}

    bool RegexRule::validate(QString name, QJsonObject data) {
        auto value = data.value(name);
        auto message = params.value("message");
        setError(name, message);

        if (!value.isString()) {
            return false;
        }

        QRegularExpression expression(params.value("pattern").toString(),
                                      static_cast<QRegularExpression::PatternOption>(params.value("options").toInt()));

        return expression.match(value.toString()).hasMatch();
    }

}

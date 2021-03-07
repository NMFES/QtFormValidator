#include "arrayrule.h"

namespace QtFormValidator {
    ArrayRule::ArrayRule(QHash<QString, QVariant> params): Rule {params} {}

    ArrayRule::~ArrayRule() {}

    bool ArrayRule::validate(QString name, QJsonObject data) {
        setError(name, params.value("message"));

        // TODO: add ability to specify when the array must not be empty

        if (!data.value(name).isArray()) {
            return false;
        }

        // we got a list to compare with
        if (params.contains("in")) {
            auto array      = data.value(name).toArray();
            auto allowed    = params.value("in").toJsonArray();

            // check every element in data list and make sure it presents in mandatory list
            foreach (const auto& element, array) {
                if (!allowed.contains(element)) {
                    return false;
                }
            }
        }

        return true;
    }
}

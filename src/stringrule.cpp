#include "stringrule.h"

namespace QtFormValidator {
    StringRule::StringRule(QHash<QString, QVariant> params): Rule {params} {}

    StringRule::~StringRule() {}

    bool StringRule::validate(QString name, QJsonObject data) {
        auto value = data.value(name);
        auto message = params.value("message");
        setError(name, message);

        if (!value.isString()) {
            return false;
        }

        QHashIterator<QString, QVariant> iterator(params);

        while (iterator.hasNext()) {
            iterator.next();

            // check for min length of the string
            if (iterator.key() == "min") {
                if (value.toString().length() < iterator.value().toInt()) {
                    if (message.isNull()) {
                        setError(name, "\"" + name + "\" must be longer than " + iterator.value().toString() + " symbols");
                    }

                    return false;
                }
            }

            // check for the max length of the string
            if (iterator.key() == "max") {
                if (value.toString().length() > iterator.value().toInt()) {
                    if (message.isNull()) {
                        setError(name, "\"" + name + "\" must be shorter than " + iterator.value().toString() + " symbols");
                    }

                    return false;
                }
            }

            // check if the string present in some strings list
            if (iterator.key() == "in") {
                if (!iterator.value().toStringList().contains(value.toString())) {
                    return false;
                }
            }
        }

        return true;
    }

}

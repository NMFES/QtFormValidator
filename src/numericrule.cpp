#include "numericrule.h"

namespace QtFormValidator {
    NumericRule::NumericRule(QHash<QString, QVariant> params): Rule {params} {}

    NumericRule::~NumericRule() {}

    bool NumericRule::validate(QString name, QJsonObject data) {
        auto value = data.value(name);
        auto message = params.value("message");
        setError(name, message);

        if (!value.isDouble()) {
            return false;
        }

        QHashIterator<QString, QVariant> iterator(params);

        while (iterator.hasNext()) {
            iterator.next();
            // check if the value in greater than min
            if (iterator.key() == "min") {
                if (value.toDouble() < iterator.value().toDouble()) {
                    if (message.isNull()) {
                        setError(name, "\"" + name + "\" must be greater than " + iterator.value().toString());
                    }

                    return false;
                }
            }

            // check if the value is less than max
            if (iterator.key() == "max") {
                if (value.toDouble() > iterator.value().toDouble()) {
                    if (message.isNull()) {
                        setError(name, "\"" + name + "\" must be less than " + iterator.value().toString());
                    }

                    return false;
                }
            }

            // check if the value present in given range
            if (iterator.key() == "in") {
                qDebug() << value.toDouble();
                qDebug() << iterator.value().toJsonArray();

                if (!iterator.value().toJsonArray().contains(value.toDouble())) {
                    return false;
                }
            }
        }

        return true;
    }

}

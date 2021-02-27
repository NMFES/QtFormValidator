#include "callbackrule.h"

namespace QtFormValidator {
    CallbackRule::CallbackRule(std::function<bool (const QString&, const QJsonObject&, QString&)> callback): callback(callback) {}

    CallbackRule::~CallbackRule() {}

    bool CallbackRule::validate(QString name, QJsonObject data) {
        QString message;

        if (!callback(name, data, message)) {
            setError(name, message);
            return false;
        }

        return true;
    }
}

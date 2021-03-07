#include "form.h"

namespace QtFormValidator {
    Form::Form(const QJsonObject& data, const QHash<QString, QVariant>& extra): data(data), extra(extra) {}

    Form::~Form() {
        delete validator;
    }

    bool Form::validate() {
        return validator->validate() ? after() : failed(validator->getError());
    }

    QString Form::getError() {
        return error;
    }

    bool Form::after() {
        return true;
    }

    bool Form::failed(const QString& message) {
        error = message;
        return false;
    }
}

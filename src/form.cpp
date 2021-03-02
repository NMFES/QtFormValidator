#include "form.h"

namespace QtFormValidator {
    Form::Form(const QJsonObject& data, const QHash<QString, QVariant>& extra): data(data), extra(extra) {}

    Form::~Form() {
        delete validator;
    }

    bool Form::validate() {
        return validator->validate();
    }

    QString Form::getError() {
        return validator->getError();
    }
}

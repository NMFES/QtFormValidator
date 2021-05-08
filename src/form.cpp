#include "form.h"

namespace QtFormValidator {
    Form::Form(const QJsonObject& data, const QHash<QString, QVariant>& extra): data(data), extra(extra) {}

    Form::~Form() {
        delete validator;
    }

    bool Form::validate() {
        return validator->validate() ? after() : failed(validator->getError());
    }

    QPair<QString, QString> Form::getError() {
        return error;
    }

    bool Form::after() {
        return true;
    }

    /**
     * @brief Short manual error. "_" means some common error
     * @param message
     * @return
     */
    bool Form::failed(const QString& message) {
        return failed("_", message);
    }

    /**
     * @brief For manual setting error
     * @param name
     * @param message
     * @return
     */
    bool Form::failed(const QString& name, const QString& message) {
        error.first     = name;
        error.second    = message;
        return false;
    }

    /**
     * @brief For receiving Validator's error
     * @param error
     * @return
     */
    bool Form::failed(QPair<QString, QString> error) {
        this->error = error;
        return false;
    }
}

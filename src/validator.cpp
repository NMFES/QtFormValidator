#include "validator.h"

namespace QtFormValidator {
    Validator::Validator(QJsonObject data, QList<QPair<QString, QList<Rule*>>> rules): rules(rules), data(data) {}

    Validator::~Validator() {
        QList<QPair<QString, QList<Rule*>>>::iterator iterator;

        // delete all the rule pointers
        for (iterator = rules.begin(); iterator != rules.end(); ++iterator) {
            foreach (auto rule, iterator->second) {
                delete rule;
            }
        }
    }

    bool Validator::valid() {
        QList<QPair<QString, QList<Rule*>>>::iterator iterator;

        // get attribute's list of rules
        for (iterator = rules.begin(); iterator != rules.end(); ++iterator) {
            // run validation for every rule for this attribute
            foreach (auto rule, iterator->second) {
                if (!rule->validate(iterator->first, data)) {
                    // get the error and brake the loop.
                    // we don't need to check other rules
                    // when at least one of them is failed
                    setError(rule->getError());
                    return false;
                }

            }
        }

        // there were no errors or rules list is empty
        return true;
    }

    QString Validator::getError() {
        return error;
    }

    void Validator::setError(const QString& error) {
        this->error = error;
    }
}

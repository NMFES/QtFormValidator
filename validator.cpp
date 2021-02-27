#include "validator.h"

namespace QtFormValidator {
    Validator::Validator(QJsonObject data, QHash<QString, QList<Rule*> > rules): rules(rules), data(data) {}

    Validator::~Validator() {
        QHashIterator<QString, QList<Rule*>> iterator(rules);

        // delete all the rule pointers
        while (iterator.hasNext()) {
            iterator.next();

            foreach (auto rule, iterator.value()) {
                delete rule;
            }
        }
    }

    bool Validator::valid() {
        QHashIterator<QString, QList<Rule*>> iterator(rules);
        // get attribute's list of rules
        while (iterator.hasNext()) {
            iterator.next();

            // run validation for every rule for this attribute
            foreach (auto rule, iterator.value()) {
                if (!rule->validate(iterator.key(), data)) {
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

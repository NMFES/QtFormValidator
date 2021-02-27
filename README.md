# Introduction

QT doesn't provide enough tools to validate user's input (at least v5.15). We can use QDoubleValidator, QIntValidator, and QRegularExpressionValidator. So if we want to validate some strings we have to use built-in methods like isEmpty() / isNull(), or write manual strings length checking; for numbers we have to write our code with many if/else statements. Also it doesn't explain the way how to separate validation code of business logic (like MVC pattern).

# Quick start

The easiest way to use QtFormValidator is by adding it to your project as git submodule.
To add the library use the following steps:

- Create a new subdirs project. Skip this step if your project already has `TEMPLATE = subdirs` .
- Add a new application subproject. "Qt Console Application" for example. Skip this step if you already have it and the previous step is true.
- Go to your root directory in console. Run `git submodule add https://github.com/NMFES/QtFormValidator.git` in terminal. 
- Add to your main project .pro file `SUBDIRS += QtFormValidator`. Then you should see the next structure in Qt Creator: main project (step 1), it includes your console app (step 2) and QtFormValidator project (step 3-4).
- Right click on your console app project and hit Add library -> Internal library -> select QtFormValidator. Click finish. It will add some code for Qmake into your console app .pro-file. Now you can include the library.

```
#include -- common QT includes here --
#include <"qtformvalidator.h">

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    
    using namespace QtFormValidator;

    // data to check
    QJsonObject data {
        {"name", "NMFES"},
        {"type", 3},
        {"email", "username@gmail.com"},
        {"checked", "1"},
        {"options", QJsonArray {"one", "two"}},
        {"object", QJsonObject {{"prop", 10}}},
    };

    // full example
    Validator validator1(data, {
        {
            "name", {
                new StringRule({{"min", 3}, {"max", 5}, {"in", QStringList {"GitHub", "NMFES"}}, {"message", "Wrong \"name\""}}),
                new CallbackRule([](const QString & name, const QJsonObject & data, QString & message) {
                    return true;
                }),
            }
        },
        {
            "type", {
                new NumericRule({{"min", 1}, {"max", 5}, {"in", QJsonArray {1, 3, 5}}, {"message", "Wrong \"type\""}}),
                new CallbackRule([](const QString & name, const QJsonObject & data, QString & message) {
                    return true;
                    message = "Wrong value";
                    return false;
                }),
            }
        },
        {
            "email", {
                new RegexRule({{"pattern", "^[a-z]+@[a-z]+.[a-z]+$"}, {"options", QRegularExpression::NoPatternOption}, {"message", "Invalid data"}}),
            }
        },
        {
            "checked", {
                new BooleanRule({{"equals", true}, {"message", "Wrong \"checked\""}}),
            }
        },
        {
            "options", {
                new ArrayRule({{"message", "Wrong \"options\""}}),
            }
        },
        {
            "object", {
                new JsonRule({{"message", "Wrong \"object\""}}),
            }
        },
    });

    if (validator1.valid()) {
        qDebug() << "OK";
    } else {
        qDebug() << "FAIL" << validator1.getError();
    }


    // compact example without custom error messages and without extra spaces
    Validator validator2(data, {
        {
            "name", {
                new StringRule({{"min", 3}, {"max", 5}, {"in", QStringList {"GitHub", "NMFES"}}}),
                new CallbackRule([](const QString & name, const QJsonObject & data, QString & message) {
                    return true;
                }),
            }
        },
        {
            "type", {
                new NumericRule({{"min", 1}, {"max", 5}, {"in", QJsonArray {1, 3, 5}}}),
                new CallbackRule([](const QString & name, const QJsonObject & data, QString & message) {
                    return true;
                }),
            }
        },
        { "email", { new RegexRule({{"pattern", "^[a-z]+@[a-z]+.[a-z]+$"}}) } },
        { "checked", { new BooleanRule({{"equals", true}}) } },
        { "options", { new ArrayRule() } },
        { "object", { new JsonRule() } },
    });

    if (validator2.valid()) {
        qDebug() << "OK";
    } else {
        qDebug() << "FAIL" << validator2.getError();
    }
    
    return a.exec();
}
```

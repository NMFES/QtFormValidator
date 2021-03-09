# Introduction

Qt doesn't provide enough tools to validate user's input (at least v5.15). We can use QDoubleValidator, QIntValidator, and QRegularExpressionValidator. So if we want to validate some strings we have to use built-in methods like isEmpty() / isNull(), or write manual strings length checking; for numbers we have to write our code with many if/else statements. Also it doesn't explain the way how to separate validation code of business logic (like MVC pattern).

# Quick start

The easiest way to use QtFormValidator is by adding it to your project as git submodule.
To add the library use the following steps:

- Create a new subdirs project. Skip this step if your project already has `TEMPLATE = subdirs` .
- Add a new application subproject. "Qt Console Application" for example. Skip this step if you already have it and the previous step is true.
- Go to your root directory in console. Run `git submodule add https://github.com/NMFES/QtFormValidator.git` in terminal. 
- Add to your main project .pro file `SUBDIRS += QtFormValidator`. Then you should see the next structure in Qt Creator: main project (step 1), it includes your console app (step 2) and QtFormValidator project (step 3-4).
- Right click on your console app project and hit Add library -> Internal library -> select QtFormValidator. Click finish. It will add some code for Qmake into your console app .pro-file. Now you can include the library. Also you could add `CONFIG += ordered` next to previous SUBDIRS directive to make sure your dependencies are being comppiled in right order.

Please refer [Qt Docs SUBDIRS](https://doc.qt.io/qt-5/qmake-variable-reference.html#subdirs) and [Qt Wiki](https://wiki.qt.io/SUBDIRS_-_handling_dependencies) if you have some troubles with understanding.

## Validation Rules

There are several validation rules. Some of them have mandatory params. 
- **StringRule**. Value must be a string:
    - [min*] (int) Minimal string length
    - [max*] (int) Maximal string length
    - [in*] (QStringList) List of valid values

- **CallbackRule**. Custom valudation using your own code:
    - Lambda-function. Must return boolean value (`true` if checking value in this function is valid). You can use here any you code if provided rules not enough for you. Your function will accept field name (`name`), a whole data object (`data`), you can use here already validated fields (which are above this rule in rules list). Mandatory.

- **NumericRule**. Value must be `int` or `Double`:
    - [min*] (Double) Minimal value
    - [max*] (Double) Maximal value
    - [in*] (QJsonArray) List of valid values (Double)

- **RegexRule**. Value must be a string and pass given Regex pattern:
    - [pattern] (QString) Pattern to check. Mandatory
    - [options*] (int) Qt Regex options. [See Qt docs](https://doc.qt.io/qt-5/qregularexpression.html#PatternOption-enum)

- **BooleanRule**. Value must be a boolean:
    - [equals] (bool) If field value must be `true` or `false`. Optional.

- **ArrayRule**. Value must be a QJsonArray value:
    - [message*] (QString) Custom error message
    - [in*] (QJsonArray) List of valid values (Double/QString)

- **JsonRule**. Value must be a QJsonObject value:
    - [message*] (QString) Custom error message

Params marked with * are optional. Validation stops once there was at least one error. 
As you can see we use RAW pointers to minify our rules code. Anyway each pointer will be deleted in Validator destructor once Validator object leaves current visibility area. Not tested with Qt v6.

## Full example

```c++
#include <QtFormValidator>

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

    Validator validator(data, {
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
                    // message = "Wrong value";
                    // return false;
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

    if (validator.validate()) {
        qDebug() << "OK";
    } else {
        qDebug() << "FAIL" << validator.getError();
    }
    
    return a.exec();
}
```


## Compact example

```c++
#include <QtFormValidator>

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

    Validator validator(data, {
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

    if (validator.validate()) {
        qDebug() << "OK";
    } else {
        qDebug() << "FAIL" << validator.getError();
    }
    
    return a.exec();
}
```

## Using Forms

Let's imagine you want to move previous code somewhere. Forms give you that ability. It is a some kind of Model. To use it you have to create a derived from Form class (.h, .cpp) somewhere in `forms` directory:

```c++
#pragma once
#include <QtFormValidator>

using namespace QtFormValidator;

class UserForm: public Form {
    public:
        UserForm(const QJsonObject& data, const QHash<QString, QVariant>& extra = {});
        bool isBanned();
        
    protected:
        virtual bool after();
};
```

```c++
#include "user_form.h"

bool UserForm::isBanned() {
    return false;
}

UserForm::UserForm(const QJsonObject& data, const QHash<QString, QVariant>& extra): Form(data, extra) {
    validator = new Validator (data, {
        {
            "name", {
                new StringRule({{"min", 3}, {"max", 5}, {"in", QStringList {"GitHub", "NMFES"}}, {"message", "Wrong \"name\""}}),
                new CallbackRule([](const QString & name, const QJsonObject & data, QString & message) {
                    return true;
                }),
            }
        },
    });
}

bool UserForm::after() {
    return (your statement) ? true : failed();
}

```

Then in your `main.cpp` include this user_form and call validation from it:

```c++
#include "forms/user_form.h"
...
UserForm form({
    {"name", "NMFES"},
});

qDebug() << form.validate();
qDebug() << form.getError();
qDebug() << form.isBanned();
        
```

That's it. Also you could see there is `isBanned` method. It is a custom method which is not really needed. But you can add as many custom methods as you want. In our case we use it after we are convinced that given data is valid and we can check if this user is banned, exists etc.

The hook `after()` will be called only if previous validation rules are passed successfully. This method must return true if all is good. If there were any errors you need to return `failed("your custom error here")`.

```c++
...
UserForm form({
    {"name", "NMFES"},
});

if (form.validate() && !form.isBanned()) {
    // sign in him
}
```

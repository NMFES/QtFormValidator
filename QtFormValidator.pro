QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/arrayrule.cpp \
    src/booleanrule.cpp \
    src/callbackrule.cpp \
    src/form.cpp \
    src/jsonrule.cpp \
    src/numericrule.cpp \
    src/regexrule.cpp \
    src/rule.cpp \
    src/stringrule.cpp \
    src/validator.cpp

HEADERS += \
    src/arrayrule.h \
    src/booleanrule.h \
    src/callbackrule.h \
    src/form.h \
    src/jsonrule.h \
    src/numericrule.h \
    qtformvalidator.h \
    src/regexrule.h \
    src/rule.h \
    src/stringrule.h \
    src/validator.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QtFormValidator

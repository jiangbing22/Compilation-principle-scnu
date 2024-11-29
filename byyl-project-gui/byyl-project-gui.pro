QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DFA.cpp \
    LALR.cpp \
    NFA.cpp \
    RE.cpp \
    grammar.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DFA.h \
    LALR.h \
    NFA.h \
    RE.h \
    grammar.h \
    mainwindow.h \
    mutils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    min_cgrammar.txt \
    min_c文法.txt \
    mini_c_tokens.txt \
    source_code.mini_c \
    testgrammar.txt \
    tiny_grammar.txt \
    tiny_test_code.txt \
    tiny_tokens.txt

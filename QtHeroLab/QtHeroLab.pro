# Add more folders to ship with the application, here
QmlData.source = qml/QtHeroLab
QmlData.target = qml
DEPLOYMENTFOLDERS = QmlData

QT += xml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

win32: DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += QUAZIP_STATIC
win32: include(../zlib-1.2.8/zlib.pri)
linux: LIBS += -lz
include(../quazip-0.5.1/quazip/quazip.pri)

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    portfolio.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    portfolio.h

OTHER_FILES += \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/version.xml \
    android/res/values-ja/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-id/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/AndroidManifest.xml

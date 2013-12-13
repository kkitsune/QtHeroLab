# Add more folders to ship with the application, here
QmlData.source = qml
QmlData.target = .
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
SOURCES += main.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
qtcAddDeployment()

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
INCLUDEPATH += "C:\Program Files\OpenCV\Opencv300\build\include"

win32:CONFIG(debug, debug|release): {
    LIBS += -L"C:\Program Files\OpenCV\Opencv300\build\x64\vc12\lib" \
    -lopencv_ts300d \
    -lopencv_world300d
    }
else:win32:CONFIG(release, debug|release): {
    LIBS += -L"C:\Program Files\OpenCV\Opencv300\build\x64\vc12\lib" \
    -lopencv_ts300 \
    -lopencv_world300
    }

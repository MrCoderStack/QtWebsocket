QT       *= network

SOURCES += $$PWD/websocket.cpp \
	$$PWD/websocketserver.cpp \
	$$PWD/websocketprotocol.cpp \
	$$PWD/handshakerequest.cpp \
	$$PWD/handshakeresponse.cpp \
	$$PWD/dataprocessor.cpp

HEADERS += $$PWD/websocket.h \
	$$PWD/websocketserver.h \
	$$PWD/websocketprotocol.h \
	$$PWD/handshakerequest.h \
	$$PWD/handshakeresponse.h \
	$$PWD/dataprocessor.h

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

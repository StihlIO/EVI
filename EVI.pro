QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    EVIModel/ConnectorModel.cpp \
    EVIModel/ConnectorView.cpp \
    EVIModel/EviModel.cpp \
    EVIModel/EviModelView.cpp \
    EVIModel/ImageLighter.cpp \
    OCPP/Messages/Authorize.cpp \
    OCPP/Messages/Bootnotification.cpp \
    OCPP/Messages/Chargingprofile.cpp \
    OCPP/Messages/Chargingschedule.cpp \
    OCPP/Messages/Chargingscheduleperiod.cpp \
    OCPP/Messages/Responce/AuthorizeResp.cpp \
    OCPP/Messages/Responce/BootnotificationResp.cpp \
    OCPP/Messages/Responce/RemotestarttransactionResp.cpp \
    OCPP/Messages/Responce/RemotestoptransactionResp.cpp \
    OCPP/Messages/Heartbeat.cpp \
    OCPP/Messages/Metervalue.cpp \
    OCPP/Messages/Metervalues.cpp \
    OCPP/Messages/Remotestarttransaction.cpp \
    OCPP/Messages/Remotestoptransaction.cpp \
    OCPP/Messages/Responce/StarttransactionResp.cpp \
    OCPP/Messages/Sampledvalue.cpp \
    OCPP/Messages/Starttransaction.cpp \
    OCPP/Messages/Statusnotification.cpp \
    OCPP/Messages/Stoptransaction.cpp \
    OCPP/Ocpp16MessageBuilder.cpp \
    OCPP/Ocpp16Messages.cpp \
    OCPP/OcppCore16.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    EVIModel/ConnectorModel.h \
    EVIModel/ConnectorView.h \
    EVIModel/EviModel.h \
    EVIModel/EviModelView.h \
    EVIModel/ImageLighter.h \
    OCPP/Enumeration/Ocpp16_Authorizationstatus.h \
    OCPP/Enumeration/Ocpp16_Chargingprofilekindtype.h \
    OCPP/Enumeration/Ocpp16_Chargingprofilepurposetype.h \
    OCPP/Enumeration/Ocpp16_Chargingrateunittype.h \
    OCPP/Enumeration/Ocpp16_Enumeration.h \
    OCPP/Enumeration/Ocpp16_Errorvalue.h \
    OCPP/Enumeration/Ocpp16_Location.h \
    OCPP/Enumeration/Ocpp16_Measurand.h \
    OCPP/Enumeration/Ocpp16_Phase.h \
    OCPP/Enumeration/Ocpp16_Readingcontext.h \
    OCPP/Enumeration/Ocpp16_Reason.h \
    OCPP/Enumeration/Ocpp16_Recurrencykindtype.h \
    OCPP/Enumeration/Ocpp16_Registrationstatus.h \
    OCPP/Enumeration/Ocpp16_Remotestartstopstatus.h \
    OCPP/Enumeration/Ocpp16_Status.h \
    OCPP/Enumeration/Ocpp16_Unitofmeasure.h \
    OCPP/Enumeration/Ocpp16_Valueformat.h \
    OCPP/Messages/Authorize.h \
    OCPP/Messages/Bootnotification.h \
    OCPP/Messages/Chargingprofile.h \
    OCPP/Messages/Chargingschedule.h \
    OCPP/Messages/Chargingscheduleperiod.h \
    OCPP/Messages/Responce/AuthorizeResp.h \
    OCPP/Messages/Responce/BootnotificationResp.h \
    OCPP/Messages/Responce/RemotestarttransactionResp.h \
    OCPP/Messages/Responce/RemotestoptransactionResp.h \
    OCPP/Messages/Heartbeat.h \
    OCPP/Messages/Idtaginfo.h \
    OCPP/Messages/Metervalue.h \
    OCPP/Messages/Metervalues.h \
    OCPP/Messages/Remotestarttransaction.h \
    OCPP/Messages/Remotestoptransaction.h \
    OCPP/Messages/Responce/StarttransactionResp.h \
    OCPP/Messages/Sampledvalue.h \
    OCPP/Messages/Starttransaction.h \
    OCPP/Messages/Statusnotification.h \
    OCPP/Messages/Stoptransaction.h \
    OCPP/Ocpp16Constant.h \
    OCPP/Ocpp16MessageBuilder.h \
    OCPP/Ocpp16Messages.h \
    OCPP/Ocpp16Origin.h \
    OCPP/OcppCore16.h \
    mainwindow.h

FORMS += \
    EVIModel/ConnectorView.ui \
    EVIModel/EviModelView.ui \
    EVIModel/ImageLighter.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

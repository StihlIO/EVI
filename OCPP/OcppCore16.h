#ifndef OCPPCORE16_H
#define OCPPCORE16_H

#include <QWebSocket>

#include "OCPP/Ocpp16Messages.h"
#include "OCPP/Ocpp16MessageBuilder.h"

class OcppCore16 : public QObject
{
    Q_OBJECT

    struct Session {
        QWebSocket *wSock = nullptr;
        QString url;
        bool isConnected = false;
        std::function<void(bool isConnected)> connectionChange = nullptr;
        std::function<OCPP16Origin*(const QString &, const QJsonObject &)> unpendingMessage = nullptr;
        QHash<QString, std::function<void(const QJsonObject &)>> pendingMessage;
    };

    QHash<QString, Session *> sessions; // session for url
    std::function<void(const QString &)> onLog = nullptr;
    void DebugMessage(const QString &msg) const;
    void TextMessageReceived(Session *session, const QString &message);

public:

    OcppCore16();
    static OcppCore16 *I();

    //create session for url
    void Start(const QString &url, std::function<void(bool isConnected)> connectionChange,
               std::function<OCPP16Origin*(const QString &, const QJsonObject &)> unpendingMessage);

    //make connect for existing url
    void Connect(const QString &url);
    void Disconnect(const QString &url) const;

    void MakeMessage(const QString &url, const OCPP16Origin *unit, std::function<void(const QJsonObject &)> onResponce);

    void OnLog(std::function<void(const QString &)> onLog);
};

#endif // OCPPCORE16_H

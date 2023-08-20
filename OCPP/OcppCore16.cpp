/*

Copyright 2023 Lukashevich Daniil

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "OcppCore16.h"

#include <QJsonArray>
#include <QJsonDocument>

OcppCore16::OcppCore16() : QObject(nullptr)
{

}

void OcppCore16::DebugMessage(const QString &msg) const
{
    if(onLog) {
        onLog(msg);
    }
}

void OcppCore16::TextMessageReceived(Session *session, const QString &message)
{
    QJsonArray array = QJsonDocument::fromJson(message.toUtf8()).array();
    if(array.size() == 3) {
        if(array[0].toInt() == static_cast<int>(OCPP16MessageType::CALLRESULT)) {
            QString uid = array[1].toString();
            if(session->pendingMessage.contains(uid)) {
                session->pendingMessage[uid](array[2].toObject());
                session->pendingMessage.remove(uid);
            }
        }
    } else if(array.size() == 4) {
        if(array[0].toInt() == static_cast<int>(OCPP16MessageType::CALL)) {
            if(session->unpendingMessage != nullptr) {
                auto responce = session->unpendingMessage(array[2].toString(), array[3].toObject());
                if(responce != nullptr) {
                    QString uid = array[1].toString();
                    QString msg = Ocpp16MessageBuilder::I()->Build(OCPP16MessageType::CALLRESULT, responce, uid).AsString();
                    DebugMessage("Responce:");
                    DebugMessage(msg);
                    session->wSock->sendTextMessage(msg);
                    delete responce;
                }
            }
        }
    }
}

OcppCore16 *OcppCore16::I()
{
    static OcppCore16 instace;
    return &instace;
}

void OcppCore16::Start(const QString &url, std::function<void(bool isConnected)> connectionChange, std::function<OCPP16Origin *(const QString &, const QJsonObject &)> unpendingMessage)
{
    if(sessions.contains(url)) {
        return;
    }

    auto s = new Session();
    s->connectionChange = connectionChange;
    s->unpendingMessage = unpendingMessage;
    sessions.insert(url, s);
    s->wSock = new QWebSocket();
    connect(s->wSock, &QWebSocket::disconnected, this, [ s, this ]() {
        DebugMessage("Disconnected!");
        s->isConnected = false;
        s->connectionChange(false);
    });

    connect(s->wSock, &QWebSocket::connected, this, [ s, this ]() {
        DebugMessage("Connected!");
        s->isConnected = true;
        s->connectionChange(true);
    });

    connect(s->wSock, &QWebSocket::textMessageReceived, this, [ s, this ](const QString & message) {
        DebugMessage("Request: " + message);
        TextMessageReceived(s, message);
    });
}

void OcppCore16::Connect(const QString &url)
{
    if(sessions.contains(url)) {
        auto s = sessions[url];
        s->pendingMessage.clear();
        DebugMessage("Connect to " + url);
        QNetworkRequest rq;
        rq.setUrl(url);
        rq.setRawHeader("Sec-WebSocket-Protocol", "ocpp1.6");
        s->wSock->open(rq);
    }
}

void OcppCore16::Disconnect(const QString &url) const
{
    if(sessions.contains(url)) {
        auto s = sessions[url];
        s->wSock->close();
    }
}

void OcppCore16::MakeMessage(const QString &url, const OCPP16Origin *unit, std::function<void (const QJsonObject &)> onResponce)
{
    if(sessions.contains(url)) {
        auto s = sessions[url];
        if(s != nullptr) {
            QString uid;
            auto msg = Ocpp16MessageBuilder::I()->Build(OCPP16MessageType::CALL, unit, uid).AsString();
            if(onResponce != nullptr) {
                s->pendingMessage.insert(uid, onResponce);
            }

            if(!s->isConnected) {
                DebugMessage("No connection, try reconnect!");
                Connect(s->url);
            }

            DebugMessage("Send to " + url + ":");
            DebugMessage(msg);
            s->wSock->sendTextMessage(msg);
        } else {
            qDebug() << "Session for" << url << "is closed";
        }
    } else {
        qDebug() << "Can't find session for" << url;
    }
}

void OcppCore16::OnLog(std::function<void (const QString &)> onLog)
{
    this->onLog = onLog;
}

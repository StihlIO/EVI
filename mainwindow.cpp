/*

Copyright 2023 Lukashevich Daniil

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>

#include "EVIModel/EviModelView.h"
#include "OCPP/OcppCore16.h"

void Log(const QString &logData)
{
    QDir dir(QDir::currentPath() + "/Log/" + QDateTime::currentDateTime().date().toString("ddMMyyyy"));
    if(!dir.exists()) {
        dir.mkpath(dir.path());
    }
    QFile file(dir.path() + "/" + QDateTime::currentDateTime().date().toString("ddMMyyyy") + ".txt");
    file.open(QIODevice::Append);
    QString fullLog = QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + ": " + logData + "\n";
    file.write(fullLog.toUtf8());
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto emView = new EviModelView();
    auto em = new EviModel("EVIPoint", "ws://localhost:4991/OCPP/EVI01");

    OcppCore16::I()->OnLog([ emView ](const QString & msg) {
        Log(msg);
        emView->AddLogData(msg);
    });

    em->AddConnector(new ConnectorModel(0, 500, "05K/SEC", 2));
    em->AddConnector(new ConnectorModel(0, 1000, "1K/SEC", 1));
    emView->Bind(em);

    ui->evModels->addWidget(emView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "ConnectorView.h"
#include "EviModelView.h"
#include "ui_EviModelView.h"

void EviModelView::StartEna()
{
    model->ChangeUrl(ui->leUrl->text());
    model->Enable([ this ](bool isConnected) {
        if(isConnected) {
            Log("Connected");
            model->Boot([ this ](QString status, int interval) {
                Log("Boot responce " + status);
                StatusSwitch();
                heartTimer->start(interval * 1000);
            });
        } else {
            heartTimer->stop();
            Log("Disconnected");
        }
    });
}

void EviModelView::PowerOff() const
{
    model->Disconnect();
}

void EviModelView::StatusSwitch()
{
    auto cons = model->ConnectorList();
    // error when std::begin(model->ConnectorList()), std::end(model->ConnectorList()) ->
    // for(auto : model->ConnectorList()) work proper
    std::for_each(std::begin(cons), std::end(cons), [this](auto c) {
        c->SetPowerState(!ui->cbPowerError->isChecked());
    });
}

void EviModelView::Log(const QString &msg) const
{
    ui->teDisplay->append(msg);
}

EviModelView::EviModelView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EviModelView)
{
    ui->setupUi(this);
}

EviModelView::~EviModelView()
{
    delete ui;
}

void EviModelView::Bind(EviModel *model)
{
    this->model = model;
    ui->leUrl->setText(model->getFurl());
    auto cl = model->ConnectorList();
    for(auto model : cl) {
        auto view = new ConnectorView();
        connectors.append(view);
        view->BindModel(model);
        for(int i = 0; i < model->PossibleConnectorTypes(); i++) {
            view->AddConnectorType(model->Name() + "T" + QString::number(i + 1));
        }
        view->Init(10000, 50000, 100000, [ this ](const QString & data) {
            AddLogData(data);
        });

        ui->connectorHolder->addWidget(view);
    }
    heartTimer = new QTimer(this);
    connect(heartTimer, &QTimer::timeout, this, [ model, this ]() {
        model->HeartBeat();
    });
}

void EviModelView::AddLogData(const QString &logData) const
{
    QString fullLog = QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + ": " + logData;
    ui->teDisplay->append(fullLog);
}

void EviModelView::on_btnEna_clicked()
{
    if(ui->btnEna->text() == "PowerOff") {
        PowerOff();
        ui->btnEna->setText("Enable");
        ui->btnReboot->setEnabled(false);
        return;
    }
    StartEna();
    ui->btnReboot->setEnabled(true);
    ui->btnEna->setText("PowerOff");
}

void EviModelView::on_btnReboot_clicked()
{
    model->Disconnect();
    StartEna();
}

void EviModelView::on_cbPowerError_clicked()
{
    StatusSwitch();
}

void EviModelView::on_btnTouchCard_clicked()
{
    model->AuthTag(ui->leTagUID->text(), nullptr);
}

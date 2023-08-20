#include "ConnectorView.h"
#include "ImageLighter.h"
#include "ui_ConnectorView.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QSpacerItem>

#define LazyNew(val) if(val){delete val;} val

int ConnectorView::id(const QPushButton *btn) const
{
    for(int i = 0; i < vConnectors.count(); i++) {
        if(vConnectors[i].button == btn) {
            return i;
        }
    }
    return -1;
}

void ConnectorView::ChangeButtonState(bool newState, const QPushButton *exclude)
{
    for(auto &c : qAsConst(vConnectors)) {
        if(exclude == c.button) {
            continue;
        }
        c.button->setEnabled(newState);
    }
}

void ConnectorView::InitDone()
{
    QGridLayout *gl = dynamic_cast<QGridLayout *>(this->layout());
    if(gl) {
        gl->addWidget(label, 0, 0, 1, 1);
        gl->addWidget(pbCurrent, 0, 1, 1, 1);
        for(int i = 0; i < vConnectors.length(); i++) {
            gl->addWidget(vConnectors[i].button, 1 + i, 0, 1, 1);
        }
        gl->addWidget(dsbCurr, 1, 1, 1, 1);
        gl->addWidget(dsbMax, 2, 1, 1, 1);
        gl->addWidget(lighter, 3, 1, 1, 1);
    }
}

void ConnectorView::Handle(int id)
{
    if(id == -1) {
        return;
    }
    auto btn = vConnectors[id].button;
    ChangeButtonState(false, btn);

    pbCurrent->setMaximum(dsbMax->value());
    pbCurrent->setValue(dsbCurr->value());
    pbCurrent->setEnabled(true);
    dsbCurr->setEnabled(false);
    dsbCurr->setEnabled(false);

    model->Handle();

    ((ImageLighter *)lighter)->SetOff(false);
    emit Handled(true);
}

void ConnectorView::Close(int id, bool notCallModel)
{
    if(id == -1) {
        return;
    }
    auto btn = vConnectors[id].button;
    btn->setText(vConnectors[id].connectorTypeName);
    ChangeButtonState(true, nullptr);

    pbCurrent->setEnabled(false);
    dsbCurr->setEnabled(true);
    dsbCurr->setEnabled(true);

    if(!notCallModel) {
        model->Close();
    }

    ((ImageLighter *)lighter)->SetOff(true);
    emit Handled(false);
}

void ConnectorView::Verbose(const QString &data) const
{
    qDebug() << model->Id() << data;
    if(verbose) {
        verbose(QString::asprintf("[%02d]: ", model->Id()) + data);
    }
}

void ConnectorView::StateChange(ConnectorModel::State newState)
{
    using enum ConnectorModel::State;
    QString str = "";
    switch(newState) {
        case Undefined:
            str = "Udef";
            break;
        case Faulted:
            str = "Fault";
            break;
        case OnPost:
            str = "Idle";
            for(int id = 0; id < vConnectors.count(); id++) {
                Close(id, true);
            }
            break;
        case Authorized:
            str = "Auth";
            break;
        case OnPostAuthClr:
            str = "Clear";
            break;
        case Connected2EV:
            str = "InEv";
            break;
        case Charging:
            str = "Charge";
            break;
        case InEVButChargeDone:
            str = "Done";
            break;
    }
    label->setText("Connector: " + QString::number(model->Id()) + "[" + str + "]");
    Verbose(str);
}

void ConnectorView::BeforeInitProgressClosure(int currValue, int maxValue, int maxPossible)
{
    LazyNew(dsbCurr) = new QDoubleSpinBox(this);
    LazyNew(dsbMax) = new QDoubleSpinBox(this);
    LazyNew(pbCurrent) = new QProgressBar(this);

    dsbCurr->setMaximum(maxPossible);
    dsbCurr->setValue(currValue);
    dsbMax->setMaximum(maxPossible);
    dsbMax->setValue(maxValue);

    pbCurrent->setValue(0);
    pbCurrent->setEnabled(false);

    LazyNew(lighter) = new ImageLighter(this);
    lighter->setMaximumSize(64, 64);
}

ConnectorView::ConnectorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectorView)
{
    ui->setupUi(this);
    this->setLayout(new QGridLayout());
}

ConnectorView::~ConnectorView()
{
    delete ui;
}

void ConnectorView::BindModel(ConnectorModel *model)
{
    this->model = model;
    LazyNew(label) = new QLabel("Connector: " + QString::number(model->Id()), this);
    LazyNew(processTimer) = new QTimer(this);
    connect(processTimer, &QTimer::timeout, this, [ model, this ]() {
        AddProgress(model->ProcessCharging(Rest()));
    });
    processTimer->start(250);
    model->OnStateChange(this, [ this ](ConnectorModel::State newState) {
        StateChange(newState);
    });
    StateChange(model->Current());
}

void ConnectorView::AddConnectorType(const QString &typeName)
{
    auto btn = new QPushButton(this);
    vConnectors.append(ConnectorViewData{typeName, btn});
    btn->setText(typeName);
    connect(btn, &QPushButton::clicked, this, [ btn, this ]() {
        if(model->IsCanHandled()) {
            Handle(id(btn));
        } else if(model->IsCanClose()) {
            Close(id(btn));
        }
    });
}

void ConnectorView::Init(int currValue, int maxValue, int maxPossible, std::function<void (const QString &)> verbose)
{
    BeforeInitProgressClosure(currValue, maxValue, maxPossible);
    this->verbose = verbose;
    InitDone();
}

void ConnectorView::AddProgress(int val)
{
    pbCurrent->setValue(pbCurrent->value() + val);
}

int ConnectorView::Rest() const
{
    return pbCurrent->maximum() - pbCurrent->value();
}

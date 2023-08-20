#ifndef EVIMODELVIEW_H
#define EVIMODELVIEW_H

#include "ConnectorView.h"
#include "EviModel.h"

#include <QTimer>
#include <QWidget>

namespace Ui
{
class EviModelView;
}

class EviModelView : public QWidget
{
    Q_OBJECT

    EviModel *model;

    void StartEna();
    void PowerOff() const;
    void StatusSwitch();

    void Log(const QString &msg) const;
    QList<ConnectorView *> connectors;

    QTimer *heartTimer = nullptr;

public:
    explicit EviModelView(QWidget *parent = nullptr);
    ~EviModelView();

    void Bind(EviModel *model);
    void AddLogData(const QString &logData) const;

private slots:

    void on_btnEna_clicked();
    void on_btnReboot_clicked();
    void on_cbPowerError_clicked();
    void on_btnTouchCard_clicked();

private:
    Ui::EviModelView *ui;
};

#endif // EVIMODELVIEW_H

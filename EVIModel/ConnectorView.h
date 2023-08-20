#ifndef CONNECTORVIEW_H
#define CONNECTORVIEW_H

#include "ConnectorModel.h"

#include <QDoubleSpinBox>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

namespace Ui
{
class ConnectorView;
}

class ConnectorView : public QWidget
{
    Q_OBJECT

    ConnectorModel *model;

    QLabel *label = nullptr;
    QWidget *lighter = nullptr;
    QDoubleSpinBox *dsbCurr = nullptr;
    QDoubleSpinBox *dsbMax = nullptr;
    QProgressBar *pbCurrent = nullptr;

    QTimer *processTimer = nullptr;
    std::function<void(const QString &data)> verbose = nullptr;

    struct ConnectorViewData {
        QString connectorTypeName;
        QPushButton *button;
    };
    QList<ConnectorViewData> vConnectors;
    int id(const QPushButton *btn) const;

    void ChangeButtonState(bool newState, const QPushButton *exclude);

    void InitDone();

    void Handle(int id);
    void Close(int id, bool notCallModel = false);
    void Verbose(const QString &data) const;

    void StateChange(ConnectorModel::State newState);
    void BeforeInitProgressClosure(int currValue, int maxValue, int maxPossible);

public:
    explicit ConnectorView(QWidget *parent = nullptr);
    ~ConnectorView();

    void BindModel(ConnectorModel *model);
    void AddConnectorType(const QString &typeName);

    void Init(int currValue, int maxValue, int maxPossible, std::function<void(const QString &data)> verbose);

    void AddProgress(int val);
    int Rest() const;

signals:

    void Handled(bool isHandled);

private:
    Ui::ConnectorView *ui;
};

#endif // CONNECTORVIEW_H

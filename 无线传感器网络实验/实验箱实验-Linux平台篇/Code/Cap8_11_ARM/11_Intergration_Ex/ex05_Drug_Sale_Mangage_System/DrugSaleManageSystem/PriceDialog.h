#ifndef PRICEDIALOG_H
#define PRICEDIALOG_H

#include <QDialog>

namespace Ui {
    class PriceDialog;
}

class PriceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PriceDialog(QWidget *parent = 0);
    ~PriceDialog();

    float price() const;
    QString name() const;

public slots:
    void setPrice(float p);
    void setName(const QString &name);

private:
    Ui::PriceDialog *ui;

private slots:
    void onSftKeypadNewString(const QString &str);
};

#endif // PRICEDIALOG_H

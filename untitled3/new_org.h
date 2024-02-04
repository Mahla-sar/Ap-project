#ifndef NEW_ORG_H
#define NEW_ORG_H

#include <QDialog>

namespace Ui {
class new_org;
}

class new_org : public QDialog
{
    Q_OBJECT

public:
    explicit new_org(QWidget *parent = nullptr);
    ~new_org();

private slots:
    void on_buttonBox_accepted();
signals:
    void neworg_added(QString);
private:
    Ui::new_org *ui;
};

#endif // NEW_ORG_H

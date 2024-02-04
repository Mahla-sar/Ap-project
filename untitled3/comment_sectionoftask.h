#ifndef COMMENT_SECTIONOFTASK_H
#define COMMENT_SECTIONOFTASK_H

#include <QDialog>

namespace Ui {
class comment_sectionoftask;
}

class comment_sectionoftask : public QDialog
{
    Q_OBJECT

public:
    explicit comment_sectionoftask(QWidget *parent = nullptr);

    ~comment_sectionoftask();

private slots:
    void on_pushButton_clicked();
    //void showComment(const QString &taskName, const QString &comment);


private:
    Ui::comment_sectionoftask *ui;
};

#endif // COMMENT_SECTIONOFTASK_H

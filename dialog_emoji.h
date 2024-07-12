#ifndef DIALOG_EMOJI_H
#define DIALOG_EMOJI_H

#include <QDialog>

namespace Ui {
class Dialog_emoji;
}

class Dialog_emoji : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_emoji(QWidget *parent = nullptr);
    ~Dialog_emoji();

signals:
    void newEmoji(QString new_emoji);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

private:
    Ui::Dialog_emoji *ui;
    QString emoji_str;
};

#endif // DIALOG_EMOJI_H

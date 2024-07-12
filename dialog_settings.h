#ifndef DIALOG_SETTINGS_H
#define DIALOG_SETTINGS_H

#include <QDialog>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkInterface>

namespace Ui {
class Dialog_settings;
}

class Dialog_settings : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_settings(QWidget *parent = nullptr);
    ~Dialog_settings();

    int getPort();

    QString getAdress();

    QString getNick();

    int mode;

public slots:

    void printAdress(QString print_adress);

    void printPort(int print_port);

    void printNick(QString print_nick);

private slots:
    void on_radioButton_Client_clicked();

    void on_radioButton_Server_clicked();

    void on_pushButton_Create_clicked();

    void on_pushButton_Connect_clicked();

    void setPort(int new_port);

    void setAdress(QString new_adress_string);

    void setNick(QString new_nick);

    void setIpRegex(QRegExp new_ipRegex);

    QRegExp getIpRegex(); // геттер шаблона для валидатора

    bool checkAdress();

    bool checkNickname();

    bool checkPort(); // проверка портов

    void getMyIP();

private:
    Ui::Dialog_settings *ui;

    int port;

    QString nick, adress_string;

    QRegExpValidator *ipValidator;

    QValidator *portValidator;

    QRegExp ipRegex;

};

#endif // DIALOG_SETTINGS_H

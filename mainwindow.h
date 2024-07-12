#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer> // Для сервера
#include <QtNetwork/QTcpSocket> // Для соединения
#include <QTimer>
#include <QVector>
#include <dialog_settings.h>
#include <dialog_emoji.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void read_data(void); // Поступили данные

    void new_connection(void); // Подключился клиент

    void disconnected(void);

    void spam();

    void connection_state(void);

    void printEmojis(QString new_emoji);

    void printEmojisSpam(QString new_emoji);

    void on_pushButton_SendMes_clicked();

    void on_pushButton_Settings_clicked();

    void on_pushButton_Emoji_clicked();

    void on_pushButton_Disconnect_clicked();

    void on_pushButton_ServerOff_clicked();

    void on_pushButton_SPAM_clicked();

    void on_pushButton_Stop_clicked();

    void on_lineEdit_SendMes_textChanged();

    void on_lineEdit_Spam_textChanged();

    void on_pushButton_Emoji_2_clicked();

private:
    Ui::MainWindow *ui;

    QTimer * spam_timer = nullptr;
    QTimer * connection_timer = nullptr;

    QTcpServer * TCPServer;
    QTcpSocket * clientSocket;

    QVector<QTcpSocket*> sockets;

    QString nick, string_adress;
    QByteArray spam_ba;
    int mode, port, clients;
    bool first;
};

#endif // MAINWINDOW_H

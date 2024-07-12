#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) // Конструктор
{
    ui->setupUi(this);

    //    TCPSocket = new QTcpSocket(this);
    TCPServer = new QTcpServer(this);

    clientSocket = new QTcpSocket(this);
    spam_timer = new QTimer(this);
    connection_timer = new QTimer(this);

    mode = 0;
    clients = 0;
    first = true;

    ui->pushButton_SendMes->hide();
    ui->pushButton_Disconnect->hide();
    ui->pushButton_ServerOff->hide();

    setWindowTitle("MultiChat");
    ui->textEdit_Input->setReadOnly(true);

    ui->label->clear();
    ui->pushButton_Stop->hide();/*
    ui->lineEdit_Spam->hide();*/
    ui->pushButton_SPAM->setEnabled(false);
    ui->pushButton_SPAM->hide();/*
    ui->pushButton_Emoji_2->hide();*/

    //    connect(TCPSocket, SIGNAL(connected()),this, SLOT(connected()));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(spam_timer, SIGNAL(timeout()), this, SLOT(spam()));
    connect(connection_timer, SIGNAL(timeout()), this, SLOT(connection_state()));
}

MainWindow::~MainWindow() // Деструктор
{
    if (mode == 1)
    {
        on_pushButton_ServerOff_clicked();
        for (int i = 0; i < sockets.size(); i++) {
            sockets[i]->write("Server off");
            delete sockets[i];
            sockets[i] = nullptr;
        }
        sockets.clear();
        TCPServer->close();
    }
    else if (mode == 2)
    {
        QByteArray ba;
        ba.append(nick + " disconnected");
        clientSocket->write(ba);
        clientSocket->waitForDisconnected(10);
        clientSocket->abort();
        clientSocket->disconnect();
        clientSocket->disconnectFromHost();
    }

    spam_timer->stop();
    connection_timer->stop();



    delete spam_timer;
    delete connection_timer;



    delete clientSocket;
    delete TCPServer;

    clientSocket = nullptr;
    TCPServer = nullptr;

    spam_timer = nullptr;
    connection_timer = nullptr;

    sockets.squeeze();

    delete ui;
}

void MainWindow::read_data(void) // Поступили данные
{
    if (mode == 1)
    {
        for (int i = 0; i < sockets.size(); i++)
        {
            QByteArray ba;

            ba = sockets[i]->readAll();

            if (!ba.isEmpty())
            {
                ui->textEdit_Input->append(ba);
                for (int j = 0; j < i; j++)
                    sockets[j]->write(ba);
                for (int j = i+1; j < sockets.size(); j++)
                    sockets[j]->write(ba);
            }
        }
    }
    else if (mode == 2) {

        QByteArray ba;

        ba = clientSocket->readAll();
        QString stroka(ba);

        if (!stroka.isEmpty())
            ui->textEdit_Input->append(stroka);
    }
}

void MainWindow::new_connection(void) // Подключился клиент
{
    clients++;
    QTcpSocket * TCPSocket = new QTcpSocket(this);
    TCPSocket = TCPServer->nextPendingConnection();
    connect(TCPSocket, SIGNAL(readyRead()), this, SLOT(read_data()));
    connect(TCPSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    sockets.append(TCPSocket);

    disconnect(TCPServer, SIGNAL(newConnection()), this, SLOT(new_connection()));

    connection_timer->start();

    ui->textEdit_Input->show();
    ui->lineEdit_SendMes->show();
    ui->pushButton_SendMes->show();
    ui->lineEdit_Spam->show();
    ui->pushButton_SPAM->show();
    ui->pushButton_Emoji_2->show();
    ui->pushButton_SPAM->setEnabled(false);

    connect(TCPServer, SIGNAL(newConnection()), this, SLOT(new_connection()));
}

void MainWindow::disconnected(void) // клиент отключился
{
    if (mode == 1)
    {
        //        for (int i = 0; i < sockets.size(); i++)
        //        {
        //            if (sockets[i]->state() == QAbstractSocket::UnconnectedState)
        //            {
        //                if (i != sockets.size()-1)
        //                {
        //                    std::swap(sockets[i], sockets[sockets.size()-1]);
        //                }
        //                sockets[sockets.size()-1]->abort();
        //                delete sockets[sockets.size()-1];
        //                sockets.pop_back();
        //                clients--;
//        ui->textEdit_Input->append("Client disconnected");
        //            }
        //        }
    }
    else if (mode == 2)
    {
        ui->pushButton_Disconnect->hide();
        ui->pushButton_Settings->setEnabled(true);
        ui->pushButton_SendMes->hide();
        ui->textEdit_Input->append("Disconnected");

        on_pushButton_Stop_clicked();/*
        ui->lineEdit_Spam->hide();*/
        ui->pushButton_SPAM->hide();
        ui->pushButton_Stop->hide();/*
        ui->pushButton_Emoji_2->hide();*/
        ui->label->clear();
    }
}

void MainWindow::on_pushButton_SendMes_clicked() // Отправка сообщения
{
    if (mode == 1)
    {
        QByteArray ba;
        for (int j = 0; j < 1; j++)
        {
            ba.append(nick + ": " + ui->lineEdit_SendMes->text().toUtf8());
            ui->textEdit_Input->append(ba);
            for (int i = 0; i < sockets.size(); i++)
            {
                sockets[i]->write(ba);
            }
        }
    }
    else if (mode == 2)
    {
        QByteArray ba;
        ba.append(nick + ": " + ui->lineEdit_SendMes->text().toUtf8());
        clientSocket->write(ba);
        ui->textEdit_Input->append(ba);
    }
}

// 1) Проверки - done
// 2) Русский язык - done
// 3) Вывод своего IP - done
// 4) Добавить код на обрыв соединения - done
// 5) Добавить защиту от повторного подключения - done
// 6) СПАМ - done
// 7) Бонусная задача: добавить фильтр выражений, добавить передачу картинок, файлов

void MainWindow::on_pushButton_Settings_clicked() // Нажата кнопка настроек
{
    Dialog_settings dialog;
    if (!first)
    {
        dialog.printNick(nick);
        dialog.printPort(port);
        dialog.printAdress(string_adress);
    }
    dialog.exec();

    if (dialog.mode == 2) // Клиент подключается к серверу
    {
        nick = dialog.getNick();
        port = dialog.getPort();
        string_adress = dialog.getAdress();
        QHostAddress * adress;

        adress = new QHostAddress;
        adress->setAddress(string_adress);

        clientSocket->connectToHost(*adress, quint16(port));

        if (clientSocket->waitForConnected(1000))
        {
            connect(clientSocket, SIGNAL(readyRead()), this, SLOT(read_data()));
            ui->pushButton_SendMes->setVisible(true);

            first = false;

            ui->label->setText("Клиент");

            ui->lineEdit_SendMes->show();
            ui->pushButton_SendMes->show();
            ui->pushButton_SPAM->show();
            ui->lineEdit_Spam->show();
            ui->pushButton_Emoji_2->show();
            ui->pushButton_SPAM->setEnabled(true);
            mode = 2;

            ui->pushButton_Disconnect->show();
            ui->pushButton_Settings->setEnabled(false);

            QByteArray ba;
            ba.append(nick + " connected");
            clientSocket->write(ba);

            if (ui->lineEdit_SendMes->text().isEmpty())
                ui->pushButton_SendMes->setEnabled(false);
            else
                ui->pushButton_SendMes->setEnabled(true);

            if (ui->lineEdit_Spam->text().isEmpty())
                ui->pushButton_SPAM->setEnabled(false);
            else
                ui->pushButton_SPAM->setEnabled(true);
        }
        else
        {
            clientSocket->abort();
            on_pushButton_Disconnect_clicked();
            QMessageBox::information(this, "Ошибка", "Данный сервер занят или не существует", QMessageBox::Ok);
        }
    }

    else if (dialog.mode == 1) // Создан сервер
    {
        clients = 0;
        mode = 1;
        nick = dialog.getNick();
        port = dialog.getPort();
        ui->pushButton_Disconnect->hide();
        ui->pushButton_ServerOff->show();

        TCPServer->listen(QHostAddress::Any, quint16(port));

        if (TCPServer->isListening())
        {
            connect(TCPServer, SIGNAL(newConnection()), this, SLOT(new_connection()));

            first = false;

            ui->label->setText("Сервер");
            ui->pushButton_Settings->setEnabled(false);
        }
        else
        {
            QMessageBox::information(this, "Ошибка", "Данный сервер занят", QMessageBox::Ok);
            on_pushButton_ServerOff_clicked();
        }
    }
}

void MainWindow::on_pushButton_Emoji_clicked() // Нажата кнопка эмоджи
{
    Dialog_emoji dialog;
    connect(&dialog, SIGNAL(newEmoji(QString)), this, SLOT(printEmojis(QString)));
    dialog.exec();
}

void MainWindow::printEmojis(QString new_emoji) // вывод эмоджи в лайн эдит
{
    ui->lineEdit_SendMes->setText(ui->lineEdit_SendMes->text() + new_emoji);
}

void MainWindow::on_pushButton_Disconnect_clicked() // Нажата кнопка отключиться от сервера
{
    QByteArray ba;
    ba.append(nick + " disconnected");
    clientSocket->write(ba);
    on_pushButton_Stop_clicked();
    ui->pushButton_Disconnect->hide();
    ui->pushButton_Settings->setEnabled(true);
    ui->pushButton_SendMes->hide();
    ui->pushButton_SPAM->hide();
    ui->pushButton_Stop->hide();

    clientSocket->waitForDisconnected(10);
    clientSocket->disconnectFromHost();
    clientSocket->abort();

    ui->label->clear();
    mode = 0;

}

void MainWindow::on_pushButton_ServerOff_clicked() // Нажата кнопка отключить сервер
{
    on_pushButton_Stop_clicked();
    for (int i = 0; i < sockets.size(); i++) {
        sockets[i]->write("Server off");
    }
    ui->pushButton_ServerOff->hide();
    ui->pushButton_Settings->setEnabled(true);
    ui->pushButton_SendMes->hide();

    ui->pushButton_SPAM->hide();
    ui->pushButton_Stop->hide();

    for (int i = 0; i < sockets.size(); i++) {
        //        disconnect(sockets[i], SIGNAL(disconnected()), this, SLOT(disconnected()));
        sockets[i]->abort();
        sockets[i]->disconnectFromHost();
        sockets[i]->disconnect();
        delete sockets[i];
        sockets[i] = nullptr;
        sockets.clear();
    }

    ui->textEdit_Input->append("Server off");

    //    disconnect(TCPServer, SIGNAL(newConnection()), this, SLOT(new_connection()));
    TCPServer->close();
    ui->label->clear();

    clients = 0;
    mode = 0;
}


void MainWindow::on_pushButton_SPAM_clicked() // Нажата кнопка СПАМ
{
    QString message = nick + ":" + ui->lineEdit_Spam->text();
    spam_ba = message.toUtf8();
    spam_timer->start(200);

    ui->pushButton_SPAM->hide();
    ui->pushButton_Stop->show();
    ui->lineEdit_Spam->setEnabled(false);
    ui->pushButton_Emoji_2->setEnabled(false);
}

void MainWindow::spam() // функция отпарвки спама
{
    if (mode == 1)
    {
        for (int i = 0; i < sockets.size(); i++)
        {
            sockets[i]->write(spam_ba);
        }
        ui->textEdit_Input->append(spam_ba);
    }
    else if (mode == 2) {
        clientSocket->write(spam_ba);
        ui->textEdit_Input->append(spam_ba);
    }
}

void MainWindow::on_pushButton_Stop_clicked() // нажата кнопка стоп
{
    spam_timer->stop();

    ui->lineEdit_Spam->setEnabled(true);
    ui->pushButton_Emoji_2->setEnabled(true);
    ui->pushButton_SPAM->show();
    ui->pushButton_Stop->hide();
}

void MainWindow::connection_state(void) // проверка подключения
{
    if (mode == 1)
    {
        if (sockets.size() == 0)
        {
            ui->pushButton_SendMes->hide();/*
            ui->lineEdit_Spam->hide();*/
            on_pushButton_Stop_clicked();/*
            ui->pushButton_Emoji_2->hide();*/
            ui->pushButton_SPAM->hide();
        }
        for (auto i : sockets)
        {
            if (i->state() == QAbstractSocket::UnconnectedState)
            {
                delete i;
                sockets.removeOne(i);
            }
        }
    }

    if (mode == 2)
        if (clientSocket->state() == QAbstractSocket::UnconnectedState)
        {
            on_pushButton_Disconnect_clicked();
            QMessageBox::information(this, "Ошибка", "Данный сервер занят или не существует", QMessageBox::Ok);
        }
}

void MainWindow::on_lineEdit_SendMes_textChanged() // Изменен лайнЭдит отправки сообщения
{
    if (ui->lineEdit_SendMes->text().isEmpty())
        ui->pushButton_SendMes->setEnabled(false);

    else
        ui->pushButton_SendMes->setEnabled(true);
}

void MainWindow::on_lineEdit_Spam_textChanged() // Изменен лайн эдит спама
{
    if (ui->lineEdit_Spam->text().isEmpty())
        ui->pushButton_SPAM->setEnabled(false);

    else
        ui->pushButton_SPAM->setEnabled(true);
}

void MainWindow::on_pushButton_Emoji_2_clicked() // нажата кнопка emoji для спама
{
    Dialog_emoji dialog;
    connect(&dialog, SIGNAL(newEmoji(QString)), this, SLOT(printEmojisSpam(QString)));
    dialog.exec();
}

void MainWindow::printEmojisSpam(QString new_emoji) // вывод эмоджи в лайн эдит
{
    ui->lineEdit_Spam->setText(ui->lineEdit_Spam->text() + new_emoji);
}

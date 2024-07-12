#include "dialog_settings.h"
#include "ui_dialog_settings.h"

Dialog_settings::Dialog_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_settings) // Конструктор
{
    ui->setupUi(this);

    ui->pushButton_Create->hide();
    ui->pushButton_Connect->hide();


    ui->label_Port->hide();
    ui->label_Adress->hide();
    ui->label_Nick->hide();

    ui->lineEdit_Port->hide();
    ui->lineEdit_Adress->hide();
    ui->lineEdit_Nick->hide();
    ui->line->hide();
    ui->comboBox->hide();

    // Контроль ввода IP-адреса
    QRegExp regExp("(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");
    ipValidator = new QRegExpValidator(regExp, this);
    ui->lineEdit_Adress->setValidator(ipValidator);
    //    ui->lineEdit_Adress->setInputMask("000.000.000.000");
    ui->lineEdit_Adress->setCursorPosition(0);

    // Контроль ввода портов
    portValidator = new QIntValidator(1, 65536, this);
    ui->lineEdit_Port->setValidator(portValidator);

    setIpRegex(regExp);

    setWindowTitle("Настройки");

    mode = 0;

    //    point = ui->pushButton_Create->pos();
    //    point.setY(350);
    //    ui->pushButton_Create->move(point);

    getMyIP();

}

Dialog_settings::~Dialog_settings() // Деструктор
{
    delete ui;
}

void Dialog_settings::printNick(QString print_nick) // записать наш ник при повторном посещении окна
{
    ui->lineEdit_Nick->setText(print_nick);
}

void Dialog_settings::printPort(int print_port) // записать порт при повторном посещении окна
{
    ui->lineEdit_Port->setText(QString::number(print_port));
}

void Dialog_settings::printAdress(QString print_adress) // записать адрес при повторном посещении окна
{
    ui->lineEdit_Adress->setText(print_adress);
}


void Dialog_settings::getMyIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for(int i = 0; i < list.count(); i++)
    {
        if(!list[i].isLoopback())
            if (list[i].protocol() == QAbstractSocket::IPv4Protocol )
                ui->comboBox->addItem(list[i].toString());
    }
}

bool Dialog_settings::checkPort()
{
    int port = ui->lineEdit_Port->text().toInt();

    if (port > 0)
        return true;
    else
        return false;
}

bool Dialog_settings::checkNickname() // проверка никнейма
{
    if (ui->lineEdit_Nick->text().isEmpty())
        return false;
    else
        return true;
}

bool Dialog_settings::checkAdress() // проверка IP адреса
{
    if (getIpRegex().exactMatch(ui->lineEdit_Adress->text()))
        return true;
    else
        return false;
}

void Dialog_settings::setIpRegex(QRegExp new_ipRegex) // сеттер шаблона для валидатора
{
    ipRegex = new_ipRegex;
}

QRegExp Dialog_settings::getIpRegex() // геттер шаблона для валидатора
{
    return ipRegex;
}

void Dialog_settings::setPort(int new_port) // сеттер порта
{
    port = new_port;
}

void Dialog_settings::setAdress(QString new_adress_string) // сеттер адреса
{
    adress_string = new_adress_string;
}

void Dialog_settings::setNick(QString new_nick) // сеттер ника
{
    nick = new_nick;
}

int Dialog_settings::getPort() // геттер порта
{
    return port;
}

QString Dialog_settings::getAdress() // геттер адреса
{
    return adress_string;
}

QString Dialog_settings::getNick() // геттер ника
{
    return nick;
}

void Dialog_settings::on_radioButton_Client_clicked() // Выбран режим клиента
{
    ui->pushButton_Create->hide();
    ui->pushButton_Connect->show();

    ui->label_Port->show();
    ui->label_Adress->show();

    ui->lineEdit_Port->show();
    ui->lineEdit_Adress->show();

    QPoint point;
    point = ui->label_Port->pos();
    point.setY(180);
    ui->label_Port->move(point);

    point = ui->lineEdit_Port->pos();
    point.setY(180);
    ui->lineEdit_Port->move(point);

    point = ui->line->pos();
    point.setY(240);
    ui->line->move(point);

    ui->label_Nick->show();
    ui->lineEdit_Nick->show();
    ui->comboBox->show();
    ui->line->show();
}

void Dialog_settings::on_radioButton_Server_clicked() // Выбран режим сервера
{
    ui->pushButton_Create->show();
    ui->pushButton_Connect->hide();

    ui->label_Port->show();
    ui->label_Adress->hide();

    ui->lineEdit_Port->show();
    ui->lineEdit_Adress->hide();

    QPoint point;
    point = ui->label_Port->pos();
    point.setY(110);
    ui->label_Port->move(point);

    point = ui->lineEdit_Port->pos();
    point.setY(110);
    ui->lineEdit_Port->move(point);

    point = ui->line->pos();
    point.setY(170);
    ui->line->move(point);

    ui->label_Nick->show();
    ui->lineEdit_Nick->show();
    ui->comboBox->show();
    ui->line->show();
}

void Dialog_settings::on_pushButton_Create_clicked() // нажата кнопка создать
{
    if (checkPort() and checkNickname())
    {
        setPort(ui->lineEdit_Port->text().toInt());
        setNick(ui->lineEdit_Nick->text().toUtf8());
        mode = 1;
        Dialog_settings::close();
    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Неверно введены данные", QMessageBox::Ok);
        mode = 0;
    }
}

void Dialog_settings::on_pushButton_Connect_clicked() // нажата кнопка подключиться
{
    if (checkPort() and checkAdress() and checkNickname())
    {
        mode = 2;
        setPort(ui->lineEdit_Port->text().toInt());
        setNick(ui->lineEdit_Nick->text().toUtf8());
        setAdress(ui->lineEdit_Adress->text().toUtf8());
        Dialog_settings::close();
    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Неверно введены данные", QMessageBox::Ok);
        mode = 0;
    }
}


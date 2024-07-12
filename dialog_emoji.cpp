#include "dialog_emoji.h"
#include "ui_dialog_emoji.h"

Dialog_emoji::Dialog_emoji(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_emoji) // конструктор
{
    ui->setupUi(this);

    setWindowTitle("Эмоджи");

    on_radioButton_clicked();
    ui->radioButton->setChecked(true);
}

Dialog_emoji::~Dialog_emoji() // Деструктор
{
    delete ui;
}

void Dialog_emoji::on_radioButton_clicked() // нажата радиокнопка 1
{
    ui->pushButton->setText("😂");
    ui->pushButton_2->setText("❤");
    ui->pushButton_3->setText("😍");
    ui->pushButton_4->setText("🤣");
    ui->pushButton_5->setText("😊");
    ui->pushButton_6->setText("🙏");
    ui->pushButton_7->setText("💕");
    ui->pushButton_8->setText("😭");
    ui->pushButton_9->setText("🔥");
    ui->pushButton_10->setText("😘");
}

void Dialog_emoji::on_radioButton_2_clicked() // нажата радиокнопка 2
{
    ui->pushButton->setText("👍");
    ui->pushButton_2->setText("🥰");
    ui->pushButton_3->setText("😎");
    ui->pushButton_4->setText("😆");
    ui->pushButton_5->setText("😁");
    ui->pushButton_6->setText("😉");
    ui->pushButton_7->setText("🤔");
    ui->pushButton_8->setText("😅");
    ui->pushButton_9->setText("😔");
    ui->pushButton_10->setText("🙄");
}

void Dialog_emoji::on_radioButton_3_clicked() // нажата радиокнопка 3
{
    ui->pushButton->setText("😜");
    ui->pushButton_2->setText("♥");
    ui->pushButton_3->setText("♻");
    ui->pushButton_4->setText("😒");
    ui->pushButton_5->setText("😩");
    ui->pushButton_6->setText("☺");
    ui->pushButton_7->setText("😁");
    ui->pushButton_8->setText("👌");
    ui->pushButton_9->setText("👏");
    ui->pushButton_10->setText("💔");
}

void Dialog_emoji::on_radioButton_4_clicked() // нажата радиокнопка 4
{
    ui->pushButton->setText("💖");
    ui->pushButton_2->setText("💙");
    ui->pushButton_3->setText("😢");
    ui->pushButton_4->setText("💪");
    ui->pushButton_5->setText("🤗");
    ui->pushButton_6->setText("💜");
    ui->pushButton_7->setText("😎");
    ui->pushButton_8->setText("😇");
    ui->pushButton_9->setText("🌹");
    ui->pushButton_10->setText("🤦");
}

void Dialog_emoji::on_radioButton_5_clicked() // нажата радиокнопка 5
{
    ui->pushButton->setText("🎉");
    ui->pushButton_2->setText("💞");
    ui->pushButton_3->setText("✌");
    ui->pushButton_4->setText("✨");
    ui->pushButton_5->setText("🤷");
    ui->pushButton_6->setText("😱");
    ui->pushButton_7->setText("😌");
    ui->pushButton_8->setText("🌸");
    ui->pushButton_9->setText("🙌");
    ui->pushButton_10->setText("😋");
}

void Dialog_emoji::on_pushButton_clicked() // нажата кнопка 1 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "😂";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "👍";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "😜";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "💖";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "🎉";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_2_clicked() // нажата кнопка 2 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "❤";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "🥰";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "♥";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "💙";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "💞";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_3_clicked() // нажата кнопка 3 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "😍";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "😎";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "♻";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "😢";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "✌";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_4_clicked() // нажата кнопка 4 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "🤣";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "😆";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "😒";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "💪";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "✨";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_5_clicked() // нажата кнопка 5 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "😊";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "😁";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "😩";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "🤗";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "🤷";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_6_clicked() // нажата кнопка 6 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "🙏";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "😉";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "☺";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "💜";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "😱";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_7_clicked() // нажата кнопка 7 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "💕";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "🤔";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "😁";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "😎";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "😌";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_8_clicked() // нажата кнопка 8 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "😭";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "😅";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "👌";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "😇";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "🌸";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_9_clicked() // нажата кнопка 9 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "🔥";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "😔";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "👏";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "🌹";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "🙌";
        emit newEmoji(new_emoji);
    }
}

void Dialog_emoji::on_pushButton_10_clicked() // нажата кнопка 10 символа
{
    if (ui->radioButton->isChecked())
    {
        QString new_emoji = "😘";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_2->isChecked()) {
        QString new_emoji = "🙄";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_3->isChecked()) {
        QString new_emoji = "💔";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_4->isChecked()) {
        QString new_emoji = "🤦";
        emit newEmoji(new_emoji);
    }
    else if (ui->radioButton_5->isChecked()) {
        QString new_emoji = "😋";
        emit newEmoji(new_emoji);
    }
}








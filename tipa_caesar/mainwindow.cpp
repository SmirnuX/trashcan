#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    UpdateKeyTable();

    connect(ui->keyEdit, SIGNAL(textChanged()), this, SLOT(UpdateKeyTable()));
    connect(ui->shiftBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateKeyTable()));
    connect(ui->decodeButton, SIGNAL(clicked(bool)), this, SLOT(DecodeText()));
    connect(ui->encodeButton, SIGNAL(clicked(bool)), this, SLOT(EncodeText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateShift(int sh)
{
    shift = sh;
}

void MainWindow::UpdateKeyTable()
{
    QString temp_key = ui->keyEdit->toPlainText();
    bool error = CheckAlphabet(temp_key);
    QTextCursor curs = ui->keyEdit->textCursor();
    if (temp_key != ui->keyEdit->toPlainText())
    {
        ui->keyEdit->setPlainText(temp_key);
        ui->keyEdit->setTextCursor(curs);
    }
    ShowKeyError(!error);

    if (!error)
        return;

    key = ui->keyEdit->toPlainText();
    shift = ui->shiftBox->value();

    bool used_lets[33] = {false};

    int i = shift;
    while (i < 0)
        i += 33;

    for (QChar a : key)
    {
        if (!used_lets[tonum(a)])
        {
            table[i] = a;
            used_lets[tonum(a)] = true;
            i++;
            if (i >= 33)
                i = 0;
        }
    }

    for (int j = 0; j < 33; j++)
    {
        if (!used_lets[j])
        {
            table[i] = tolet(j);
            used_lets[j] = true;
            i++;
            if (i >= 33)
                i = 0;
        }
    }

    for (int j = 0; j < 11; j++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(table[j]);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tableRow1->setItem(0, j, newItem);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(table[j+11]);
        newItem2->setTextAlignment(Qt::AlignHCenter);
        ui->tableRow2->setItem(0, j, newItem2);
        QTableWidgetItem *newItem3 = new QTableWidgetItem(table[j+22]);
        newItem3->setTextAlignment(Qt::AlignHCenter);
        ui->tableRow3->setItem(0, j, newItem3);
    }
}


bool MainWindow::CheckAlphabet(QString& str)    //Checks if str contains wrong characters and moves all character to uppercase
{
    bool res = true;
    for (int i = 0; i < str.length(); i++)
    {
        if (tonum(str[i]) >= 0)
            continue;
        else if (tonum(str[i].toUpper()) >= 0)
            str.replace(i, 1, str[i].toUpper());
        else
            res = false;
    }
    return res;
}


void MainWindow::ShowEncodedError(bool visibility) //Shows error
{
    ui->encodedErrorLabel->setVisible(visibility);
}

void MainWindow::ShowDecodedError(bool visibility)
{
    ui->decodedErrorLabel->setVisible(visibility);
}

void MainWindow::ShowKeyError(bool visibility)
{
    ui->keyErrorLabel->setVisible(visibility);
}

void MainWindow::EncodeText()
{
    QString decoded_text = ui->decodedTextEdit->toPlainText();
    CheckAlphabet(decoded_text);
    QTextCursor curs = ui->decodedTextEdit->textCursor();
    if (decoded_text != ui->keyEdit->toPlainText())
    {
        ui->decodedTextEdit->setPlainText(decoded_text);
        ui->decodedTextEdit->setTextCursor(curs);
    }

    QString result = "";
    for(QChar c : decoded_text)
    {
        if (tonum(c) < 0)
            continue;
        result.append(table[tonum(c)]);
    }
    ui->encodedTextEdit->setPlainText(result);
}

void MainWindow::DecodeText()
{
    QString encoded_text = ui->encodedTextEdit->toPlainText();
    CheckAlphabet(encoded_text);
    QTextCursor curs = ui->encodedTextEdit->textCursor();
    if (encoded_text != ui->keyEdit->toPlainText())
    {
        ui->encodedTextEdit->setPlainText(encoded_text);
        ui->encodedTextEdit->setTextCursor(curs);
    }

    QString result = "";
    for(QChar c : encoded_text)
    {
        for (int i = 0; i < 33; i++)
        {
            if (table[i] == c)
            {
               result.append(tolet(i));
               break;
            }
        }
    }

    ui->decodedTextEdit->setPlainText(result);
}

QChar MainWindow::tolet(int n)
{
    if (n == -1)
        return QChar(' ');
    return rus_lets[n];
}

int MainWindow::tonum(QChar c)
{
    for (int i = 0; i < 33; i++)    //WORST IDEA EVER
    {
        if (rus_lets[i] == c)
            return i;
    }
    return -1;
}

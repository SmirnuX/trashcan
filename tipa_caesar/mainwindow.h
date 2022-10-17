#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const QString rus_lets = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void UpdateShift(int sh);
    bool CheckAlphabet(QString& str);    //Checks if str contains wrong characters and moves all character to uppercase
    void ShowEncodedError(bool visibility); //Shows error
    void ShowDecodedError(bool visibility);
    void ShowKeyError(bool visibility);

    QChar tolet(int n);
    int tonum(QChar c);

    ~MainWindow();

public slots:
    void UpdateKeyTable();
    void EncodeText();
    void DecodeText();

private:
    Ui::MainWindow *ui;
    QString encoded; //Encoded text
    QString decoded; //Decoded text
    int shift = 0;
    QString key; //Keyword
    QChar table[33];



};
#endif // MAINWINDOW_H

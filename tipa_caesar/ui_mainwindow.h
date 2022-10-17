/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPlainTextEdit *encodedTextEdit;
    QLabel *label;
    QPlainTextEdit *decodedTextEdit;
    QLabel *label_2;
    QTableWidget *tableRow1;
    QTableWidget *tableRow2;
    QTableWidget *tableRow3;
    QLabel *label_3;
    QPlainTextEdit *keyEdit;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *shiftBox;
    QPushButton *encodeButton;
    QPushButton *decodeButton;
    QLabel *keyErrorLabel;
    QLabel *encodedErrorLabel;
    QLabel *decodedErrorLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(890, 607);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        encodedTextEdit = new QPlainTextEdit(centralwidget);
        encodedTextEdit->setObjectName(QString::fromUtf8("encodedTextEdit"));
        encodedTextEdit->setGeometry(QRect(40, 60, 371, 221));
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        font.setPointSize(12);
        encodedTextEdit->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 10, 201, 51));
        label->setTextFormat(Qt::PlainText);
        label->setScaledContents(false);
        decodedTextEdit = new QPlainTextEdit(centralwidget);
        decodedTextEdit->setObjectName(QString::fromUtf8("decodedTextEdit"));
        decodedTextEdit->setGeometry(QRect(40, 370, 371, 221));
        decodedTextEdit->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 320, 201, 51));
        label_2->setTextFormat(Qt::PlainText);
        label_2->setScaledContents(false);
        tableRow1 = new QTableWidget(centralwidget);
        if (tableRow1->columnCount() < 11)
            tableRow1->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableRow1->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        if (tableRow1->rowCount() < 1)
            tableRow1->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableRow1->setVerticalHeaderItem(0, __qtablewidgetitem11);
        tableRow1->setObjectName(QString::fromUtf8("tableRow1"));
        tableRow1->setGeometry(QRect(460, 60, 396, 91));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Courier New")});
        font1.setPointSize(22);
        font1.setBold(true);
        QFont font_nbold;
        font_nbold.setFamilies({QString::fromUtf8("Courier New")});
        font_nbold.setPointSize(22);
        tableRow1->setFont(font_nbold);
        tableRow1->setFrameShape(QFrame::Box);
        tableRow1->setFrameShadow(QFrame::Plain);
        tableRow1->setLineWidth(2);
        tableRow1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableRow1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableRow1->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableRow1->setTextElideMode(Qt::ElideMiddle);
        tableRow1->setShowGrid(true);
        tableRow1->setWordWrap(false);
        tableRow1->setCornerButtonEnabled(false);
        tableRow1->setRowCount(1);
        tableRow1->horizontalHeader()->setVisible(true);
        tableRow1->horizontalHeader()->setMinimumSectionSize(36);
        tableRow1->horizontalHeader()->setDefaultSectionSize(36);
        tableRow1->horizontalHeader()->setHighlightSections(true);
        tableRow1->horizontalHeader()->setStretchLastSection(false);
        tableRow1->horizontalHeader()->setFont(font1);
        tableRow1->verticalHeader()->setVisible(false);
        tableRow1->verticalHeader()->setMinimumSectionSize(36);
        tableRow1->verticalHeader()->setDefaultSectionSize(36);
        tableRow1->verticalHeader()->setHighlightSections(false);
        tableRow1->verticalHeader()->setStretchLastSection(true);
        tableRow2 = new QTableWidget(centralwidget);
        if (tableRow2->columnCount() < 11)
            tableRow2->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(6, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(7, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(8, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(9, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableRow2->setHorizontalHeaderItem(10, __qtablewidgetitem22);
        if (tableRow2->rowCount() < 1)
            tableRow2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableRow2->setVerticalHeaderItem(0, __qtablewidgetitem23);
        tableRow2->setObjectName(QString::fromUtf8("tableRow2"));
        tableRow2->setGeometry(QRect(460, 160, 396, 91));
        tableRow2->setFont(font_nbold);
        tableRow2->setFrameShape(QFrame::Box);
        tableRow2->setFrameShadow(QFrame::Plain);
        tableRow2->setLineWidth(2);
        tableRow2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableRow2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableRow2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableRow2->setTextElideMode(Qt::ElideMiddle);
        tableRow2->setShowGrid(true);
        tableRow2->setWordWrap(false);
        tableRow2->setCornerButtonEnabled(false);
        tableRow2->setRowCount(1);
        tableRow2->horizontalHeader()->setVisible(true);
        tableRow2->horizontalHeader()->setMinimumSectionSize(36);
        tableRow2->horizontalHeader()->setDefaultSectionSize(36);
        tableRow2->horizontalHeader()->setHighlightSections(true);
        tableRow2->horizontalHeader()->setStretchLastSection(false);
        tableRow2->horizontalHeader()->setFont(font1);
        tableRow2->verticalHeader()->setVisible(false);
        tableRow2->verticalHeader()->setMinimumSectionSize(36);
        tableRow2->verticalHeader()->setDefaultSectionSize(36);
        tableRow2->verticalHeader()->setHighlightSections(false);
        tableRow2->verticalHeader()->setStretchLastSection(true);
        tableRow3 = new QTableWidget(centralwidget);
        if (tableRow3->columnCount() < 11)
            tableRow3->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(1, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(2, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(3, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(4, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(5, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(6, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(7, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(8, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(9, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableRow3->setHorizontalHeaderItem(10, __qtablewidgetitem34);
        if (tableRow3->rowCount() < 1)
            tableRow3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableRow3->setVerticalHeaderItem(0, __qtablewidgetitem35);
        tableRow3->setObjectName(QString::fromUtf8("tableRow3"));
        tableRow3->setGeometry(QRect(460, 260, 396, 91));
        tableRow3->setFont(font_nbold);
        tableRow3->setFrameShape(QFrame::Box);
        tableRow3->setFrameShadow(QFrame::Plain);
        tableRow3->setLineWidth(2);
        tableRow3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableRow3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableRow3->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableRow3->setTextElideMode(Qt::ElideMiddle);
        tableRow3->setShowGrid(true);
        tableRow3->setWordWrap(false);
        tableRow3->setCornerButtonEnabled(false);
        tableRow3->setRowCount(1);
        tableRow3->horizontalHeader()->setVisible(true);
        tableRow3->horizontalHeader()->setMinimumSectionSize(36);
        tableRow3->horizontalHeader()->setDefaultSectionSize(36);
        tableRow3->horizontalHeader()->setHighlightSections(true);
        tableRow3->horizontalHeader()->setStretchLastSection(false);
        tableRow3->horizontalHeader()->setFont(font1);
        tableRow3->verticalHeader()->setVisible(false);
        tableRow3->verticalHeader()->setMinimumSectionSize(36);
        tableRow3->verticalHeader()->setDefaultSectionSize(36);
        tableRow3->verticalHeader()->setHighlightSections(false);
        tableRow3->verticalHeader()->setStretchLastSection(true);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(460, 10, 201, 51));
        label_3->setTextFormat(Qt::PlainText);
        label_3->setScaledContents(false);
        keyEdit = new QPlainTextEdit(centralwidget);
        keyEdit->setObjectName(QString::fromUtf8("keyEdit"));
        keyEdit->setGeometry(QRect(450, 420, 401, 41));
        keyEdit->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(450, 380, 201, 51));
        label_4->setTextFormat(Qt::PlainText);
        label_4->setScaledContents(false);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(450, 520, 201, 21));
        label_5->setTextFormat(Qt::PlainText);
        label_5->setScaledContents(false);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        shiftBox = new QSpinBox(centralwidget);
        shiftBox->setObjectName(QString::fromUtf8("shiftBox"));
        shiftBox->setGeometry(QRect(580, 520, 42, 26));
        shiftBox->setMinimum(-33);
        shiftBox->setMaximum(33);
        encodeButton = new QPushButton(centralwidget);
        encodeButton->setObjectName(QString::fromUtf8("encodeButton"));
        encodeButton->setGeometry(QRect(680, 500, 171, 29));
        decodeButton = new QPushButton(centralwidget);
        decodeButton->setObjectName(QString::fromUtf8("decodeButton"));
        decodeButton->setGeometry(QRect(680, 550, 171, 29));
        keyErrorLabel = new QLabel(centralwidget);
        keyErrorLabel->setObjectName(QString::fromUtf8("keyErrorLabel"));
        keyErrorLabel->setEnabled(true);
        keyErrorLabel->setGeometry(QRect(450, 470, 401, 21));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        keyErrorLabel->setPalette(palette);
        keyErrorLabel->setTextFormat(Qt::PlainText);
        keyErrorLabel->setScaledContents(false);
        encodedErrorLabel = new QLabel(centralwidget);
        encodedErrorLabel->setObjectName(QString::fromUtf8("encodedErrorLabel"));
        encodedErrorLabel->setEnabled(true);
        encodedErrorLabel->setGeometry(QRect(40, 290, 371, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        encodedErrorLabel->setPalette(palette1);
        encodedErrorLabel->setTextFormat(Qt::PlainText);
        encodedErrorLabel->setScaledContents(false);
        decodedErrorLabel = new QLabel(centralwidget);
        decodedErrorLabel->setObjectName(QString::fromUtf8("decodedErrorLabel"));
        decodedErrorLabel->setEnabled(true);
        decodedErrorLabel->setGeometry(QRect(40, 600, 371, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        decodedErrorLabel->setPalette(palette2);
        decodedErrorLabel->setTextFormat(Qt::PlainText);
        decodedErrorLabel->setScaledContents(false);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        encodedTextEdit->setPlaceholderText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\210\320\270\321\204\321\200\320\276\320\262\320\260\320\275\320\275\321\213\320\271 \321\202\320\265\320\272\321\201\321\202", nullptr));
        decodedTextEdit->setPlaceholderText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\210\320\270\321\204\321\200\320\276\320\262\320\260\320\275\320\275\321\213\320\271 \321\202\320\265\320\272\321\201\321\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableRow1->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableRow1->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\221", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableRow1->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\222", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableRow1->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\320\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableRow1->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\320\224", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableRow1->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableRow1->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\320\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableRow1->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\320\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableRow1->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\320\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableRow1->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\320\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableRow1->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\320\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableRow1->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableRow2->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "\320\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableRow2->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "\320\233", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableRow2->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "\320\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableRow2->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "\320\235", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableRow2->horizontalHeaderItem(4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "\320\236", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableRow2->horizontalHeaderItem(5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "\320\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableRow2->horizontalHeaderItem(6);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "\320\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableRow2->horizontalHeaderItem(7);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "\320\241", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableRow2->horizontalHeaderItem(8);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "\320\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableRow2->horizontalHeaderItem(9);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "\320\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableRow2->horizontalHeaderItem(10);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "\320\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableRow2->verticalHeaderItem(0);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableRow3->horizontalHeaderItem(0);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "\320\245", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableRow3->horizontalHeaderItem(1);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "\320\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableRow3->horizontalHeaderItem(2);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "\320\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableRow3->horizontalHeaderItem(3);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "\320\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableRow3->horizontalHeaderItem(4);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "\320\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableRow3->horizontalHeaderItem(5);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "\320\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableRow3->horizontalHeaderItem(6);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "\320\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableRow3->horizontalHeaderItem(7);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "\320\254", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableRow3->horizontalHeaderItem(8);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "\320\255", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableRow3->horizontalHeaderItem(9);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("MainWindow", "\320\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableRow3->horizontalHeaderItem(10);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("MainWindow", "\320\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableRow3->verticalHeaderItem(0);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\242\320\260\320\261\320\273\320\270\321\206\320\260 \320\264\320\273\321\217 \321\210\320\270\321\204\321\200\320\276\320\262\320\272\320\270", nullptr));
        keyEdit->setPlaceholderText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\232\320\273\321\216\321\207 \321\210\320\270\321\204\321\200\320\260", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        encodeButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        decodeButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        keyErrorLabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\273\321\216\321\207 \320\264\320\276\320\273\320\266\320\265\320\275 \321\201\320\276\321\201\321\202\320\276\321\217\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276 \320\270\320\267 \320\261\321\203\320\272\320\262 \321\200\321\203\321\201\321\201\320\272\320\276\320\263\320\276 \320\260\320\273\321\204\320\260\320\262\320\270\321\202\320\260", nullptr));
        encodedErrorLabel->setText(QString());
        decodedErrorLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

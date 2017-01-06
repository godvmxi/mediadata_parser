/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *fileWidget;
    QHBoxLayout *fileWidgetHorizontalLayout;
    QLabel *openLabel;
    QLineEdit *filePathLineEdit;
    QPushButton *openPushButton;
    QWidget *h264Widget;
    QHBoxLayout *horizontalLayout;
    QSplitter *nalSplitter;
    QTableView *nalTableView;
    QPlainTextEdit *nalPlainTextEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(721, 473);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        fileWidget = new QWidget(centralWidget);
        fileWidget->setObjectName(QStringLiteral("fileWidget"));
        fileWidgetHorizontalLayout = new QHBoxLayout(fileWidget);
        fileWidgetHorizontalLayout->setSpacing(6);
        fileWidgetHorizontalLayout->setContentsMargins(11, 11, 11, 11);
        fileWidgetHorizontalLayout->setObjectName(QStringLiteral("fileWidgetHorizontalLayout"));
        openLabel = new QLabel(fileWidget);
        openLabel->setObjectName(QStringLiteral("openLabel"));

        fileWidgetHorizontalLayout->addWidget(openLabel);

        filePathLineEdit = new QLineEdit(fileWidget);
        filePathLineEdit->setObjectName(QStringLiteral("filePathLineEdit"));
        filePathLineEdit->setReadOnly(true);

        fileWidgetHorizontalLayout->addWidget(filePathLineEdit);

        openPushButton = new QPushButton(fileWidget);
        openPushButton->setObjectName(QStringLiteral("openPushButton"));

        fileWidgetHorizontalLayout->addWidget(openPushButton);


        verticalLayout->addWidget(fileWidget);

        h264Widget = new QWidget(centralWidget);
        h264Widget->setObjectName(QStringLiteral("h264Widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(h264Widget->sizePolicy().hasHeightForWidth());
        h264Widget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(h264Widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        nalSplitter = new QSplitter(h264Widget);
        nalSplitter->setObjectName(QStringLiteral("nalSplitter"));
        nalSplitter->setOrientation(Qt::Horizontal);
        nalTableView = new QTableView(nalSplitter);
        nalTableView->setObjectName(QStringLiteral("nalTableView"));
        nalTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        nalSplitter->addWidget(nalTableView);
        nalPlainTextEdit = new QPlainTextEdit(nalSplitter);
        nalPlainTextEdit->setObjectName(QStringLiteral("nalPlainTextEdit"));
        nalPlainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        nalSplitter->addWidget(nalPlainTextEdit);

        horizontalLayout->addWidget(nalSplitter);


        verticalLayout->addWidget(h264Widget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "H264 Naked", 0));
        openLabel->setText(QApplication::translate("MainWindow", "File:", 0));
        openPushButton->setText(QApplication::translate("MainWindow", "Open", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

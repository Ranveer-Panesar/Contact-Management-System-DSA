/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *searchLayout;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *clearSearchButton;
    QLabel *sortLabel;
    QComboBox *sortComboBox;
    QTableWidget *contactTable;
    QHBoxLayout *buttonLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *viewButton;
    QPushButton *refreshButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *importButton;
    QPushButton *exportButton;
    QLabel *statusLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName("searchLineEdit");

        searchLayout->addWidget(searchLineEdit);

        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");

        searchLayout->addWidget(searchButton);

        clearSearchButton = new QPushButton(centralwidget);
        clearSearchButton->setObjectName("clearSearchButton");

        searchLayout->addWidget(clearSearchButton);

        sortLabel = new QLabel(centralwidget);
        sortLabel->setObjectName("sortLabel");

        searchLayout->addWidget(sortLabel);

        sortComboBox = new QComboBox(centralwidget);
        sortComboBox->setObjectName("sortComboBox");
        sortComboBox->setMinimumWidth(200);

        searchLayout->addWidget(sortComboBox);


        verticalLayout->addLayout(searchLayout);

        contactTable = new QTableWidget(centralwidget);
        contactTable->setObjectName("contactTable");

        verticalLayout->addWidget(contactTable);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");

        buttonLayout->addWidget(addButton);

        editButton = new QPushButton(centralwidget);
        editButton->setObjectName("editButton");

        buttonLayout->addWidget(editButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");

        buttonLayout->addWidget(deleteButton);

        viewButton = new QPushButton(centralwidget);
        viewButton->setObjectName("viewButton");

        buttonLayout->addWidget(viewButton);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName("refreshButton");

        buttonLayout->addWidget(refreshButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(horizontalSpacer);

        importButton = new QPushButton(centralwidget);
        importButton->setObjectName("importButton");

        buttonLayout->addWidget(importButton);

        exportButton = new QPushButton(centralwidget);
        exportButton->setObjectName("exportButton");

        buttonLayout->addWidget(exportButton);


        verticalLayout->addLayout(buttonLayout);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Contact Management System", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Contact Management System", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 24px; font-weight: bold; padding: 20px;", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by name or phone...", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        clearSearchButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        sortLabel->setText(QCoreApplication::translate("MainWindow", "Sort:", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Add Contact", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "Edit Contact", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Delete Contact", nullptr));
        viewButton->setText(QCoreApplication::translate("MainWindow", "View Details", nullptr));
        refreshButton->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        importButton->setText(QCoreApplication::translate("MainWindow", "Import", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Total Contacts: 0", nullptr));
        statusLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 10px;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

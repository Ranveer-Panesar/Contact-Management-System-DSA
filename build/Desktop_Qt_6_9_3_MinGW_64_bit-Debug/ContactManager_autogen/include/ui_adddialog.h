/********************************************************************************
** Form generated from reading UI file 'adddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDIALOG_H
#define UI_ADDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *addressLabel;
    QTextEdit *addressTextEdit;
    QLabel *notesLabel;
    QTextEdit *notesTextEdit;
    QHBoxLayout *buttonLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddDialog)
    {
        if (AddDialog->objectName().isEmpty())
            AddDialog->setObjectName("AddDialog");
        AddDialog->resize(500, 450);
        verticalLayout = new QVBoxLayout(AddDialog);
        verticalLayout->setObjectName("verticalLayout");
        nameLabel = new QLabel(AddDialog);
        nameLabel->setObjectName("nameLabel");

        verticalLayout->addWidget(nameLabel);

        nameLineEdit = new QLineEdit(AddDialog);
        nameLineEdit->setObjectName("nameLineEdit");

        verticalLayout->addWidget(nameLineEdit);

        phoneLabel = new QLabel(AddDialog);
        phoneLabel->setObjectName("phoneLabel");

        verticalLayout->addWidget(phoneLabel);

        phoneLineEdit = new QLineEdit(AddDialog);
        phoneLineEdit->setObjectName("phoneLineEdit");

        verticalLayout->addWidget(phoneLineEdit);

        emailLabel = new QLabel(AddDialog);
        emailLabel->setObjectName("emailLabel");

        verticalLayout->addWidget(emailLabel);

        emailLineEdit = new QLineEdit(AddDialog);
        emailLineEdit->setObjectName("emailLineEdit");

        verticalLayout->addWidget(emailLineEdit);

        addressLabel = new QLabel(AddDialog);
        addressLabel->setObjectName("addressLabel");

        verticalLayout->addWidget(addressLabel);

        addressTextEdit = new QTextEdit(AddDialog);
        addressTextEdit->setObjectName("addressTextEdit");
        addressTextEdit->setMaximumHeight(60);

        verticalLayout->addWidget(addressTextEdit);

        notesLabel = new QLabel(AddDialog);
        notesLabel->setObjectName("notesLabel");

        verticalLayout->addWidget(notesLabel);

        notesTextEdit = new QTextEdit(AddDialog);
        notesTextEdit->setObjectName("notesTextEdit");
        notesTextEdit->setMaximumHeight(60);

        verticalLayout->addWidget(notesTextEdit);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(horizontalSpacer);

        saveButton = new QPushButton(AddDialog);
        saveButton->setObjectName("saveButton");

        buttonLayout->addWidget(saveButton);

        cancelButton = new QPushButton(AddDialog);
        cancelButton->setObjectName("cancelButton");

        buttonLayout->addWidget(cancelButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(AddDialog);

        QMetaObject::connectSlotsByName(AddDialog);
    } // setupUi

    void retranslateUi(QDialog *AddDialog)
    {
        AddDialog->setWindowTitle(QCoreApplication::translate("AddDialog", "Add/Edit Contact", nullptr));
        nameLabel->setText(QCoreApplication::translate("AddDialog", "Name *", nullptr));
        nameLineEdit->setPlaceholderText(QCoreApplication::translate("AddDialog", "Enter full name", nullptr));
        phoneLabel->setText(QCoreApplication::translate("AddDialog", "Phone *", nullptr));
        phoneLineEdit->setPlaceholderText(QCoreApplication::translate("AddDialog", "Enter phone number", nullptr));
        emailLabel->setText(QCoreApplication::translate("AddDialog", "Email", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("AddDialog", "Enter email address", nullptr));
        addressLabel->setText(QCoreApplication::translate("AddDialog", "Address", nullptr));
        addressTextEdit->setPlaceholderText(QCoreApplication::translate("AddDialog", "Enter address", nullptr));
        notesLabel->setText(QCoreApplication::translate("AddDialog", "Notes", nullptr));
        notesTextEdit->setPlaceholderText(QCoreApplication::translate("AddDialog", "Additional notes (optional)", nullptr));
        saveButton->setText(QCoreApplication::translate("AddDialog", "Save", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddDialog: public Ui_AddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDIALOG_H

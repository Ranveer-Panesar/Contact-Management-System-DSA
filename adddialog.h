/**
 * @file adddialog.h
 * @brief Dialog for adding/editing contacts with validation
 */

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "contact.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr, bool isEdit = false);
    ~AddDialog();

    Contact getContact() const;
    void setContact(const Contact& contact);

private slots:
    void onAccept();
    void onCancel();
    void onPhoneTextChanged(const QString& text);
    void onEmailTextChanged(const QString& text);

private:
    Ui::AddDialog *ui;
    bool editMode;

    bool validateInput();
    bool isValidPhone(const QString& phone);
    bool isValidEmail(const QString& email);
    void setupValidators();
};

#endif // ADDDIALOG_H

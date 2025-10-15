/**
 * @file adddialog.cpp
 * @brief Implementation of AddDialog class with validation
 */

#include "adddialog.h"
#include "./ui_adddialog.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>

AddDialog::AddDialog(QWidget *parent, bool isEdit)
    : QDialog(parent)
    , ui(new Ui::AddDialog)
    , editMode(isEdit) {
    ui->setupUi(this);

    setWindowTitle(editMode ? "Edit Contact" : "Add New Contact");

    // Setup input validators
    setupValidators();

    // Connect buttons
    connect(ui->saveButton, &QPushButton::clicked, this, &AddDialog::onAccept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AddDialog::onCancel);

    // Connect real-time validation
    connect(ui->phoneLineEdit, &QLineEdit::textChanged,
            this, &AddDialog::onPhoneTextChanged);
    connect(ui->emailLineEdit, &QLineEdit::textChanged,
            this, &AddDialog::onEmailTextChanged);
}

AddDialog::~AddDialog() {
    delete ui;
}

void AddDialog::setupValidators() {
    // Phone validator: allows digits, spaces, hyphens, parentheses, and +
    QRegularExpression phoneRegex("^[0-9\\s\\-\\(\\)\\+]*$");
    QRegularExpressionValidator *phoneValidator =
        new QRegularExpressionValidator(phoneRegex, this);
    ui->phoneLineEdit->setValidator(phoneValidator);

    // Set placeholder text with format hints
    ui->phoneLineEdit->setPlaceholderText("e.g., +91-9876543210 or 9876543210");
    ui->emailLineEdit->setPlaceholderText("e.g., example@email.com");
}

bool AddDialog::isValidPhone(const QString& phone) {
    // Remove all non-digit characters for validation
    QString digitsOnly = phone;
    digitsOnly.remove(QRegularExpression("[^0-9]"));

    // Indian phone number validation
    // Must have 10 digits, or 12 digits with country code (91)
    if (digitsOnly.length() == 10) {
        // Valid 10-digit Indian number
        return true;
    } else if (digitsOnly.length() == 12 && digitsOnly.startsWith("91")) {
        // Valid with country code
        return true;
    } else if (digitsOnly.length() >= 7 && digitsOnly.length() <= 15) {
        // International numbers can be 7-15 digits
        return true;
    }

    return false;
}

bool AddDialog::isValidEmail(const QString& email) {
    if (email.trimmed().isEmpty()) {
        return true; // Email is optional
    }

    // Comprehensive email validation regex
    QRegularExpression emailRegex(
        "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"
        );

    QRegularExpressionMatch match = emailRegex.match(email.trimmed());
    return match.hasMatch();
}

void AddDialog::onPhoneTextChanged(const QString& text) {
    // Real-time visual feedback
    if (text.isEmpty()) {
        ui->phoneLineEdit->setStyleSheet("");
        return;
    }

    if (isValidPhone(text)) {
        ui->phoneLineEdit->setStyleSheet(
            "QLineEdit { border: 2px solid #34C759; }"
            );
    } else {
        ui->phoneLineEdit->setStyleSheet(
            "QLineEdit { border: 2px solid #FF3B30; }"
            );
    }
}

void AddDialog::onEmailTextChanged(const QString& text) {
    // Real-time visual feedback
    if (text.isEmpty()) {
        ui->emailLineEdit->setStyleSheet("");
        return;
    }

    if (isValidEmail(text)) {
        ui->emailLineEdit->setStyleSheet(
            "QLineEdit { border: 2px solid #34C759; }"
            );
    } else {
        ui->emailLineEdit->setStyleSheet(
            "QLineEdit { border: 2px solid #FF3B30; }"
            );
    }
}

bool AddDialog::validateInput() {
    // Validate Name
    if (ui->nameLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error",
                             "Name cannot be empty!");
        ui->nameLineEdit->setFocus();
        return false;
    }

    // Check if name contains at least some letters
    QString name = ui->nameLineEdit->text().trimmed();
    QRegularExpression nameRegex("[a-zA-Z]+");
    if (!nameRegex.match(name).hasMatch()) {
        QMessageBox::warning(this, "Validation Error",
                             "Name must contain at least some letters!");
        ui->nameLineEdit->setFocus();
        return false;
    }

    // Validate Phone
    QString phone = ui->phoneLineEdit->text().trimmed();
    if (phone.isEmpty()) {
        QMessageBox::warning(this, "Validation Error",
                             "Phone number cannot be empty!");
        ui->phoneLineEdit->setFocus();
        return false;
    }

    if (!isValidPhone(phone)) {
        QMessageBox::warning(this, "Invalid Phone Number",
                             "Please enter a valid phone number.\n\n"
                             "Accepted formats:\n"
                             "• 10 digits: 9876543210\n"
                             "• With country code: +91-9876543210\n"
                             "• With spaces: 98765 43210\n"
                             "• With parentheses: (987) 654-3210");
        ui->phoneLineEdit->setFocus();
        return false;
    }

    // Validate Email (if provided)
    QString email = ui->emailLineEdit->text().trimmed();
    if (!email.isEmpty() && !isValidEmail(email)) {
        QMessageBox::warning(this, "Invalid Email",
                             "Please enter a valid email address.\n\n"
                             "Example: example@domain.com");
        ui->emailLineEdit->setFocus();
        return false;
    }

    return true;
}

Contact AddDialog::getContact() const {
    return Contact(
        ui->nameLineEdit->text().trimmed(),
        ui->phoneLineEdit->text().trimmed(),
        ui->emailLineEdit->text().trimmed(),
        ui->addressTextEdit->toPlainText().trimmed(),
        ui->notesTextEdit->toPlainText().trimmed()
        );
}

void AddDialog::setContact(const Contact& contact) {
    ui->nameLineEdit->setText(contact.getName());
    ui->phoneLineEdit->setText(contact.getPhone());
    ui->emailLineEdit->setText(contact.getEmail());
    ui->addressTextEdit->setPlainText(contact.getAddress());
    ui->notesTextEdit->setPlainText(contact.getNotes());
}

void AddDialog::onAccept() {
    if (validateInput()) {
        accept();
    }
}

void AddDialog::onCancel() {
    reject();
}

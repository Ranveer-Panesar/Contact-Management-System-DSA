/**
 * @file contact.cpp
 * @brief Implementation of Contact class methods
 */

#include "contact.h"

// Initialize static member
int Contact::nextId = 1;

Contact::Contact()
    : id(nextId++),
    createdDate(QDateTime::currentDateTime()),
    modifiedDate(QDateTime::currentDateTime()) {
}

Contact::Contact(const QString& name, const QString& phone,
                 const QString& email, const QString& address,
                 const QString& notes)
    : id(nextId++),
    name(name),
    phone(phone),
    email(email),
    address(address),
    notes(notes),
    createdDate(QDateTime::currentDateTime()),
    modifiedDate(QDateTime::currentDateTime()) {
}

QString Contact::toString() const {
    return QString("ID: %1\nName: %2\nPhone: %3\nEmail: %4\nAddress: %5\nNotes: %6")
    .arg(id)
        .arg(name)
        .arg(phone)
        .arg(email)
        .arg(address)
        .arg(notes);
}

/**
 * @file contact.h
 * @brief Contact class definition for storing individual contact information
 * @author Your Name
 * @date October 2025
 *
 * This class represents a single contact with all relevant information
 * including name, phone, email, address, and additional notes.
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDateTime>

class Contact {
public:
    /**
     * @brief Default constructor
     */
    Contact();

    /**
     * @brief Parameterized constructor
     * @param name Contact's full name
     * @param phone Contact's phone number
     * @param email Contact's email address
     * @param address Contact's physical address
     * @param notes Additional notes about the contact
     */
    Contact(const QString& name, const QString& phone,
            const QString& email, const QString& address,
            const QString& notes = "");

    // Getters
    int getId() const { return id; }
    QString getName() const { return name; }
    QString getPhone() const { return phone; }
    QString getEmail() const { return email; }
    QString getAddress() const { return address; }
    QString getNotes() const { return notes; }
    QDateTime getCreatedDate() const { return createdDate; }
    QDateTime getModifiedDate() const { return modifiedDate; }

    // Setters
    void setId(int newId) { id = newId; }
    void setName(const QString& newName) { name = newName; updateModifiedDate(); }
    void setPhone(const QString& newPhone) { phone = newPhone; updateModifiedDate(); }
    void setEmail(const QString& newEmail) { email = newEmail; updateModifiedDate(); }
    void setAddress(const QString& newAddress) { address = newAddress; updateModifiedDate(); }
    void setNotes(const QString& newNotes) { notes = newNotes; updateModifiedDate(); }

    /**
     * @brief Comparison operator for sorting contacts by name
     */
    bool operator<(const Contact& other) const {
        return name.toLower() < other.name.toLower();
    }

    /**
     * @brief Converts contact to a formatted string
     * @return QString representation of contact
     */
    QString toString() const;

private:
    int id;                      ///< Unique identifier for the contact
    QString name;                ///< Full name of the contact
    QString phone;               ///< Phone number
    QString email;               ///< Email address
    QString address;             ///< Physical address
    QString notes;               ///< Additional notes
    QDateTime createdDate;       ///< Date and time when contact was created
    QDateTime modifiedDate;      ///< Date and time when contact was last modified

    static int nextId;           ///< Static counter for generating unique IDs

    /**
     * @brief Updates the modified date to current date/time
     */
    void updateModifiedDate() { modifiedDate = QDateTime::currentDateTime(); }
};

#endif // CONTACT_H

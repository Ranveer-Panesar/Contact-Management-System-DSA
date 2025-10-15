/**
 * @file contactmanager.cpp
 * @brief Implementation of ContactManager class methods
 */

#include "contactmanager.h"
#include <QDebug>

ContactManager::ContactManager() {
}

ContactManager::~ContactManager() {
    clear();
}

bool ContactManager::addContact(const Contact& contact) {
    try {
        contacts.push_back(contact);
        rebuildIndexMap();
        return true;
    } catch (const std::exception& e) {
        qDebug() << "Error adding contact:" << e.what();
        return false;
    }
}

bool ContactManager::removeContact(int id) {
    auto it = std::find_if(contacts.begin(), contacts.end(),
                           [id](const Contact& c) { return c.getId() == id; });

    if (it != contacts.end()) {
        contacts.erase(it);
        rebuildIndexMap();
        return true;
    }
    return false;
}

bool ContactManager::updateContact(int id, const Contact& updatedContact) {
    auto it = std::find_if(contacts.begin(), contacts.end(),
                           [id](const Contact& c) { return c.getId() == id; });

    if (it != contacts.end()) {
        // Preserve the original ID and created date
        Contact temp = updatedContact;
        temp.setId(id);
        *it = temp;
        return true;
    }
    return false;
}

Contact* ContactManager::getContactById(int id) {
    auto mapIt = idToIndex.find(id);
    if (mapIt != idToIndex.end() && mapIt->second < contacts.size()) {
        return &contacts[mapIt->second];
    }
    return nullptr;
}

std::vector<Contact> ContactManager::searchByName(const QString& searchTerm) const {
    std::vector<Contact> results;
    QString lowerSearch = searchTerm.toLower();

    for (const auto& contact : contacts) {
        if (contact.getName().toLower().contains(lowerSearch)) {
            results.push_back(contact);
        }
    }

    return results;
}

std::vector<Contact> ContactManager::searchByPhone(const QString& phoneNumber) const {
    std::vector<Contact> results;

    for (const auto& contact : contacts) {
        if (contact.getPhone().contains(phoneNumber)) {
            results.push_back(contact);
        }
    }

    return results;
}

std::vector<Contact> ContactManager::getAllContactsSorted() const {
    std::vector<Contact> sortedContacts = contacts;
    std::sort(sortedContacts.begin(), sortedContacts.end());
    return sortedContacts;
}

bool ContactManager::saveToFile(const QString& filename) const {
    QJsonArray contactArray;

    for (const auto& contact : contacts) {
        QJsonObject contactObj;
        contactObj["id"] = contact.getId();
        contactObj["name"] = contact.getName();
        contactObj["phone"] = contact.getPhone();
        contactObj["email"] = contact.getEmail();
        contactObj["address"] = contact.getAddress();
        contactObj["notes"] = contact.getNotes();
        contactObj["created"] = contact.getCreatedDate().toString(Qt::ISODate);
        contactObj["modified"] = contact.getModifiedDate().toString(Qt::ISODate);

        contactArray.append(contactObj);
    }

    QJsonDocument doc(contactArray);
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        return true;
    }

    return false;
}

bool ContactManager::loadFromFile(const QString& filename) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isArray()) {
        return false;
    }

    clear();
    QJsonArray contactArray = doc.array();

    for (const auto& value : contactArray) {
        QJsonObject obj = value.toObject();

        Contact contact(
            obj["name"].toString(),
            obj["phone"].toString(),
            obj["email"].toString(),
            obj["address"].toString(),
            obj["notes"].toString()
            );

        addContact(contact);
    }

    return true;
}

void ContactManager::clear() {
    contacts.clear();
    idToIndex.clear();
}

bool ContactManager::phoneExists(const QString& phone, int excludeId) const {
    for (const auto& contact : contacts) {
        if (contact.getId() != excludeId && contact.getPhone() == phone) {
            return true;
        }
    }
    return false;
}


void ContactManager::rebuildIndexMap() {
    idToIndex.clear();
    for (size_t i = 0; i < contacts.size(); ++i) {
        idToIndex[contacts[i].getId()] = i;
    }
}

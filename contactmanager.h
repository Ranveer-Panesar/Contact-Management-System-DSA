/**
 * @file contactmanager.h
 * @brief Contact manager class using STL data structures
 * @author Your Name
 * @date October 2025
 *
 * This class manages the collection of contacts using various data structures:
 * - Vector for main storage (dynamic array)
 * - Map for quick ID-based lookup (Red-Black Tree)
 * - Set for maintaining sorted order (BST)
 *
 * Demonstrates usage of STL containers for efficient data management.
 */

#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include "contact.h"
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ContactManager {
public:
    ContactManager();
    ~ContactManager();

    /**
 * @brief Checks if a phone number already exists
 * @param phone The phone number to check
 * @param excludeId ID to exclude from check (for edit operations)
 * @return true if phone exists, false otherwise
 */
    bool phoneExists(const QString& phone, int excludeId = -1) const;


    /**
     * @brief Adds a new contact to the system
     * @param contact The contact object to add
     * @return true if successful, false otherwise
     * Time Complexity: O(log n) due to map insertion
     */
    bool addContact(const Contact& contact);

    /**
     * @brief Removes a contact by ID
     * @param id The unique identifier of the contact
     * @return true if contact was found and removed, false otherwise
     * Time Complexity: O(n) for vector, O(log n) for map
     */
    bool removeContact(int id);

    /**
     * @brief Updates an existing contact
     * @param id The ID of the contact to update
     * @param updatedContact The new contact data
     * @return true if successful, false otherwise
     * Time Complexity: O(n)
     */
    bool updateContact(int id, const Contact& updatedContact);

    /**
     * @brief Retrieves a contact by ID
     * @param id The unique identifier
     * @return Pointer to contact if found, nullptr otherwise
     * Time Complexity: O(log n) using map
     */
    Contact* getContactById(int id);

    /**
     * @brief Searches contacts by name (partial match)
     * @param searchTerm The name to search for
     * @return Vector of matching contacts
     * Time Complexity: O(n)
     */
    std::vector<Contact> searchByName(const QString& searchTerm) const;

    /**
     * @brief Searches contacts by phone number
     * @param phoneNumber The phone to search for
     * @return Vector of matching contacts
     * Time Complexity: O(n)
     */
    std::vector<Contact> searchByPhone(const QString& phoneNumber) const;

    /**
     * @brief Gets all contacts sorted by name
     * @return Vector of all contacts in alphabetical order
     * Time Complexity: O(n log n) if not cached
     */
    std::vector<Contact> getAllContactsSorted() const;

    /**
     * @brief Gets total number of contacts
     * @return Contact count
     * Time Complexity: O(1)
     */
    int getContactCount() const { return contacts.size(); }

    /**
     * @brief Saves all contacts to a JSON file
     * @param filename Path to the file
     * @return true if successful, false otherwise
     */
    bool saveToFile(const QString& filename) const;

    /**
     * @brief Loads contacts from a JSON file
     * @param filename Path to the file
     * @return true if successful, false otherwise
     */
    bool loadFromFile(const QString& filename);

    /**
     * @brief Clears all contacts from memory
     */
    void clear();

private:
    std::vector<Contact> contacts;        ///< Main storage using dynamic array
    std::map<int, size_t> idToIndex;     ///< Maps ID to vector index for O(log n) lookup

    /**
     * @brief Rebuilds the ID-to-index mapping
     * Called after operations that change vector indices
     * Time Complexity: O(n)
     */
    void rebuildIndexMap();
};

#endif // CONTACTMANAGER_H

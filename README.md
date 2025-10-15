# 📇 Contact Management System

<div align="center">

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

**A modern Qt-based contact management application demonstrating practical Data Structures and Algorithms implementation**

*Built for DSA Course Assignment | October 2025*

[Features](#-features) • [Demo](#-demo) • [Installation](#-installation) • [DSA Concepts](#-dsa-concepts) • [Documentation](#-documentation)

</div>

---

## 🎯 About The Project

This Contact Management System is a full-featured desktop application built with **Qt6** and **C++17** as part of my Data Structures and Algorithms course assignment. The project demonstrates real-world implementation of core DSA concepts in a production-ready application with a professional, minimalist UI inspired by modern design principles.

### 🌟 Project Highlights

- **Professional Grade**: Auto-save, data persistence, and comprehensive error handling
- **Modern C++**: Leverages C++17 features (lambda functions, auto, range-based loops, STL containers)
- **Clean UI**: Apple/Samsung-inspired minimalist design using custom QSS styling
- **Well Documented**: Extensive inline documentation and complexity analysis
- **DSA Focused**: Implements Vector, Map (Red-Black Tree), Sorting, and Search algorithms

---

## ✨ Features

### 🔥 Core Functionality

| Feature | Description |
|---------|-------------|
| ➕ **Add Contacts** | Create contacts with complete validation |
| ✏️ **Edit Contacts** | Update existing contact information |
| 🗑️ **Delete Contacts** | Remove contacts with confirmation |
| 🔍 **Smart Search** | Search by name or phone (supports partial matching) |
| 🔄 **Flexible Sorting** | Sort by Name (A-Z, Z-A) or ID (Asc, Desc) |
| 👁️ **View Details** | Complete contact info with timestamps |

### 💎 Advanced Features

- **✅ Real-time Validation**
  - Phone: Indian format (`9876543210`, `+91-9876543210`) and international
  - Email: RFC-compliant validation with visual feedback (green/red borders)
  
- **💾 Auto-Save & Persistence**
  - Automatic data saving on every operation
  - Contacts persist across app sessions
  - Platform-independent storage location

- **📤 Import/Export**
  - JSON-based data format
  - Bulk import capability
  - Easy data backup and migration

- **🚫 Smart Duplicate Prevention**
  - Checks for duplicate phone numbers
  - Prevents data inconsistency

- **🎨 Professional UI**
  - Clean, responsive interface
  - Custom QSS styling
  - Intuitive user experience

---

## 🛠️ Tech Stack

```Frontend: Qt 6.x (Widgets, Designer)
Backend: C++17 (STL, OOP principles)
Build System: CMake 3.16+
Styling: QSS (Qt Style Sheets)
Data Format: JSON (QJsonDocument)
Version Control: Git & GitHub
```


---

## 📚 DSA Concepts Demonstrated

### Data Structures

<details>
<summary><b>1. Vector (Dynamic Array)</b> - Click to expand</summary>

```
std::vector<Contact> contacts; // Primary storage
```


**Implementation Details:**
- **Purpose**: Main contact storage with dynamic memory allocation
- **Operations**: `push_back()`, `erase()`, `size()`, iteration
- **Time Complexity**: 
  - Access: O(1)
  - Insertion: O(1) amortized
  - Deletion: O(n)
- **Space Complexity**: O(n)

**Real-world Application**: Resizable contact list that grows/shrinks automatically

</details>

<details>
<summary><b>2. Map (Red-Black Tree)</b> - Click to expand</summary>

```
std::map<int, size_t> idToIndex; // ID-to-index mapping
```


**Implementation Details:**
- **Purpose**: Fast O(log n) contact lookup by unique ID
- **Operations**: `find()`, `insert()`, `clear()`
- **Time Complexity**: O(log n) for search and insertion
- **Space Complexity**: O(n)

**Real-world Application**: Database indexing for efficient retrieval

</details>

<details>
<summary><b>3. String (QString)</b> - Click to expand</summary>

**Implementation Details:**
- **Purpose**: Dynamic text storage and manipulation
- **Operations**: Concatenation, comparison, substring matching
- **Features**: Unicode support, immutable design with copy-on-write

</details>

### Algorithms

#### 🔍 **1. Linear Search** - `O(n)`

```
std::vector<Contact> searchByName(const QString& searchTerm) const {
std::vector<Contact> results;
for (const auto& contact : contacts) {
if (contact.getName().contains(searchTerm)) {
results.push_back(contact);
}
}
return results;
}
```


**Use Case**: Flexible substring matching for name and phone search

---

#### ⚡ **2. Binary Search (Implicit)** - `O(log n)`

```
Contact* getContactById(int id) {
auto mapIt = idToIndex.find(id); // Binary search on Red-Black Tree
return (mapIt != idToIndex.end()) ? &contacts[mapIt->second] : nullptr;
}
```


**Use Case**: Fast contact retrieval by unique identifier

---

#### 📊 **3. Sorting Algorithms** - `O(n log n)`

```
// Sort by name ascending
std::sort(contacts.begin(), contacts.end());

// Sort by name descending with custom comparator
std::sort(contacts.begin(), contacts.end(),
[](const Contact& a, const Contact& b) {
return a.getName().toLower() > b.getName().toLower();
});

// Sort by ID with lambda function
std::sort(contacts.begin(), contacts.end(),
[](const Contact& a, const Contact& b) {
return a.getId() < b.getId();
});
```


**Sorting Options Available:**
- Name (A-Z / Z-A)
- ID (Ascending / Descending)

**Algorithm Used**: IntroSort (hybrid of QuickSort, HeapSort, and Insertion Sort)

---

#### 🎯 **4. Conditional Search (find_if)** - `O(n)`

```
auto it = std::find_if(contacts.begin(), contacts.end(),
[id](const Contact& c) { return c.getId() == id; });
```


**Use Case**: Predicate-based searching with lambda expressions

---

### OOP Principles Applied

```
class Contact {
private:
int id; // Encapsulation
QString name, phone;
static int nextId; // Static member shared across instances

public:
Contact(); // Constructor overloading
Contact(const QString& name, ...);

int getId() const;         // Const correctness
void setName(const QString&);

bool operator<(const Contact& other) const {  // Operator overloading
    return name.toLower() < other.name.toLower();
}
};
```


**Concepts Demonstrated:**
- ✅ Encapsulation (private data, public interface)
- ✅ Abstraction (ContactManager hides implementation)
- ✅ Constructor overloading
- ✅ Operator overloading
- ✅ Static members
- ✅ Const correctness

---

## ⏱️ Time Complexity Analysis

| Operation | Implementation | Time | Space |
|-----------|---------------|------|-------|
| **Add Contact** | Vector + Map insert | O(log n) | O(1) |
| **Delete Contact** | Vector erase | O(n) | O(1) |
| **Search by ID** | Map find (RB-Tree) | O(log n) | O(1) |
| **Search by Name** | Linear scan | O(n) | O(k)* |
| **Sort Contacts** | IntroSort | O(n log n) | O(1) |
| **Update Contact** | Linear search | O(n) | O(1) |
| **Import Contacts** | Batch insert | O(n log n) | O(n) |
| **Duplicate Check** | Linear scan | O(n) | O(1) |

\* k = number of matching results

**Overall Space Complexity**: O(n) where n is the number of contacts

---

## ⚙️ Installation

### Prerequisites

Ensure you have the following installed:

- **Qt 6.5 or higher** - [Download Qt](https://www.qt.io/download)
- **CMake 3.16+** - [Download CMake](https://cmake.org/download/)
- **C++17 Compatible Compiler**:
  - GCC 7+ (Linux)
  - MSVC 2019+ (Windows)
  - Clang 5+ (macOS)

### Quick Start

#### 🚀 Option 1: Qt Creator (Recommended)

```
1. Clone the repository
git clone https://github.com/yourusername/ContactManagementSystem.git
cd ContactManagementSystem

2. Open in Qt Creator
File → Open File or Project → Select CMakeLists.txt
Configure with Qt 6.x kit → Click Run (Ctrl+R)
```


#### 💻 Option 2: Command Line

```
1. Clone the repository
git clone https://github.com/yourusername/ContactManagementSystem.git
cd ContactManagementSystem

2. Create build directory
mkdir build && cd build

3. Configure with CMake (replace with your Qt path)
cmake -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64 ..

4. Build
cmake --build .

5. Run
./ContactManager # Linux/macOS
ContactManager.exe # Windows
```


### 📍 Common Qt Installation Paths

- **Windows**: `C:/Qt/6.5.3/msvc2019_64` or `C:/Qt/6.5.3/mingw_64`
- **Linux**: `/opt/Qt/6.5.3/gcc_64` or `~/Qt/6.5.3/gcc_64`
- **macOS**: `~/Qt/6.5.3/macos`

---

## 🚀 Usage Guide

### Getting Started

1. **Launch Application**
```./ContactManager```


2. **Add First Contact**
- Click "Add Contact" button
- Fill required fields (Name*, Phone*)
- Optional: Email, Address, Notes
- Click "Save"

3. **Search Contacts**
```
Search bar → Enter name/phone → Search
Clear → Reset to full list
```

4. **Sort Contacts**

```
Dropdown menu:

Sort by Name (A-Z)

Sort by Name (Z-A)

Sort by ID (Low-High)

Sort by ID (High-Low)
```

5. **Import Sample Data**
```
Import → Select contacts.json → Open
→ 20 sample contacts loaded!
```

### 📝 Input Validation

**Phone Number Formats** (Auto-validated):

```
✓ 9876543210 (10 digits)
✓ +91-9876543210 (with country code)
✓ +91 98765 43210 (with spaces)
✓ (987) 654-3210 (with parentheses)
✗ 12345 (too short)
```

**Email Format**:

```
✓ user@example.com
✓ name.surname@company.co.in
✗ invalid.email (missing @)
✗ @domain.com (missing username)
```


### 💾 Data Storage Location

Contacts auto-save to:
- **Windows**: `C:\Users\YourName\AppData\Local\DSA Project\ContactManager\contacts_data.json`
- **Linux**: `~/.local/share/DSA Project/ContactManager/contacts_data.json`
- **macOS**: `~/Library/Application Support/DSA Project/ContactManager/contacts_data.json`

---

## 📁 Project Structure

```
ContactManagementSystem/
│
├── CMakeLists.txt # Build configuration
├── README.md # Project documentation
├── LICENSE # MIT License
├── contacts.json # Sample data (20 contacts)
│
├── src/
│ ├── main.cpp # Entry point
│ ├── mainwindow.h # Main window header
│ ├── mainwindow.cpp # Main window implementation
│ ├── mainwindow.ui # UI layout (Qt Designer)
│ ├── contact.h # Contact entity class
│ ├── contact.cpp # Contact implementation
│ ├── contactmanager.h # Business logic layer
│ ├── contactmanager.cpp # Data structure operations
│ ├── adddialog.h # Add/Edit dialog
│ ├── adddialog.cpp # Dialog implementation
│ └── adddialog.ui # Dialog UI layout
│
└── resources/
├── resources.qrc # Qt resource file
└── styles.qss # Custom stylesheets
```


---

## 📸 Screenshots

### Main Interface
*Professional, clean UI with table view and sorting options*

### Add/Edit Contact Dialog
*Input validation with real-time visual feedback*

### Search Functionality
*Fast search with partial matching support*

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

### How to Contribute

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Ideas for Enhancement

- [ ] Contact groups/categories
- [ ] Profile picture support
- [ ] Export to VCF (vCard) format
- [ ] Dark mode theme
- [ ] Email integration
- [ ] Data encryption
- [ ] Backup/restore functionality
- [ ] Advanced search filters

---

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.

---

## 👨‍💻 Author

**Computer Science/Engineering Student**  
*Data Structures and Algorithms Project*  
*October 2025*

📧 Email: your.email@example.com  
🔗 GitHub: [@yourusername](https://github.com/yourusername)  
💼 LinkedIn: [Your LinkedIn](https://linkedin.com/in/yourprofile)

---

## 🙏 Acknowledgments

- **Qt Framework** - Comprehensive GUI development
- **C++ STL** - Robust data structures and algorithms
- **Qt Documentation** - Excellent reference material
- **Design Inspiration** - Apple & Samsung UI/UX principles

---

## 📊 Project Stats

![C++](https://img.shields.io/badge/Code-C++-informational?style=flat&logo=c%2B%2B&logoColor=white&color=00599C)
![Qt](https://img.shields.io/badge/Framework-Qt-informational?style=flat&logo=qt&logoColor=white&color=41CD52)
![Lines of Code](https://img.shields.io/badge/Lines%20of%20Code-2000%2B-blue)
![Files](https://img.shields.io/badge/Files-12-orange)

---

<div align="center">

### ⭐ If you found this project helpful, please give it a star!

**Made with ❤️ for DSA Course Assignment**

*Building practical applications to understand theoretical concepts*

</div>

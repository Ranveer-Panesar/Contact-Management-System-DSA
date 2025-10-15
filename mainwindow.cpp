/**
 * @file mainwindow.cpp
 * @brief Implementation of MainWindow class with sorting functionality
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QCloseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , contactManager(new ContactManager())
    , currentSortOption(SortByNameAsc) {  // Default sort by name
    ui->setupUi(this);

    // Set up the data file path
    dataFilePath = getDefaultDataPath();

    setupUI();
    loadStyleSheet();
    autoLoadContacts();
    onRefreshTable();
}

MainWindow::~MainWindow() {
    autoSaveContacts();
    delete contactManager;
    delete ui;
}

QString MainWindow::getDefaultDataPath() {
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    if (!dir.exists(dataDir)) {
        dir.mkpath(dataDir);
    }
    return dataDir + "/contacts_data.json";
}

void MainWindow::autoLoadContacts() {
    QFile file(dataFilePath);
    if (file.exists()) {
        if (contactManager->loadFromFile(dataFilePath)) {
            qDebug() << "Contacts loaded successfully from:" << dataFilePath;
            ui->statusLabel->setText(
                QString("Loaded %1 contacts").arg(contactManager->getContactCount())
                );
        } else {
            qDebug() << "Failed to load contacts from:" << dataFilePath;
        }
    } else {
        qDebug() << "No existing data file found. Starting fresh.";
    }
}

void MainWindow::autoSaveContacts() {
    if (contactManager->saveToFile(dataFilePath)) {
        qDebug() << "Contacts saved successfully to:" << dataFilePath;
    } else {
        qDebug() << "Failed to save contacts to:" << dataFilePath;
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    autoSaveContacts();
    event->accept();
}

void MainWindow::setupUI() {
    setWindowTitle("Contact Management System");
    resize(1000, 600);

    // Add sort options to the combo box
    ui->sortComboBox->addItem("Sort by Name (A-Z)", SortByNameAsc);
    ui->sortComboBox->addItem("Sort by Name (Z-A)", SortByNameDesc);
    ui->sortComboBox->addItem("Sort by ID (Low-High)", SortByIDAsc);
    ui->sortComboBox->addItem("Sort by ID (High-Low)", SortByIDDesc);
    ui->sortComboBox->setCurrentIndex(0);  // Default to Name A-Z

    // Connect signals and slots
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddContact);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditContact);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteContact);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchContact);
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::onRefreshTable);
    connect(ui->viewButton, &QPushButton::clicked, this, &MainWindow::onViewDetails);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::onExportContacts);
    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::onImportContacts);
    connect(ui->clearSearchButton, &QPushButton::clicked, this, &MainWindow::onClearSearch);
    connect(ui->contactTable, &QTableWidget::itemSelectionChanged,
            this, &MainWindow::onTableSelectionChanged);
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSortChanged);

    // Configure table
    ui->contactTable->setColumnCount(5);
    ui->contactTable->setHorizontalHeaderLabels(
        {"ID", "Name", "Phone", "Email", "Address"});
    ui->contactTable->horizontalHeader()->setStretchLastSection(true);
    ui->contactTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->contactTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->contactTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Update button states
    onTableSelectionChanged();
}

void MainWindow::loadStyleSheet() {
    QFile file(":/styles/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}

void MainWindow::onSortChanged(int index) {
    currentSortOption = static_cast<SortOption>(ui->sortComboBox->itemData(index).toInt());
    applySorting();
}

void MainWindow::applySorting() {
    std::vector<Contact> contacts = contactManager->getAllContactsSorted();

    // Apply the selected sort option
    switch (currentSortOption) {
    case SortByNameAsc:
        // Already sorted by name ascending in getAllContactsSorted()
        break;

    case SortByNameDesc:
        std::sort(contacts.begin(), contacts.end(),
                  [](const Contact& a, const Contact& b) {
                      return a.getName().toLower() > b.getName().toLower();
                  });
        break;

    case SortByIDAsc:
        std::sort(contacts.begin(), contacts.end(),
                  [](const Contact& a, const Contact& b) {
                      return a.getId() < b.getId();
                  });
        break;

    case SortByIDDesc:
        std::sort(contacts.begin(), contacts.end(),
                  [](const Contact& a, const Contact& b) {
                      return a.getId() > b.getId();
                  });
        break;
    }

    populateTable(contacts);
}

void MainWindow::populateTable(const std::vector<Contact>& contacts) {
    ui->contactTable->setRowCount(0);

    for (const auto& contact : contacts) {
        int row = ui->contactTable->rowCount();
        ui->contactTable->insertRow(row);

        ui->contactTable->setItem(row, 0, new QTableWidgetItem(QString::number(contact.getId())));
        ui->contactTable->setItem(row, 1, new QTableWidgetItem(contact.getName()));
        ui->contactTable->setItem(row, 2, new QTableWidgetItem(contact.getPhone()));
        ui->contactTable->setItem(row, 3, new QTableWidgetItem(contact.getEmail()));
        ui->contactTable->setItem(row, 4, new QTableWidgetItem(contact.getAddress()));
    }

    ui->statusLabel->setText(QString("Total Contacts: %1").arg(contacts.size()));
}

void MainWindow::onAddContact() {
    AddDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Contact newContact = dialog.getContact();

        if (contactManager->phoneExists(newContact.getPhone())) {
            QMessageBox::warning(this, "Duplicate Contact",
                                 "A contact with this phone number already exists!");
            return;
        }

        if (contactManager->addContact(newContact)) {
            autoSaveContacts();
            QMessageBox::information(this, "Success", "Contact added successfully!");
            applySorting();  // Use applySorting instead of onRefreshTable
        } else {
            QMessageBox::warning(this, "Error", "Failed to add contact!");
        }
    }
}

void MainWindow::onEditContact() {
    if (!isContactSelected()) {
        QMessageBox::warning(this, "Warning", "Please select a contact to edit!");
        return;
    }

    Contact selectedContact = getSelectedContact();
    AddDialog dialog(this, true);
    dialog.setContact(selectedContact);

    if (dialog.exec() == QDialog::Accepted) {
        Contact updatedContact = dialog.getContact();

        if (contactManager->phoneExists(updatedContact.getPhone(),
                                        selectedContact.getId())) {
            QMessageBox::warning(this, "Duplicate Contact",
                                 "Another contact with this phone number already exists!");
            return;
        }

        if (contactManager->updateContact(selectedContact.getId(), updatedContact)) {
            autoSaveContacts();
            QMessageBox::information(this, "Success", "Contact updated successfully!");
            applySorting();  // Use applySorting instead of onRefreshTable
        } else {
            QMessageBox::warning(this, "Error", "Failed to update contact!");
        }
    }
}

void MainWindow::onDeleteContact() {
    if (!isContactSelected()) {
        QMessageBox::warning(this, "Warning", "Please select a contact to delete!");
        return;
    }

    Contact selectedContact = getSelectedContact();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete",
        QString("Are you sure you want to delete %1?").arg(selectedContact.getName()),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        if (contactManager->removeContact(selectedContact.getId())) {
            autoSaveContacts();
            QMessageBox::information(this, "Success", "Contact deleted successfully!");
            applySorting();  // Use applySorting instead of onRefreshTable
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete contact!");
        }
    }
}

void MainWindow::onSearchContact() {
    QString searchTerm = ui->searchLineEdit->text().trimmed();

    if (searchTerm.isEmpty()) {
        QMessageBox::information(this, "Info", "Please enter a search term!");
        return;
    }

    std::vector<Contact> results = contactManager->searchByName(searchTerm);

    if (results.empty()) {
        results = contactManager->searchByPhone(searchTerm);
    }

    // Apply current sorting to search results
    switch (currentSortOption) {
    case SortByNameDesc:
        std::sort(results.begin(), results.end(),
                  [](const Contact& a, const Contact& b) {
                      return a.getName().toLower() > b.getName().toLower();
                  });
        break;

    case SortByIDAsc:
        std::sort(results.begin(), results.end(),
                  [](const Contact& a, const Contact& b) {
                      return a.getId() < b.getId();
                  });
        break;

    case SortByIDDesc:
        std::sort(results.begin(), results.end(),
                  [](const Contact& a, const Contact& b) {
                      return a.getId() > b.getId();
                  });
        break;

    default: // SortByNameAsc
        std::sort(results.begin(), results.end());
        break;
    }

    populateTable(results);

    if (results.empty()) {
        ui->statusLabel->setText("No contacts found!");
    }
}

void MainWindow::onRefreshTable() {
    applySorting();
    ui->searchLineEdit->clear();
}

void MainWindow::onViewDetails() {
    if (!isContactSelected()) {
        QMessageBox::warning(this, "Warning", "Please select a contact to view!");
        return;
    }

    Contact selectedContact = getSelectedContact();

    QString details = QString(
                          "Contact Details\n\n"
                          "Name: %1\n"
                          "Phone: %2\n"
                          "Email: %3\n"
                          "Address: %4\n"
                          "Notes: %5\n\n"
                          "Created: %6\n"
                          "Modified: %7"
                          ).arg(selectedContact.getName())
                          .arg(selectedContact.getPhone())
                          .arg(selectedContact.getEmail())
                          .arg(selectedContact.getAddress())
                          .arg(selectedContact.getNotes())
                          .arg(selectedContact.getCreatedDate().toString("yyyy-MM-dd hh:mm:ss"))
                          .arg(selectedContact.getModifiedDate().toString("yyyy-MM-dd hh:mm:ss"));

    QMessageBox::information(this, "Contact Details", details);
}

void MainWindow::onExportContacts() {
    QString filename = QFileDialog::getSaveFileName(
        this, "Export Contacts",
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/contacts.json",
        "JSON Files (*.json)"
        );

    if (!filename.isEmpty()) {
        if (contactManager->saveToFile(filename)) {
            QMessageBox::information(this, "Success",
                                     QString("Contacts exported successfully to:\n%1").arg(filename));
        } else {
            QMessageBox::warning(this, "Error", "Failed to export contacts!");
        }
    }
}

void MainWindow::onImportContacts() {
    QString filename = QFileDialog::getOpenFileName(
        this, "Import Contacts",
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        "JSON Files (*.json)"
        );

    if (!filename.isEmpty()) {
        if (contactManager->loadFromFile(filename)) {
            autoSaveContacts();
            QMessageBox::information(this, "Success",
                                     QString("Contacts imported successfully!\nTotal contacts: %1")
                                         .arg(contactManager->getContactCount()));
            applySorting();  // Use applySorting instead of onRefreshTable
        } else {
            QMessageBox::warning(this, "Error", "Failed to import contacts!");
        }
    }
}

void MainWindow::onClearSearch() {
    ui->searchLineEdit->clear();
    applySorting();
}

void MainWindow::onTableSelectionChanged() {
    bool hasSelection = !ui->contactTable->selectedItems().isEmpty();
    ui->editButton->setEnabled(hasSelection);
    ui->deleteButton->setEnabled(hasSelection);
    ui->viewButton->setEnabled(hasSelection);
}

Contact MainWindow::getSelectedContact() {
    int row = ui->contactTable->currentRow();
    int id = ui->contactTable->item(row, 0)->text().toInt();
    return *contactManager->getContactById(id);
}

bool MainWindow::isContactSelected() {
    return !ui->contactTable->selectedItems().isEmpty();
}

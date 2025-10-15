/**
 * @file mainwindow.h
 * @brief Main window class for the Contact Management System UI
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QStandardPaths>
#include <QComboBox>  // Add this
#include "contactmanager.h"
#include "adddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Enum for sort options
    enum SortOption {
        SortByNameAsc,
        SortByNameDesc,
        SortByIDAsc,
        SortByIDDesc
    };

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onAddContact();
    void onEditContact();
    void onDeleteContact();
    void onSearchContact();
    void onRefreshTable();
    void onViewDetails();
    void onExportContacts();
    void onImportContacts();
    void onClearSearch();
    void onTableSelectionChanged();
    void onSortChanged(int index);  // Add this

private:
    Ui::MainWindow *ui;
    ContactManager *contactManager;
    QString dataFilePath;
    SortOption currentSortOption;  // Add this

    void setupUI();
    void loadStyleSheet();
    void populateTable(const std::vector<Contact>& contacts);
    Contact getSelectedContact();
    bool isContactSelected();

    void autoSaveContacts();
    void autoLoadContacts();
    QString getDefaultDataPath();
    void applySorting();  // Add this
};

#endif // MAINWINDOW_H

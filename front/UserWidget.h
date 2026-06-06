#ifndef USERWIDGET_H
#define USERWIDGET_H

#include "UserModel.h"
#include "UserService.h"

#include <QWidget>
#include <QVector>

class QLineEdit;
class QComboBox;
class QPushButton;
class QTableWidget;


class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);

private:
    UserService* userService;

    QLineEdit* searchEdit;

    QComboBox* roleFilterBox;

    QPushButton* refreshBtn;


    QTableWidget* userTable;

    QLineEdit* usernameEdit;

    QLineEdit* fullNameEdit;

    QLineEdit* passwordEdit;

    QComboBox* roleBox;


    QPushButton* addBtn;

    QPushButton* updateBtn;

    QPushButton* deleteBtn;

    QPushButton* clearBtn;

    QVector<User> users;

    int currentSelectedRow = -1;

private:

    void setupUI();

    void setupSearchArea();

    void setupTable();

    void setupForm();

    void setupButtons();

    void setupStyles();

    void setupConnections();

    void refreshTable();

    void clearForm();

    bool validateInput();

    void fillFormFromTable(int row);

private slots:

    void addUser();

    void updateUser();

    void deleteUser();

    void searchUsers();

    void handleTableClicked(
        int row,
        int column
        );

    void handleUsersLoaded(
        QVector<User> data
        );

    void handleApiError(
        QString message
        );
};

#endif
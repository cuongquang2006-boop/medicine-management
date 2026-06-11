#include "UserWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QLineEdit>
#include <QComboBox>

#include <QPushButton>

#include <QTableWidget>
#include <QHeaderView>

#include <QMessageBox>

#include <QLabel>


UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    setupSearchArea();

    setupTable();

    setupForm();

    setupButtons();

    setupStyles();

    userService =
        new UserService(this);

    setupConnections();

    connect(userService,
            &UserService::usersLoaded,
            this,
            &UserWidget::handleUsersLoaded);

    connect(userService,
            &UserService::errorOccurred,
            this,
            &UserWidget::handleApiError);

    userService->fetchUsers();
}


void UserWidget::setupUI()
{
    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        25,25,25,25
        );

    mainLayout->setSpacing(20);
}


void UserWidget::setupSearchArea()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* searchLayout =
        new QHBoxLayout;

    searchEdit = new QLineEdit;

    searchEdit->setPlaceholderText(
        "Search user..."
        );

    roleFilterBox =
        new QComboBox;

    roleFilterBox->addItems({
        "All Roles",
        "Doctor",
        "Admin",
        "Receptionist"
    });

    refreshBtn =
        new QPushButton("Refresh");

    searchLayout->addWidget(searchEdit);

    searchLayout->addWidget(roleFilterBox);

    searchLayout->addWidget(refreshBtn);

    mainLayout->addLayout(searchLayout);
}


void UserWidget::setupTable()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    userTable =
        new QTableWidget;

    userTable->setColumnCount(5);

    userTable->setHorizontalHeaderLabels({
        "ID",
        "Username",
        "Full Name",
        "Role",
        "Created At"
    });

    userTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    userTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    userTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    userTable->setAlternatingRowColors(true);

    userTable->verticalHeader()
        ->setVisible(false);

    mainLayout->addWidget(userTable);
}


void UserWidget::setupForm()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QFormLayout* formLayout =
        new QFormLayout;

    usernameEdit =
        new QLineEdit;

    usernameEdit->setPlaceholderText(
        "Enter username"
        );

    fullNameEdit =
        new QLineEdit;

    fullNameEdit->setPlaceholderText(
        "Enter full name"
        );

    passwordEdit =
        new QLineEdit;

    passwordEdit->setPlaceholderText(
        "Enter password"
        );

    passwordEdit->setEchoMode(
        QLineEdit::Password
        );

    roleBox =
        new QComboBox;

    roleBox->addItems({
        "Doctor",
        "Admin",
        "Receptionist"
    });

    formLayout->addRow(
        "Username:",
        usernameEdit
        );

    formLayout->addRow(
        "Full Name:",
        fullNameEdit
        );

    formLayout->addRow(
        "Password:",
        passwordEdit
        );

    formLayout->addRow(
        "Role:",
        roleBox
        );

    mainLayout->addLayout(formLayout);
}


void UserWidget::setupButtons()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* btnLayout =
        new QHBoxLayout;

    addBtn =
        new QPushButton("Add User");

    updateBtn =
        new QPushButton("Update User");

    deleteBtn =
        new QPushButton("Delete User");

    clearBtn =
        new QPushButton("Clear Form");

    btnLayout->addWidget(addBtn);

    btnLayout->addWidget(updateBtn);

    btnLayout->addWidget(deleteBtn);

    btnLayout->addWidget(clearBtn);

    mainLayout->addLayout(btnLayout);
}


void UserWidget::setupStyles()
{
    setStyleSheet(R"(

        QWidget{
            background:#f4f6f9;
        }

        QLabel{
            color:#111827;
        }

        QLineEdit,
        QComboBox{

            background:white;

            color:#111827;

            border:1px solid #dbeafe;

            border-radius:10px;

            padding:8px;

            font-size:14px;
        }

        QLineEdit:focus,
        QComboBox:focus{

            border:2px solid #93c5fd;
        }

        QPushButton{

            background:#2563eb;

            color:white;

            border:1px solid #2563eb;

            border-radius:10px;

            padding:10px;

            font-size:14px;
        }

        QPushButton:hover{

            background:#1d4ed8;
        }

        QTableWidget{

            background:white;

            color:#111827;

            border:1px solid #dbeafe;

            border-radius:10px;

            font-size:14px;

            gridline-color:#e5e7eb;

            alternate-background-color:#f9fafb;
        }

        QHeaderView::section{

            background:#f3f4f6;

            color:#111827;

            border:none;

            padding:10px;

            font-weight:bold;
        }

    )");
}


void UserWidget::setupConnections()
{
    connect(addBtn,
            &QPushButton::clicked,
            this,
            &UserWidget::addUser);

    connect(updateBtn,
            &QPushButton::clicked,
            this,
            &UserWidget::updateUser);

    connect(deleteBtn,
            &QPushButton::clicked,
            this,
            &UserWidget::deleteUser);

    connect(clearBtn,
            &QPushButton::clicked,
            this,
            &UserWidget::clearForm);

    connect(searchEdit,
            &QLineEdit::textChanged,
            this,
            &UserWidget::searchUsers);

    connect(roleFilterBox,
            &QComboBox::currentTextChanged,
            this,
            &UserWidget::searchUsers);

    connect(userTable,
            &QTableWidget::cellClicked,
            this,
            &UserWidget::handleTableClicked);

    connect(refreshBtn,
            &QPushButton::clicked,
            userService,
            &UserService::fetchUsers);
}



void UserWidget::refreshTable()
{
    userTable->setRowCount(0);

    for(int i = 0;
         i < users.size();
         ++i)
    {
        const User& u =
            users[i];

        userTable->insertRow(i);

        userTable->setItem(
            i,0,
            new QTableWidgetItem(
                QString::number(u.id)
                )
            );

        userTable->setItem(
            i,1,
            new QTableWidgetItem(
                u.username
                )
            );

        userTable->setItem(
            i,2,
            new QTableWidgetItem(
                u.fullName
                )
            );

        userTable->setItem(
            i,3,
            new QTableWidgetItem(
                u.role
                )
            );

        userTable->setItem(
            i,4,
            new QTableWidgetItem(
                u.createdAt
                )
            );
    }
}


void UserWidget::clearForm()
{
    usernameEdit->clear();

    fullNameEdit->clear();

    passwordEdit->clear();

    roleBox->setCurrentIndex(0);

    currentSelectedRow = -1;
}

bool UserWidget::validateInput()
{
    if(usernameEdit->text()
            .trimmed()
            .isEmpty())
    {
        QMessageBox::warning(
            this,
            "Validation",
            "Username is required"
            );

        return false;
    }

    if(fullNameEdit->text()
            .trimmed()
            .isEmpty())
    {
        QMessageBox::warning(
            this,
            "Validation",
            "Full name is required"
            );

        return false;
    }

    if(passwordEdit->text()
            .trimmed()
            .isEmpty())
    {
        QMessageBox::warning(
            this,
            "Validation",
            "Password is required"
            );

        return false;
    }

    return true;
}



void UserWidget::fillFormFromTable(int row)
{
    const User& u =
        users[row];

    usernameEdit->setText(
        u.username
        );

    fullNameEdit->setText(
        u.fullName
        );

    passwordEdit->setText(
        u.password
        );

    roleBox->setCurrentText(
        u.role
        );
}


void UserWidget::addUser()
{
    if(!validateInput())
        return;

    User u;

    u.username =
        usernameEdit->text();

    u.fullName =
        fullNameEdit->text();

    u.password =
        passwordEdit->text();

    u.role =
        roleBox->currentText();

    userService->createUser(u);

    clearForm();
}


void UserWidget::updateUser()
{
    if(currentSelectedRow < 0)
        return;

    if(passwordEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(
            this,
            "Validation",
            "Password is required"
            );

        return;
    }

    User u =
        users[currentSelectedRow];

    u.username =
        usernameEdit->text();

    u.fullName =
        fullNameEdit->text();

    u.password =
        passwordEdit->text();

    u.role =
        roleBox->currentText();

    userService->updateUser(u);

    clearForm();
}

void UserWidget::deleteUser()
{
    if(currentSelectedRow < 0)
        return;

    int userId =
        users[currentSelectedRow].id;

    userService->deleteUser(userId);

    clearForm();
}

void UserWidget::searchUsers()
{
    QString keyword =
        searchEdit->text().trimmed();

    QString roleFilter =
        roleFilterBox->currentText();

    for(int row = 0;
         row < userTable->rowCount();
         ++row)
    {
        bool usernameMatch =
            userTable
                ->item(row,1)
                ->text()
                .contains(
                    keyword,
                    Qt::CaseInsensitive
                    );

        bool roleMatch =
            roleFilter == "All Roles"
            ||
            userTable
                    ->item(row,3)
                    ->text() == roleFilter;

        userTable->setRowHidden(
            row,
            !(usernameMatch && roleMatch)
            );
    }
}


void UserWidget::handleTableClicked(
    int row,
    int column
    )
{
    Q_UNUSED(column);

    currentSelectedRow = row;

    fillFormFromTable(row);
}

void UserWidget::handleUsersLoaded(
    QVector<User> data
    )
{
    users = data;

    refreshTable();
}


void UserWidget::handleApiError(
    QString message
    )
{
    QMessageBox::critical(
        this,
        "API Error",
        message
        );
}
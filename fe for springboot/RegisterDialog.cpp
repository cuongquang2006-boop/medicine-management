#include "RegisterDialog.h"

#include <QVBoxLayout>
#include <QFormLayout>

#include <QLineEdit>
#include <QComboBox>

#include <QPushButton>

#include <QLabel>

#include <QMessageBox>


RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();

    setupStyles();

    userService =
        new UserService(this);

    setupConnections();

    setWindowTitle(
        "Register Account"
        );

    resize(420,500);
}

void RegisterDialog::setupUI()
{
    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    QFormLayout* formLayout =
        new QFormLayout;

    usernameEdit =
        new QLineEdit;

    fullNameEdit =
        new QLineEdit;

    passwordEdit =
        new QLineEdit;

    confirmPasswordEdit =
        new QLineEdit;

    roleBox =
        new QComboBox;

    registerBtn =
        new QPushButton(
            "Create Account"
            );

    statusLabel =
        new QLabel;

    passwordEdit->setEchoMode(
        QLineEdit::Password
        );

    confirmPasswordEdit->setEchoMode(
        QLineEdit::Password
        );

    usernameEdit->setPlaceholderText(
        "Enter username"
        );

    fullNameEdit->setPlaceholderText(
        "Enter full name"
        );

    passwordEdit->setPlaceholderText(
        "Enter password"
        );

    confirmPasswordEdit->setPlaceholderText(
        "Confirm password"
        );

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
        "Confirm Password:",
        confirmPasswordEdit
        );

    formLayout->addRow(
        "Role:",
        roleBox
        );

    mainLayout->addLayout(formLayout);

    mainLayout->addWidget(registerBtn);

    mainLayout->addWidget(statusLabel);
}

void RegisterDialog::setupStyles()
{
    setStyleSheet(R"(

        QWidget{
            background:#f4f6f9;
        }

        QLineEdit,
        QComboBox{

            background:white;

            border:1px solid #dbeafe;

            border-radius:10px;

            padding:10px;

            font-size:14px;
        }

        QPushButton{

            background:#2563eb;

            color:white;

            border:none;

            border-radius:10px;

            padding:12px;

            font-size:14px;

            font-weight:bold;
        }

        QPushButton:hover{

            background:#1d4ed8;
        }

    )");
}

void RegisterDialog::setupConnections()
{
    connect(registerBtn,
            &QPushButton::clicked,
            this,
            &RegisterDialog::handleRegister);

    connect(userService,
            &UserService::usersLoaded,
            this,
            &RegisterDialog::handleUsersLoaded);

    connect(userService,
            &UserService::errorOccurred,
            this,
            &RegisterDialog::handleApiError);
}

bool RegisterDialog::validateInput()
{
    if(usernameEdit->text()
            .trimmed()
            .isEmpty())
    {
        statusLabel->setText(
            "Username is required"
            );

        return false;
    }

    if(fullNameEdit->text()
            .trimmed()
            .isEmpty())
    {
        statusLabel->setText(
            "Full name is required"
            );

        return false;
    }

    if(passwordEdit->text()
            .trimmed()
            .isEmpty())
    {
        statusLabel->setText(
            "Password is required"
            );

        return false;
    }

    if(passwordEdit->text()
        != confirmPasswordEdit->text())
    {
        statusLabel->setText(
            "Passwords do not match"
            );

        return false;
    }

    return true;
}

void RegisterDialog::handleRegister()
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

    QMessageBox::information(
        this,
        "Success",
        "Account created successfully"
        );

    accept();
}

void RegisterDialog::handleUsersLoaded(QVector<User> users)
{
    Q_UNUSED(users);
}


void RegisterDialog::handleApiError(QString message)
{
    statusLabel->setText(message);
}
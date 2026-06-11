#include "LoginWindow.h"

#include "MainWindow.h"

#include "RegisterDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLineEdit>

#include <QPushButton>

#include <QLabel>

#include <QMessageBox>

#include <QFrame>


LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    setupLeftPanel();

    setupRightPanel();

    setupStyles();

    authService =
        new AuthService(this);

    setupConnections();

    resize(1100,650);

    setWindowTitle(
        "Medicine Management Login"
        );
}



void LoginWindow::setupUI()
{
    QHBoxLayout* rootLayout =
        new QHBoxLayout(this);

    rootLayout->setContentsMargins(
        0,0,0,0
        );

    rootLayout->setSpacing(0);

    leftPanel = new QFrame;

    rightPanel = new QFrame;

    leftPanel->setMinimumWidth(520);

    rootLayout->addWidget(leftPanel);

    rootLayout->addWidget(rightPanel);
}


void LoginWindow::setupLeftPanel()
{
    QVBoxLayout* layout =
        new QVBoxLayout(leftPanel);

    layout->setContentsMargins(
        60,60,60,60
        );

    layout->setSpacing(20);

    layout->addStretch();

    QLabel* title =
        new QLabel(
            "Medicine Management System"
            );

    title->setWordWrap(true);

    title->setStyleSheet(R"(
        font-size:42px;
        font-weight:bold;
        color:white;
    )");

    QLabel* desc =
        new QLabel(
            "Professional healthcare "
            "management platform for "
            "modern clinics and hospitals."
            );

    desc->setWordWrap(true);

    desc->setStyleSheet(R"(
        font-size:18px;
        color:rgba(255,255,255,0.85);
    )");

    layout->addWidget(title);

    layout->addWidget(desc);

    layout->addStretch();

    leftPanel->setStyleSheet(R"(

        background:qlineargradient(
            x1:0,y1:0,
            x2:1,y2:1,

            stop:0 #2563eb,
            stop:1 #1d4ed8
        );

    )");
}


void LoginWindow::setupRightPanel()
{
    QVBoxLayout* outerLayout =
        new QVBoxLayout(rightPanel);

    outerLayout->setContentsMargins(
        80,60,80,60
        );

    outerLayout->setSpacing(0);

    outerLayout->addStretch();

    QFrame* formCard =
        new QFrame;

    formCard->setMinimumWidth(380);

    QVBoxLayout* layout =
        new QVBoxLayout(formCard);

    layout->setSpacing(18);

    QLabel* loginLabel =
        new QLabel("Login");

    loginLabel->setStyleSheet(R"(
        font-size:34px;
        font-weight:bold;
        color:#111827;
    )");

    QLabel* subLabel =
        new QLabel(
            "Welcome back doctor"
            );

    subLabel->setStyleSheet(R"(
        font-size:15px;
        color:#6b7280;
    )");

    usernameEdit =
        new QLineEdit;

    usernameEdit->setPlaceholderText(
        "Enter username"
        );

    passwordEdit =
        new QLineEdit;

    passwordEdit->setPlaceholderText(
        "Enter password"
        );

    passwordEdit->setEchoMode(
        QLineEdit::Password
        );

    loginBtn =
        new QPushButton("Login");

    registerBtn =
        new QPushButton("Register");

    statusLabel =
        new QLabel;

    statusLabel->setAlignment(
        Qt::AlignCenter
        );

    statusLabel->setStyleSheet(R"(
        color:#ef4444;
        font-size:13px;
    )");

    layout->addWidget(loginLabel);

    layout->addWidget(subLabel);

    layout->addSpacing(10);

    layout->addWidget(usernameEdit);

    layout->addWidget(passwordEdit);

    layout->addSpacing(8);

    layout->addWidget(loginBtn);

    layout->addWidget(registerBtn);

    layout->addWidget(statusLabel);

    outerLayout->addWidget(
        formCard,
        0,
        Qt::AlignCenter
        );

    outerLayout->addStretch();

    formCard->setStyleSheet(R"(

        QFrame{

            background:white;

            border-radius:20px;
        }

    )");
}


void LoginWindow::setupStyles()
{
    setStyleSheet(R"(

        QWidget{
            background:#f4f6f9;
            color:#111827;
        }

        QLineEdit{

            background:white;

            color:#111827;

            border:1px solid #dbeafe;

            border-radius:12px;

            padding:12px;

            font-size:15px;

            min-height:24px;
        }

        QLineEdit:focus{

            border:2px solid #93c5fd;
        }

        QPushButton{

            background:#2563eb;

            color:white;

            border:none;

            border-radius:12px;

            padding:12px;

            font-size:15px;

            font-weight:bold;
        }

        QPushButton:hover{

            background:#1d4ed8;
        }

    )");
}


void LoginWindow::setupConnections()
{
    connect(loginBtn,
            &QPushButton::clicked,
            this,
            &LoginWindow::handleLogin);

    connect(registerBtn,
            &QPushButton::clicked,
            this,
            &LoginWindow::handleRegister);

    connect(authService,
            &AuthService::loginSuccess,
            this,
            &LoginWindow::handleLoginSuccess);

    connect(authService,
            &AuthService::loginFailed,
            this,
            &LoginWindow::handleLoginFailed);
}

bool LoginWindow::validateInput()
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

    if(passwordEdit->text()
            .trimmed()
            .isEmpty())
    {
        statusLabel->setText(
            "Password is required"
            );

        return false;
    }

    statusLabel->clear();

    return true;
}


void LoginWindow::handleLogin()
{
    if(!validateInput())
        return;

    QString username =
        usernameEdit->text().trimmed();

    QString password =
        passwordEdit->text().trimmed();

    loginBtn->setEnabled(false);

    statusLabel->setText(
        "Logging in..."
        );

    authService->login(
        username,
        password
        );
}

void LoginWindow::handleRegister()
{
    RegisterDialog dialog(this);

    dialog.exec();
}

void LoginWindow::handleLoginSuccess()
{
    statusLabel->setText(
        "Login successful"
        );

    MainWindow* window =
        new MainWindow;

    window->show();

    close();
}


void LoginWindow::handleLoginFailed(
    QString message
    )
{
    loginBtn->setEnabled(true);

    statusLabel->setText(
        message
        );
}
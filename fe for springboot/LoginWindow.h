#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "AuthService.h"

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private:
    AuthService* authService;

    QWidget* leftPanel;

    QWidget* rightPanel;

    QLineEdit* usernameEdit;

    QLineEdit* passwordEdit;

    QPushButton* loginBtn;

    QPushButton* registerBtn;

    QLabel* statusLabel;

private:

    void setupUI();

    void setupLeftPanel();

    void setupRightPanel();

    void setupStyles();

    void setupConnections();

    bool validateInput();

private slots:

    void handleLogin();

    void handleRegister();

    void handleLoginSuccess();

    void handleLoginFailed(QString message);
};

#endif
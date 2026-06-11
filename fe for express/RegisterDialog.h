#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "UserService.h"

#include <QDialog>

class QLineEdit;
class QComboBox;
class QPushButton;
class QLabel;

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(
        QWidget *parent = nullptr
        );

private:

    UserService* userService;

    QLineEdit* usernameEdit;

    QLineEdit* fullNameEdit;

    QLineEdit* passwordEdit;

    QLineEdit* confirmPasswordEdit;

    QComboBox* roleBox;

    QPushButton* registerBtn;

    QLabel* statusLabel;

private:

    void setupUI();

    void setupStyles();

    void setupConnections();

    bool validateInput();

private slots:

    void handleRegister();

    void handleUsersLoaded(
        QVector<User> users
        );

    void handleApiError(
        QString message
        );
};

#endif
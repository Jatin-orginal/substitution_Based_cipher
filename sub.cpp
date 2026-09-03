#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>
#include <string>
#include <algorithm>
#include <random>

class SubstitutionCipherGUI : public QWidget {
private:
    std::string list_chars;
    std::string shuffled_chars;

    QTextEdit *inputText;
    QTextEdit *outputText;

    // Generate New Key
    void newKey() {
        shuffled_chars = list_chars;
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(shuffled_chars.begin(), shuffled_chars.end(), g);
    }

    // Message for new key
    void newKeyMessage() {
        newKey();
        QMessageBox::information(this, "Key", "New Key Generated Successfully!");
    }

    // Show Key
    void showKey() {
        QString original = QString::fromStdString(list_chars);
        QString shuffled = QString::fromStdString(shuffled_chars);
        
        QMessageBox::information(
            this,
            "Cipher Key",
            "Original:\n" + original + "\n\nEncrypted:\n" + shuffled
        );
    }

    // Encrypt Function
    void encrypt() {
        QString message = inputText->toPlainText().trimmed();
        std::string msgStr = message.toStdString();
        std::string encrypted = "";

        for (char letter : msgStr) {
            size_t pos = list_chars.find(letter);
            if (pos != std::string::npos) {
                encrypted += shuffled_chars[pos];
            } else {
                encrypted += letter;
            }
        }

        outputText->setText(QString::fromStdString(encrypted));
    }

    // Decrypt Function
    void decrypt() {
        QString message = inputText->toPlainText().trimmed();
        std::string msgStr = message.toStdString();
        std::string decrypted = "";

        for (char letter : msgStr) {
            size_t pos = shuffled_chars.find(letter);
            if (pos != std::string::npos) {
                decrypted += list_chars[pos];
            } else {
                decrypted += letter;
            }
        }

        outputText->setText(QString::fromStdString(decrypted));
    }

public:
    SubstitutionCipherGUI(QWidget *parent = nullptr) : QWidget(parent) {
        // Equivalent to Python's string.printable[:-6] (digits + lowercase + uppercase + punctuation)
        list_chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
        newKey();

        // Window setup
        setWindowTitle("Substitution Cipher");
        resize(700, 500);
        setStyleSheet("background-color: #0f172a;");

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(30, 20, 30, 20);

        // Title
        QLabel *title = new QLabel("Substitution Cipher", this);
        title->setFont(QFont("Arial", 24, QFont::Bold));
        title->setStyleSheet("color: #38bdf8; background: transparent;");
        title->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(title);

        // Input Label
        QLabel *inputLabel = new QLabel("Enter Message", this);
        inputLabel->setFont(QFont("Arial", 14));
        inputLabel->setStyleSheet("color: white; background: transparent;");
        mainLayout->addWidget(inputLabel);

        // Input Box
        inputText = new QTextEdit(this);
        inputText->setFont(QFont("Consolas", 12));
        inputText->setFixedHeight(100);
        inputText->setStyleSheet("background-color: #1e293b; color: white; border: 1px solid #334155; border-radius: 4px;");
        mainLayout->addWidget(inputText);

        // Buttons Frame
        QHBoxLayout *buttonLayout = new QHBoxLayout();

        QPushButton *encryptBtn = new QPushButton("Encrypt", this);
        encryptBtn->setFont(QFont("Arial", 12, QFont::Bold));
        encryptBtn->setStyleSheet("background-color: #2563eb; color: white; padding: 8px; border-radius: 4px;");
        connect(encryptBtn, &QPushButton::clicked, this, &SubstitutionCipherGUI::encrypt);
        buttonLayout->addWidget(encryptBtn);

        QPushButton *decryptBtn = new QPushButton("Decrypt", this);
        decryptBtn->setFont(QFont("Arial", 12, QFont::Bold));
        decryptBtn->setStyleSheet("background-color: #16a34a; color: white; padding: 8px; border-radius: 4px;");
        connect(decryptBtn, &QPushButton::clicked, this, &SubstitutionCipherGUI::decrypt);
        buttonLayout->addWidget(decryptBtn);

        QPushButton *newKeyBtn = new QPushButton("New Key", this);
        newKeyBtn->setFont(QFont("Arial", 12, QFont::Bold));
        newKeyBtn->setStyleSheet("background-color: #f59e0b; color: black; padding: 8px; border-radius: 4px;");
        connect(newKeyBtn, &QPushButton::clicked, this, &SubstitutionCipherGUI::newKeyMessage);
        buttonLayout->addWidget(newKeyBtn);

        QPushButton *showKeyBtn = new QPushButton("Show Key", this);
        showKeyBtn->setFont(QFont("Arial", 12, QFont::Bold));
        showKeyBtn->setStyleSheet("background-color: #9333ea; color: white; padding: 8px; border-radius: 4px;");
        connect(showKeyBtn, &QPushButton::clicked, this, &SubstitutionCipherGUI::showKey);
        buttonLayout->addWidget(showKeyBtn);

        mainLayout->addLayout(buttonLayout);

        // Output Label
        QLabel *outputLabel = new QLabel("Output", this);
        outputLabel->setFont(QFont("Arial", 14));
        outputLabel->setStyleSheet("color: white; background: transparent;");
        mainLayout->addWidget(outputLabel);

        // Output Box
        outputText = new QTextEdit(this);
        outputText->setFont(QFont("Consolas", 12));
        outputText->setFixedHeight(100);
        outputText->setStyleSheet("background-color: #1e293b; color: #38bdf8; border: 1px solid #334155; border-radius: 4px;");
        mainLayout->addWidget(outputText);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SubstitutionCipherGUI window;
    window.show();
    return app.exec();
}

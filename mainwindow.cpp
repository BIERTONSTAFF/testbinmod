#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Preferences");
    setFixedSize(400, 400);

    auto centralWidget = new QWidget(this);
    auto layout = new QVBoxLayout(centralWidget);

    setCentralWidget(centralWidget);

    auto inputMask = new QLineEdit();
    inputMask->setPlaceholderText("Input Mask (e.g. *.bin)");

    auto deleteInputFiles = new Setting<QCheckBox>("Delete input files", new QCheckBox());

    auto outputDirectory = new QLineEdit();
    outputDirectory->setPlaceholderText("Output directory (e.g. ./output)");

    auto overwriteOutputFiles = new Setting<QComboBox>("Overwrite output files", []{
        auto cb = new QComboBox();
        cb->addItems(QStringList{"Overwrite", "Create Unique Name"});

        return cb;
    }());

    auto mode = new Setting<QComboBox>("Mode", []{
        auto cb = new QComboBox();
        cb->addItems(QStringList{"Timer", "Run Once"});

        return cb;
    }());


    this->checkInterval = new Setting<QSpinBox>("Check interval", []{
        auto sb = new QSpinBox();
        sb->setMinimum(1);
        sb->setSuffix(" s.");

        return sb;
    }());

    auto xorKey = new QLineEdit();
    auto hexValidator = new QRegularExpressionValidator(QRegularExpression("^[0-9A-Fa-f]{16}$"), xorKey);
    xorKey->setPlaceholderText("XOR key");
    xorKey->setValidator(hexValidator);

    auto execute = new QPushButton();
    execute->setText("Execute");

    connect(mode->getChild(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onModeChanged);

    connect(execute, &QPushButton::clicked, this, [=](){
        QByteArray inputXorKey = QByteArray::fromHex(xorKey->text().toUtf8());

        if (inputXorKey.size() < 8) {
            inputXorKey = inputXorKey.leftJustified(8, '\0');
        }

        this->fileProcessor = new FileProcessor(
            inputMask->text(),
            outputDirectory->text(),
            deleteInputFiles->getChild()->isChecked(),
            overwriteOutputFiles->getChild()->currentIndex(),
            mode->getChild()->currentIndex(),
            inputXorKey,
            checkInterval->getChild()->value()
        );

        this->fileProcessor->start();
    });

    layout->addWidget(inputMask);
    layout->addWidget(deleteInputFiles);
    layout->addWidget(outputDirectory);
    layout->addWidget(overwriteOutputFiles);
    layout->addWidget(mode);
    layout->addWidget(this->checkInterval);
    layout->addWidget(xorKey);
    layout->addWidget(execute);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onModeChanged(int idx)
{
    checkInterval->setEnabled(idx == 0);
}

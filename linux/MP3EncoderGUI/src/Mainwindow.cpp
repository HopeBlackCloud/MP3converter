#include "Mainwindow.h"
#include <QFileDialog>
#include "ui_Mainwindow.h"

#include "EncoderController.h"

using namespace MediaFramework;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->toolButtonEncAll,       SIGNAL(clicked()), this, SLOT(EncodeClicked()));
    connect(ui->toolButtonSelectFolder, SIGNAL(clicked()), this, SLOT(SelectFolderClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::UpdateFileList()
{
    QStringList filterWavMp3;
    filterWavMp3<<QString("*.wav")<<QString("*.mp3");

    ui->listWidgetWavFiles->clear();
    ui->listWidgetMP3Files->clear();

    QDir dir(dirPath);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setNameFilters(filterWavMp3);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.completeSuffix() == "wav")
            ui->listWidgetWavFiles->addItem(QString("%1").arg(fileInfo.fileName()));
        else if(fileInfo.completeSuffix() == "mp3")
            ui->listWidgetMP3Files->addItem(QString("%1").arg(fileInfo.fileName()));
    }
}

void MainWindow::SelectFolderClicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QCoreApplication::applicationDirPath());

    dirPath = dialog.getExistingDirectory();

    if (!dirPath.isEmpty())
    {
        ui->labelList->setText(dirPath);

        UpdateFileList();

        if (ui->listWidgetWavFiles->count() >= 1)
            ui->toolButtonEncAll->setEnabled(true);
    }
}

void MainWindow::EncodeClicked()
{
   EncoderController encoderController(dirPath.toStdString());
   encoderController.StartEncoders();
   encoderController.Cleanup();

   UpdateFileList();
}

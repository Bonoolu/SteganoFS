#include "showfilesysteminfodialog.h"
#include "ui_showfilesysteminfodialog.h"

ShowFileSystemInfoDialog::ShowFileSystemInfoDialog(QWidget *parent)
    :
    QDialog(parent),
    ui(new Ui::ShowFileSystemInfoDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Filesystem info");

    /*   FÜR SYSTEMINFO
 *
 *     stbuf->f_bsize = hiddenFat->blockSize;    // Filesystem block size
    stbuf->f_frsize = hiddenFat->blockSize;   // Fundamental filesystem block size
    stbuf->f_blocks = hiddenFat->amountBlocks; // Total data blocks in filesystem
    stbuf->f_bfree = getFreeDiskSpace(hiddenFat) / hiddenFat->blockSize;   // Free blocks
    stbuf->f_bavail = getFreeDiskSpace(hiddenFat) / hiddenFat->blockSize;  // Free blocks available to non-superuser
    stbuf->f_namemax = STEGANOFS_MAX_FILENAME_LENGTH;
*/



}

ShowFileSystemInfoDialog::~ShowFileSystemInfoDialog()
{
    delete ui;
}

void ShowFileSystemInfoDialog::on_closeButton_clicked()
{
    this->close();
}

void ShowFileSystemInfoDialog::showFilesystemInfo(SteganoFsAdapter &sfa)
{
    struct statvfs info = sfa.getFilesystemInfo();
    QString text;

    text = "Filesystem block size:\t\t\t" + QString::number(info.f_bsize) +
        "\n\nFundamental filesystem block size:\t" + QString::number(info.f_frsize) +
        "\n\nTotal data blocks in filesystem:\t\t" + QString::number(info.f_blocks) +
        "\n\nFree blocks: \t\t\t\t" + QString::number(info.f_bfree) +
        "\n\nFree blocks available to non-superuser:\t" + QString::number(info.f_bavail);
    "\n\nFree blocks available to non-superuser:\t" + QString::number(info.f_bavail);

    ui->filesystemInfoLabel->setText(text);
}

void ShowFileSystemInfoDialog::setLightmodeOn(bool newLightsmodeOn)
{
    m_lightmodeOn = newLightsmodeOn;


    if (this->m_lightmodeOn) {
        this->setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->closeButton->setStyleSheet(
            "background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891); border-radius: 5px; padding: 5px; color: white; border: 1px solid #1073b4; padding: 2px 5px;");
        ui->filesystemInfoLabel->setStyleSheet("background-color: #efefef; color: black;");

    }

    if (!this->m_lightmodeOn) {

        this->setStyleSheet("background-color: #111111; color: #fafafa;");
        ui->closeButton->setStyleSheet(
            "background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); border-radius: 5px; color: white; border: 1px solid #607cff; padding: 2px 5px;");
        ui->filesystemInfoLabel->setStyleSheet("background-color: #1e1e1e; color: white; padding: 2px 7px ; ");

    }
}


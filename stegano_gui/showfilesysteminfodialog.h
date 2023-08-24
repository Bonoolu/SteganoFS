#ifndef SHOWFILESYSTEMINFODIALOG_H
#define SHOWFILESYSTEMINFODIALOG_H

#include <QDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"
#include <sys/statfs.h>

namespace Ui {
class ShowFileSystemInfoDialog;
}

class ShowFileSystemInfoDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a ShowFileSystemInfoDialog.
     * @param parent The parent widget.
     */
    explicit ShowFileSystemInfoDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructor for ShowFileSystemInfoDialog.
     */
    ~ShowFileSystemInfoDialog();

    /**
     * @brief Sets the light mode state.
     * @param newLightmodeOn The new light mode state.
     */
    void setLightmodeOn(bool newLightmodeOn);

    /**
     * @brief Displays filesystem information.
     * @param sfa The SteganoFsAdapter for filesystem access.
     */
    void showFilesystemInfo(SteganoFsAdapter &sfa);

private slots:
    /**
     * @brief Slot function for the close button click event.
     */
    void on_closeButton_clicked();

private:
    Ui::ShowFileSystemInfoDialog *ui; /**< The UI components. */
    bool m_lightmodeOn; /**< The state of light mode. */
};

#endif // SHOWFILESYSTEMINFODIALOG_H

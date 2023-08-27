#ifndef FORMATFILESYSTEMDIALOG_H
#define FORMATFILESYSTEMDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"

namespace Ui
{
class FormatFileSystemDialog;
}

class FormatFileSystemDialog: public QDialog
{
Q_OBJECT

public:

    /**
    * \class FormatFileSystemDialog
    * \brief Dialog for mounting a filesystem from a specific path.
    *
    * This class provides a dialog for selecting a mounting path and filesystem path,
    * along with additional settings like light mode. It also allows connecting a
    * SteganoFsAdapter to handle the mounting process.
    */
    explicit FormatFileSystemDialog(QWidget *parent = nullptr);

    /**
     * \brief Destructs the FormatFileSystemDialog.
     */
    ~FormatFileSystemDialog() override;

    /**
     * \brief Checks if light mode is enabled.
     * \return True if light mode is enabled, false otherwise.
     */
    [[maybe_unused]] bool lightmodeOn() const;

    /**
     * \brief Sets the light mode.
     * \param newLightmodeOn True to enable light mode, false to disable.
     */
    void setLightmodeOn(bool newLightmodeOn);

    /**
     * \brief Returns the selected filesystem path.
     * \return The selected filesystem path.
     */
    [[nodiscard]] QString filesystemPath() const;

    /**
     * \brief Sets the filesystem path.
     * \param newFilesystemPath The new filesystem path.
     */
    [[maybe_unused]] void setFilesystemPath(const QString &newFilesystemPath);

    /**
     * \brief Returns the associated SteganoFsAdapter.
     * \return The associated SteganoFsAdapter.
     */
    [[nodiscard]] SteganoFsAdapter *adapter() const;

    /**
     * \brief Sets the SteganoFsAdapter.
     * \param newAdapter The new SteganoFsAdapter.
     */
    void setAdapter(SteganoFsAdapter *newAdapter);

private slots:
    void on_fileSystemLineEdit_textChanged(const QString &arg1);

    void on_browseButton_clicked();

private:
    Ui::FormatFileSystemDialog *ui; ///< The UI components.
    QString m_filesystemPath;    ///< The selected filesystem path.
    bool m_lightmodeOn;          ///< Flag indicating light mode status.
    QFileDialog *m_fsDlg = nullptr;    ///< Dialog for selecting filesystem path.
    SteganoFsAdapter *m_adapter = nullptr; ///< Associated SteganoFsAdapter.
};

#endif // FORMATFILESYSTEMDIALOG_H

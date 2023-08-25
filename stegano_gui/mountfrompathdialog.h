#ifndef MOUNTFROMPATHDIALOG_H
#define MOUNTFROMPATHDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"


namespace Ui
{
class MountFromPathDialog;
}
/**
 * \class MountFromPathDialog
 * \brief Dialog for mounting a filesystem from a specific path.
 *
 * This class provides a dialog for selecting a mounting path and filesystem path,
 * along with additional settings like light mode. It also allows connecting a
 * SteganoFsAdapter to handle the mounting process.
 */
class MountFromPathDialog: public QDialog
{
Q_OBJECT

public:
    /**
     * \brief Constructs a MountFromPathDialog.
     * \param parent The parent widget.
     */
    explicit MountFromPathDialog(QWidget *parent = nullptr);

    /**
     * \brief Destructs the MountFromPathDialog.
     */
    ~MountFromPathDialog() override;

    /**
     * \brief Sets the mounting path.
     * \param newMountingPath The new mounting path.
     */
    void setMountingPath(const QString &newMountingPath);

    /**
     * \brief Returns the selected mounting path.
     * \return The selected mounting path.
     */
    [[nodiscard]] QString mountingPath() const;

    /**
     * \brief Checks if light mode is enabled.
     * \return True if light mode is enabled, false otherwise.
     */
    [[nodiscard]] bool lightmodeOn() const;

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
    void setFilesystemPath(const QString &newFilesystemPath);

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
    /**
     * \brief Slot called when the mounting path line edit text changes.
     * \param arg1 The new text.
     */
    void on_mountPathLineEdit_textChanged(const QString &arg1);

    /**
     * \brief Slot called when the filesystem path line edit text changes.
     * \param arg1 The new text.
     */
    void on_filesystemPathLineEdit_textChanged(const QString &arg1);

    /**
     * \brief Slot called when the browse directory button is clicked.
     */
    void on_browseDirButton_clicked();

    /**
     * \brief Slot called when the browse filesystem button is clicked.
     */
    void on_browseFsButton_clicked();

signals:
    /**
     * \brief Signal emitted when the mounting process is finished.
     */
    void finishedMounting();

private:
    Ui::MountFromPathDialog *ui; ///< The UI components.
    QString m_mountingPath;      ///< The selected mounting path.
    QString m_filesystemPath;    ///< The selected filesystem path.
    bool m_lightmodeOn{};          ///< Flag indicating light mode status.
    QFileDialog *m_mountDlg = nullptr; ///< Dialog for selecting mounting path.
    QFileDialog *m_fsDlg = nullptr;    ///< Dialog for selecting filesystem path.
    SteganoFsAdapter *m_adapter = nullptr; ///< Associated SteganoFsAdapter.
};

#endif // MOUNTFROMPATHDIALOG_H

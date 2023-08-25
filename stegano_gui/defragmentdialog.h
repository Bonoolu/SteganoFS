#ifndef DEFRAGMENTDIALOG_H
#define DEFRAGMENTDIALOG_H

#include <QDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"


namespace Ui
{
class DefragmentDialog;
}

/**
 * @brief The DefragmentDialog class represents a dialog for defragmentation settings.
 *
 * This class provides a dialog window to configure defragmentation settings for the application.
 */
class DefragmentDialog: public QDialog
{
Q_OBJECT

public:
    /**
     * @brief Constructs a DefragmentDialog object.
     * @param parent The parent widget.
     */
    explicit DefragmentDialog(QWidget *parent = nullptr);

    /**
     * @brief Destroys the DefragmentDialog object.
     */
    ~DefragmentDialog();

    /**
     * @brief Sets the light mode on/off.
     * @param newLightmodeOn Whether light mode should be turned on.
     */
    void setLightmodeOn(bool newLightmodeOn);

    /**
     * @brief Checks if light mode is on.
     * @return True if light mode is on, otherwise false.
     */
    bool lightmodeOn() const;

    /**
     * @brief Sets the fragmentation level.
     * @param f The new fragmentation level.
     */
    void setFragmentation(float f);

    /**
     * @brief Sets the adapter for the defragmentation dialog.
     * @param newAdapter The adapter to be set.
     */
    void setAdapter(SteganoFsAdapter *newAdapter);

private slots:
    /**
     * @brief Slot for the button click event.
     *
     * This slot is called when the push button is clicked in the dialog.
     */
    void on_pushButton_clicked();

private:
    Ui::DefragmentDialog *ui; ///< The UI components of the dialog.
    bool m_lightmodeOn{};      ///< Stores the current light mode status.
    SteganoFsAdapter *m_adapter{}; ///< Pointer to the adapter used by the dialog.
};

#endif // DEFRAGMENTDIALOG_H

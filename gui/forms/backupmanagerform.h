/*
 *  QCMA: Cross-platform content manager assistant for the PS Vita
 *
 *  Copyright (C) 2013  Codestation
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BACKUPMANAGERFORM_H
#define BACKUPMANAGERFORM_H

#include "database.h"
#include "backupitem.h"

#include <QMainWindow>

namespace Ui {
class BackupManagerForm;
}

class BackupManagerForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit BackupManagerForm(Database *db, QWidget *parent = 0);
    ~BackupManagerForm();

    Database *m_db;

private:
    void setupForm();
    void setBackupUsage(qint64 size);

    Ui::BackupManagerForm *ui;

public slots:
    void loadBackupListing(int index);
    void removeEntry(BackupItem *item);

private slots:
    void on_filterLineEdit_textChanged(const QString &arg1);
    void on_actionAboutQt_triggered();
    void on_actionAboutQcma_triggered();
    void on_actionQuit_triggered();
    void on_actionSettings_triggered();
    void on_actionRefreshDatabase_triggered();
    void saveListing();
};

#endif // BACKUPMANAGERFORM_H

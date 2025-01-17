/******************************************************************************\

    CAMotics is an Open-Source simulation and CAM software.
    Copyright (C) 2011-2015 Joseph Coffland <joseph@cauldrondevelopment.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

\******************************************************************************/

#ifndef CAMOTICS_FIND_DIALOG_H
#define CAMOTICS_FIND_DIALOG_H

#include <cbang/SmartPointer.h>

#include <QDialog>


namespace Ui {class FindDialog;}


namespace CAMotics {
  class FindDialog : public QDialog {
    Q_OBJECT;

    cb::SmartPointer<Ui::FindDialog> ui;

    bool wasReplace;

  public:
    FindDialog(bool replace);

    void findReplace(bool find, bool all);

  signals:
    void find(QString find, bool regex, int options);
    void replace(QString find, QString replace, bool regex, int options,
                 bool all);

  protected slots:
    void show();
    void find();
    void findResult(bool found);
    void replace();
    void replaceAll();
  };
}

#endif // CAMOTICS_FIND_DIALOG_H


/*
 * Copyright 2018 Matthieu Gallien <matthieu_gallien@yahoo.fr>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "elisaimportapplication.h"

#include <QCoreApplication>

ElisaImportApplication::ElisaImportApplication(QObject *parent) : QObject(parent)
{
}

void ElisaImportApplication::indexingChanged()
{
    static bool firstCall = true;

    if (firstCall) {
        firstCall = false;
    } else {
        QCoreApplication::quit();
    }
}


#include "moc_elisaimportapplication.cpp"

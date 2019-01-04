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

import QtQuick 2.10
import QtQuick.Controls 2.3
import org.kde.elisa 1.0

FocusScope {
    id: viewHeader

    property alias mainTitle: gridView.mainTitle
    property alias secondaryTitle: gridView.secondaryTitle
    property alias image: gridView.image
    property alias defaultIcon: gridView.defaultIcon
    property alias showRating: gridView.showRating
    property alias delegateDisplaySecondaryText: gridView.delegateDisplaySecondaryText
    property string genreFilterText
    property string artistFilter

    DataModel {
        id: realModel
    }

    AllAlbumsProxyModel {
        id: proxyModel

        sourceModel: realModel

        onEntriesToEnqueue: elisa.mediaPlayList.enqueue(newEntries, databaseIdType, enqueueMode, triggerPlay)
    }

    GridBrowserView {
        id: gridView

        focus: true

        anchors.fill: parent

        contentModel: proxyModel

        isSubPage: true

        onEnqueue: elisa.mediaPlayList.enqueue(databaseId, name, ElisaUtils.Album,
                                               ElisaUtils.AppendPlayList,
                                               ElisaUtils.DoNotTriggerPlay)

        onReplaceAndPlay: elisa.mediaPlayList.enqueue(databaseId, name, ElisaUtils.Album,
                                                      ElisaUtils.ReplacePlayList,
                                                      ElisaUtils.TriggerPlay)

        onOpen: viewManager.openOneAlbum(innerMainTitle, innerSecondaryTitle, innerImage, databaseId)

        onGoBack: viewManager.goBack()
    }

    Connections {
        target: elisa

        onMusicManagerChanged: {
            if (genreFilterText) {
                realModel.initializeByGenreAndArtist(elisa.musicManager, ElisaUtils.Album, genreFilterText, artistFilter)
            } else {
                realModel.initializeByArtist(elisa.musicManager, ElisaUtils.Album, artistFilter)
            }
        }
    }

    Component.onCompleted: {
        if (elisa.musicManager) {
            if (genreFilterText) {
                realModel.initializeByGenreAndArtist(elisa.musicManager, ElisaUtils.Album, genreFilterText, artistFilter)
            } else {
                realModel.initializeByArtist(elisa.musicManager, ElisaUtils.Album, artistFilter)
            }
        }
    }
}

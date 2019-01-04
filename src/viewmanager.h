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

#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "elisaLib_export.h"

#include "elisautils.h"

#include <QObject>
#include <QUrl>

class ELISALIB_EXPORT ViewManager : public QObject
{
    Q_OBJECT
public:

    enum ViewsType {
        NoViews,
        AllAlbums,
        OneAlbum,
        AllArtists,
        OneArtist,
        OneAlbumFromArtist,
        AllTracks,
        AllGenres,
        AllArtistsFromGenre,
        OneArtistFromGenre,
        OneAlbumFromArtistAndGenre,
        FrequentlyPlayedTracks,
        RecentlyPlayedTracks,
        FilesBrowser
    };

    Q_ENUM(ViewsType)

    explicit ViewManager(QObject *parent = nullptr);

Q_SIGNALS:

    void switchRecentlyPlayedTracksView(const QString &mainTitle, const QUrl &imageUrl,
                                        ElisaUtils::PlayListEntryType dataType);

    void switchFrequentlyPlayedTracksView(const QString &mainTitle, const QUrl &imageUrl, ElisaUtils::PlayListEntryType dataType);

    void switchAllAlbumsView(const QString &mainTitle, const QUrl &imageUrl,
                             ElisaUtils::PlayListEntryType dataType, const QUrl &viewDefaultIcon,
                             bool viewShowRating, bool viewDelegateDisplaySecondaryText);

    void switchOneAlbumView(const QString &mainTitle, const QUrl &imageUrl, const QString &secondaryTitle, qulonglong databaseId);

    void switchAllArtistsView(const QString &mainTitle, const QUrl &imageUrl,
                              ElisaUtils::PlayListEntryType dataType, const QUrl &viewDefaultIcon,
                              bool viewShowRating, bool viewDelegateDisplaySecondaryText);

    void switchOneArtistView(const QString &mainTitle, const QUrl &imageUrl, const QString &secondaryTitle, qulonglong databaseId);

    void switchAllTracksView(const QString &mainTitle, const QUrl &imageUrl, ElisaUtils::PlayListEntryType dataType);

    void switchAllGenresView(const QString &mainTitle, const QUrl &imageUrl,
                             ElisaUtils::PlayListEntryType dataType, const QUrl &viewDefaultIcon,
                             bool viewShowRating, bool viewDelegateDisplaySecondaryText);

    void switchAllArtistsFromGenreView(const QString &mainTitle, const QString &secondaryTitle,
                                       const QUrl &imageUrl, ElisaUtils::PlayListEntryType dataType,
                                       const QUrl &viewDefaultIcon, bool viewShowRating,
                                       bool viewDelegateDisplaySecondaryText);

    void switchOneArtistFromGenreView(const QString &mainTitle, const QString &secondaryTitle,
                                      const QUrl &imageUrl, ElisaUtils::PlayListEntryType dataType,
                                      const QUrl &viewDefaultIcon, bool viewShowRating,
                                      bool viewDelegateDisplaySecondaryText, qulonglong databaseId,
                                      const QString &genreName);

    void switchFilesBrowserView(const QString &mainTitle, const QUrl &imageUrl);

    void switchOffAllViews();

    void popOneView();

public Q_SLOTS:

    void closeAllViews();

    void openRecentlyPlayedTracks(const QString &mainTitle, const QUrl &imageUrl);

    void openFrequentlyPlayedTracks(const QString &mainTitle, const QUrl &imageUrl);

    void openAllAlbums(const QString &mainTitle, const QUrl &imageUrl);

    void openOneAlbum(const QString &albumTitle, const QString &albumAuthor,
                      const QUrl &albumCover, qulonglong albumDatabaseId);

    void openAllArtists(const QString &mainTitle, const QUrl &imageUrl);

    void openOneArtist(const QString &artistName, const QUrl &artistImageUrl, qulonglong artistDatabaseId);

    void openAllTracks(const QString &mainTitle, const QUrl &imageUrl);

    void openAllGenres(const QString &mainTitle, const QUrl &imageUrl);

    void openAllArtistsFromGenre(const QString &genreName);

    void openFilesBrowser(const QString &mainTitle, const QUrl &imageUrl);

    void recentlyPlayedTracksIsLoaded();

    void frequentlyPlayedTracksIsLoaded();

    void allAlbumsViewIsLoaded();

    void oneAlbumViewIsLoaded();

    void allArtistsViewIsLoaded();

    void oneArtistViewIsLoaded();

    void allTracksViewIsLoaded();

    void allGenresViewIsLoaded();

    void allArtistsFromGenreViewIsLoaded();

    void filesBrowserViewIsLoaded();

    void goBack();

private:

    ViewsType mCurrentView = ViewsType::NoViews;
    QString mCurrentAlbumTitle;
    QString mCurrentAlbumAuthor;
    QString mCurrentArtistName;
    QString mCurrentGenreName;

    ViewsType mTargetView = ViewsType::NoViews;
    QString mTargetAlbumTitle;
    QString mTargetAlbumAuthor;
    QString mTargetArtistName;
    QString mTargetGenreName;
    QUrl mTargetImageUrl;
    qulonglong mTargetDatabaseId = 0;

};

#endif // VIEWMANAGER_H

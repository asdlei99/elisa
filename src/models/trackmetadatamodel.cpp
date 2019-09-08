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

#include "trackmetadatamodel.h"

#include "musiclistenersmanager.h"

#include <KI18n/KLocalizedString>

#include <QtConcurrent>

TrackMetadataModel::TrackMetadataModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(&mLyricsValueWatcher, &QFutureWatcher<QString>::finished,
            this, &TrackMetadataModel::lyricsValueIsReady);
}

TrackMetadataModel::~TrackMetadataModel()
{
    if (mLyricsValueWatcher.isRunning() && !mLyricsValueWatcher.isFinished()) {
        mLyricsValueWatcher.waitForFinished();
    }
}

int TrackMetadataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return mTrackData.count();
}

QVariant TrackMetadataModel::data(const QModelIndex &index, int role) const
{
    auto result = QVariant{};

    const auto currentKey = mTrackKeys[index.row()];

    switch (role)
    {
    case Qt::DisplayRole:
        switch (currentKey)
        {
        case DatabaseInterface::TrackNumberRole:
        {
            auto trackNumber = mTrackData.trackNumber();
            if (trackNumber > 0) {
                result = trackNumber;
            }
            break;
        }
        case DatabaseInterface::DiscNumberRole:
        {
            auto discNumber = mTrackData.discNumber();
            if (discNumber > 0) {
                result = discNumber;
            }
            break;
        }
        case DatabaseInterface::ChannelsRole:
        {
            auto channels = mTrackData.channels();
            if (channels > 0) {
                result = channels;
            }
            break;
        }
        case DatabaseInterface::BitRateRole:
        {
            auto bitRate = mTrackData.bitRate();
            if (bitRate > 0) {
                result = bitRate;
            }
            break;
        }
        case DatabaseInterface::SampleRateRole:
        {
            auto sampleRate = mTrackData.sampleRate();
            if (sampleRate > 0) {
                result = sampleRate;
            }
            break;
        }
        default:
            result = mTrackData[currentKey];
            break;
        }
        break;
    case ItemNameRole:
        switch (currentKey)
        {
        case DatabaseInterface::TitleRole:
            result = i18nc("Track title for track metadata view", "Title");
            break;
        case DatabaseInterface::DurationRole:
            result = i18nc("Duration label for track metadata view", "Duration");
            break;
        case DatabaseInterface::ArtistRole:
            result = i18nc("Track artist for track metadata view", "Artist");
            break;
        case DatabaseInterface::AlbumRole:
            result = i18nc("Album name for track metadata view", "Album");
            break;
        case DatabaseInterface::AlbumArtistRole:
            result = i18nc("Album artist for track metadata view", "Album Artist");
            break;
        case DatabaseInterface::TrackNumberRole:
            result = i18nc("Track number for track metadata view", "Track Number");
            break;
        case DatabaseInterface::DiscNumberRole:
            result = i18nc("Disc number for track metadata view", "Disc Number");
            break;
        case DatabaseInterface::RatingRole:
            result = i18nc("Rating label for information panel", "Rating");
            break;
        case DatabaseInterface::GenreRole:
            result = i18nc("Genre label for track metadata view", "Genre");
            break;
        case DatabaseInterface::LyricistRole:
            result = i18nc("Lyricist label for track metadata view", "Lyricist");
            break;
        case DatabaseInterface::ComposerRole:
            result = i18nc("Composer name for track metadata view", "Composer");
            break;
        case DatabaseInterface::CommentRole:
            result = i18nc("Comment label for track metadata view", "Comment");
            break;
        case DatabaseInterface::YearRole:
            result = i18nc("Year label for track metadata view", "Year");
            break;
        case DatabaseInterface::ChannelsRole:
            result = i18nc("Channels label for track metadata view", "Channels");
            break;
        case DatabaseInterface::BitRateRole:
            result = i18nc("Bit rate label for track metadata view", "Bit Rate");
            break;
        case DatabaseInterface::SampleRateRole:
            result = i18nc("Sample Rate label for track metadata view", "Sample Rate");
            break;
        case DatabaseInterface::LastPlayDate:
            result = i18nc("Last play date label for track metadata view", "Last played");
            break;
        case DatabaseInterface::PlayCounter:
            result = i18nc("Play counter label for track metadata view", "Play count");
            break;
        case DatabaseInterface::LyricsRole:
            result = i18nc("Lyrics label for track metadata view", "Lyrics");
            break;
        case DatabaseInterface::ResourceRole:
            result = i18nc("Radio HTTP address for radio metadata view", "Stream Http Address");
            break;
        case DatabaseInterface::SecondaryTextRole:
        case DatabaseInterface::ImageUrlRole:
        case DatabaseInterface::ShadowForImageRole:
        case DatabaseInterface::ChildModelRole:
        case DatabaseInterface::StringDurationRole:
        case DatabaseInterface::MilliSecondsDurationRole:
        case DatabaseInterface::IsValidAlbumArtistRole:
        case DatabaseInterface::AllArtistsRole:
        case DatabaseInterface::HighestTrackRating:
        case DatabaseInterface::IdRole:
        case DatabaseInterface::DatabaseIdRole:
        case DatabaseInterface::IsSingleDiscAlbumRole:
        case DatabaseInterface::ContainerDataRole:
        case DatabaseInterface::IsPartialDataRole:
        case DatabaseInterface::AlbumIdRole:
        case DatabaseInterface::HasEmbeddedCover:
        case DatabaseInterface::FileModificationTime:
        case DatabaseInterface::FirstPlayDate:
        case DatabaseInterface::PlayFrequency:
        case DatabaseInterface::ElementTypeRole:
            break;
        }
        break;
    case ItemTypeRole:
        switch (currentKey)
        {
        case DatabaseInterface::TitleRole:
            result = TextEntry;
            break;
        case DatabaseInterface::ResourceRole:
            result = TextEntry;
            break;
        case DatabaseInterface::ArtistRole:
            result = TextEntry;
            break;
        case DatabaseInterface::AlbumRole:
            result = TextEntry;
            break;
        case DatabaseInterface::AlbumArtistRole:
            result = TextEntry;
            break;
        case DatabaseInterface::TrackNumberRole:
            result = IntegerEntry;
            break;
        case DatabaseInterface::DiscNumberRole:
            result = IntegerEntry;
            break;
        case DatabaseInterface::RatingRole:
            result = RatingEntry;
            break;
        case DatabaseInterface::GenreRole:
            result = TextEntry;
            break;
        case DatabaseInterface::LyricistRole:
            result = TextEntry;
            break;
        case DatabaseInterface::ComposerRole:
            result = TextEntry;
            break;
        case DatabaseInterface::CommentRole:
            result = TextEntry;
            break;
        case DatabaseInterface::YearRole:
            result = IntegerEntry;
            break;
        case DatabaseInterface::LastPlayDate:
            result = DateEntry;
            break;
        case DatabaseInterface::PlayCounter:
            result = IntegerEntry;
            break;
        case DatabaseInterface::LyricsRole:
            result = LongTextEntry;
            break;
        case DatabaseInterface::DurationRole:
        case DatabaseInterface::SampleRateRole:
        case DatabaseInterface::BitRateRole:
        case DatabaseInterface::ChannelsRole:
        case DatabaseInterface::SecondaryTextRole:
        case DatabaseInterface::ImageUrlRole:
        case DatabaseInterface::ShadowForImageRole:
        case DatabaseInterface::ChildModelRole:
        case DatabaseInterface::StringDurationRole:
        case DatabaseInterface::MilliSecondsDurationRole:
        case DatabaseInterface::IsValidAlbumArtistRole:
        case DatabaseInterface::AllArtistsRole:
        case DatabaseInterface::HighestTrackRating:
        case DatabaseInterface::IdRole:
        case DatabaseInterface::DatabaseIdRole:
        case DatabaseInterface::IsSingleDiscAlbumRole:
        case DatabaseInterface::ContainerDataRole:
        case DatabaseInterface::IsPartialDataRole:
        case DatabaseInterface::AlbumIdRole:
        case DatabaseInterface::HasEmbeddedCover:
        case DatabaseInterface::FileModificationTime:
        case DatabaseInterface::FirstPlayDate:
        case DatabaseInterface::PlayFrequency:
        case DatabaseInterface::ElementTypeRole:
            break;
        }
        break;
    }

    return result;
}

bool TrackMetadataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        mTrackData[mTrackKeys[index.row()]] = value;

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

QHash<int, QByteArray> TrackMetadataModel::roleNames() const
{
    auto names = QAbstractListModel::roleNames();

    names[ItemNameRole] = "name";
    names[ItemTypeRole] = "type";

    return names;
}

QString TrackMetadataModel::fileUrl() const
{
    return mFileUrl;
}

QUrl TrackMetadataModel::coverUrl() const
{
    if (mCoverImage.isEmpty()) {
        return QUrl(QStringLiteral("image://icon/media-optical-audio"));
    } else {
        return mCoverImage;
    }
}

MusicListenersManager *TrackMetadataModel::manager() const
{
    return mManager;
}

QString TrackMetadataModel::lyrics() const
{
    return mFullData[TrackDataType::key_type::LyricsRole].toString();
}

qulonglong TrackMetadataModel::databaseId() const
{
    return mDatabaseId;
}

void TrackMetadataModel::trackData(const TrackMetadataModel::TrackDataType &trackData)
{
    if (!mFullData.isEmpty() && trackData.databaseId() != mFullData.databaseId()) {
        return;
    }

    const QList<DatabaseInterface::ColumnsRoles> fieldsForTrack({DatabaseInterface::TitleRole, DatabaseInterface::ArtistRole,
                                                                 DatabaseInterface::AlbumRole, DatabaseInterface::AlbumArtistRole,
                                                                 DatabaseInterface::TrackNumberRole, DatabaseInterface::DiscNumberRole,
                                                                 DatabaseInterface::RatingRole, DatabaseInterface::GenreRole,
                                                                 DatabaseInterface::LyricistRole, DatabaseInterface::ComposerRole,
                                                                 DatabaseInterface::CommentRole, DatabaseInterface::YearRole,
                                                                 DatabaseInterface::LastPlayDate, DatabaseInterface::PlayCounter,
                                                                 DatabaseInterface::DatabaseIdRole});

    fillDataFromTrackData(trackData, fieldsForTrack);
}

void TrackMetadataModel::fillDataFromTrackData(const TrackMetadataModel::TrackDataType &trackData,
                                               const QList<DatabaseInterface::ColumnsRoles> &fieldsForTrack)
{
    beginResetModel();
    mFullData = trackData;
    mTrackData.clear();
    mTrackKeys.clear();

    for (DatabaseInterface::ColumnsRoles role : fieldsForTrack) {
        if (trackData.constFind(role) != trackData.constEnd()) {
            if (role == DatabaseInterface::RatingRole) {
                if (trackData[role].toInt() == 0) {
                    continue;
                }
            }

            mTrackKeys.push_back(role);
            mTrackData[role] = trackData[role];
        }
    }
    filterDataFromTrackData();
    endResetModel();

    fetchLyrics();

    mDatabaseId = trackData[DatabaseInterface::DatabaseIdRole].toULongLong();
    Q_EMIT databaseIdChanged();

    mCoverImage = trackData[DatabaseInterface::ImageUrlRole].toUrl();
    Q_EMIT coverUrlChanged();

    auto rawFileUrl = trackData[DatabaseInterface::ResourceRole].toUrl();

    if (rawFileUrl.isLocalFile()) {
        mFileUrl = rawFileUrl.toLocalFile();
    } else {
        mFileUrl = rawFileUrl.toString();
    }
    Q_EMIT fileUrlChanged();
}

void TrackMetadataModel::filterDataFromTrackData()
{
}

void TrackMetadataModel::removeMetaData(DatabaseInterface::ColumnsRoles metaData)
{
    auto itMetaData = std::find(mTrackKeys.begin(), mTrackKeys.end(), metaData);
    if (itMetaData == mTrackKeys.end()) {
        return;
    }

    mTrackKeys.erase(itMetaData);
    mTrackData.remove(metaData);
}

TrackMetadataModel::TrackDataType::mapped_type TrackMetadataModel::dataFromType(TrackDataType::key_type metaData) const
{
    return mFullData[metaData];
}

void TrackMetadataModel::fillLyricsDataFromTrack()
{
    beginInsertRows({}, mTrackData.size(), mTrackData.size());
    mTrackKeys.push_back(DatabaseInterface::LyricsRole);
    mTrackData[DatabaseInterface::LyricsRole] = mLyricsValueWatcher.result();
    endInsertRows();
}

void TrackMetadataModel::lyricsValueIsReady()
{
    if (!mLyricsValueWatcher.result().isEmpty()) {
        fillLyricsDataFromTrack();

        mFullData[DatabaseInterface::LyricsRole] = mLyricsValueWatcher.result();

        Q_EMIT lyricsChanged();
    }
}

void TrackMetadataModel::initializeById(ElisaUtils::PlayListEntryType type, qulonglong databaseId)
{
    mFullData.clear();
    mTrackData.clear();
    mCoverImage.clear();
    mFileUrl.clear();

    Q_EMIT lyricsChanged();

    Q_EMIT needDataByDatabaseId(type, databaseId);
}

void TrackMetadataModel::initialize(MusicListenersManager *newManager, DatabaseInterface *trackDatabase)
{
    mManager = newManager;
    Q_EMIT managerChanged();

    if (mManager) {
        mDataLoader.setDatabase(mManager->viewDatabase());
    } else if (trackDatabase) {
        mDataLoader.setDatabase(trackDatabase);
    }

    if (mManager) {
        mManager->connectModel(&mDataLoader);
    }

    connect(this, &TrackMetadataModel::needDataByDatabaseId,
            &mDataLoader, &ModelDataLoader::loadDataByDatabaseId);
    connect(this, &TrackMetadataModel::needDataByFileName,
            &mDataLoader, &ModelDataLoader::loadDataByFileName);
    connect(this, &TrackMetadataModel::saveRadioData,
            &mDataLoader, &ModelDataLoader::saveRadioModified);
    connect(this, &TrackMetadataModel::deleteRadioData,
            &mDataLoader, &ModelDataLoader::removeRadio);
    connect(&mDataLoader, &ModelDataLoader::trackModified,
            this, &TrackMetadataModel::trackData);
    connect(&mDataLoader, &ModelDataLoader::allTrackData,
            this, &TrackMetadataModel::trackData);
    connect(&mDataLoader, &ModelDataLoader::allRadioData,
            this, &TrackMetadataModel::radioData);
    connect(&mDataLoader, &ModelDataLoader::radioAdded,
            this, &TrackMetadataModel::radioData);
    connect(&mDataLoader, &ModelDataLoader::radioModified,
            this, &TrackMetadataModel::radioData);
}

void TrackMetadataModel::fetchLyrics()
{
    auto lyricicsValue = QtConcurrent::run(QThreadPool::globalInstance(), [=]() {
        auto trackData = mFileScanner.scanOneFile(mFullData[DatabaseInterface::ResourceRole].toUrl(), mMimeDatabase);
        if (!trackData.lyrics().isEmpty()) {
            return trackData.lyrics();
        }
        return QString{};
    });

    mLyricsValueWatcher.setFuture(lyricicsValue);
}

void TrackMetadataModel::initializeForNewRadio()
{
    mFullData.clear();
    mTrackData.clear();

    fillDataForNewRadio();
}

void TrackMetadataModel::fillDataForNewRadio()
{
    beginResetModel();
    mTrackData.clear();
    mTrackKeys.clear();

    for (auto role : {
         DatabaseInterface::TitleRole,
         DatabaseInterface::ResourceRole,
         DatabaseInterface::CommentRole,
         DatabaseInterface::DatabaseIdRole

}) {
        mTrackKeys.push_back(role);
        if (role == DatabaseInterface::DatabaseIdRole) {
            mTrackData[role] = -1;
        } else {
            mTrackData[role] = QString();
        }

    }
    filterDataFromTrackData();
    endResetModel();
}

void TrackMetadataModel::initializeByTrackFileName(const QString &fileName)
{
    mFullData.clear();
    mTrackData.clear();
    mCoverImage.clear();
    mFileUrl.clear();

    Q_EMIT lyricsChanged();

    Q_EMIT needDataByFileName(ElisaUtils::FileName, QUrl::fromLocalFile(fileName));
}

void TrackMetadataModel::setManager(MusicListenersManager *newManager)
{
    initialize(newManager, nullptr);
}

void TrackMetadataModel::setDatabase(DatabaseInterface *trackDatabase)
{
    initialize(nullptr, trackDatabase);
}

void TrackMetadataModel::saveData()
{
    Q_EMIT saveRadioData(mTrackData);
}

void TrackMetadataModel::deleteRadio()
{
    if (mTrackData[DatabaseInterface::DatabaseIdRole]>=0) {
        Q_EMIT deleteRadioData(mTrackData[DatabaseInterface::DatabaseIdRole].toULongLong());
    }
}

void TrackMetadataModel::radioData(const TrackDataType &radiosData)
{
    if (!mFullData.isEmpty() && mFullData[DatabaseInterface::DatabaseIdRole].toInt() != -1 &&
            mFullData.databaseId() != radiosData.databaseId()) {
        return;
    }

    const QList<DatabaseInterface::ColumnsRoles> fieldsForTrack({DatabaseInterface::TitleRole, DatabaseInterface::ResourceRole,
                                                                 DatabaseInterface::CommentRole, DatabaseInterface::DatabaseIdRole});

    fillDataFromTrackData(radiosData, fieldsForTrack);
}

#include "moc_trackmetadatamodel.cpp"

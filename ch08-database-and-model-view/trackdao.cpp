#include "trackdao.h"

#include <QtSql>

using namespace std;

TrackDao::TrackDao(QSqlDatabase& database)
    :mDatabase(database)
{

}

unique_ptr<vector<unique_ptr<Track>>> TrackDao::tracks() const
{
    QSqlQuery query(
                "SELECT tracks.TrackId AS id, tracks.Name AS name, "
                "albums.Title AS album, artists.Name AS artist "
                "FROM tracks "
                "JOIN albums ON tracks.AlbumId = albums.AlbumId "
                "JOIN artists ON albums.ArtistId = artists.ArtistId",
                mDatabase);
    unique_ptr<vector<unique_ptr<Track>>> list(new vector<unique_ptr<Track>>());

    if (!query.exec())
    {
        qDebug() << "query error: " << query.lastError();
    } else {
        while(query.next()) {
            unique_ptr<Track> track(new Track());
            track->setId(query.value("id").toInt());
            track->setName(query.value("name").toString());
            track->setAlbum(query.value("album").toString());
            track->setArtist(query.value("artist").toString());
            list->push_back(move(track));
        }
    }
    return list;
}

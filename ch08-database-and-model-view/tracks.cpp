#include "track.h"

Track::Track(int32_t id, QString const &name,
       QString const &album, QString const &artist)
    :mId(id)
    ,mName(name)
    ,mAlbum(album)
    ,mArtist(artist)
{

}

int32_t Track::id() const
{
    return mId;
}

void Track::setId(int32_t id)
{
    if (this->id() != id) mId = id;
}

QString Track::name() const
{
    return mName;
}

void Track::setName(QString const &v)
{
    if (name() != v) mName = v;
}

QString Track::album() const
{
    return mAlbum;
}

void Track::setAlbum(QString const &v)
{
    if (album() != v) mAlbum = v;
}

QString Track::artist() const
{
    return mArtist;
}

void Track::setArtist(QString const &v)
{
    if (artist() != v) mArtist = v;
}

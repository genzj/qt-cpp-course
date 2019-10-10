#ifndef TRACKS_H
#define TRACKS_H

#include <cinttypes>

#include <QString>

class Track
{
public:
    Track(int32_t id=0, QString const &name="",
           QString const &album="", QString const &artist="");

    int32_t id() const;
    void setId(int32_t id);
    QString name() const;
    void setName(QString const &v);
    QString album() const;
    void setAlbum(QString const &v);
    QString artist() const;
    void setArtist(QString const &v);

private:
    int32_t mId;
    QString mName;
    QString mAlbum;
    QString mArtist;
};

#endif // TRACKS_H

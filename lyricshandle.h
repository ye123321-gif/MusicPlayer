#ifndef LYRICSHANDLE_H
#define LYRICSHANDLE_H
#include <QString>
#include <string.h>
#include <vector>
#define LRC_LENGTH 256
using namespace std;
struct LrcText{
    int time;
    char lyric[LRC_LENGTH];
};

class LyricsHandle
{
public:
    LyricsHandle();
    QString getArtist() const;
    QString getTitle() const;
    QString getAlbum() const;
    void getLrcText(vector<LrcText *> &lyricContainer);
    void setLrcFileName(const char *LrcFileName);
    void clearLyricContainer(vector<LrcText *> &LyricsContainer);

private:
    char LrcFileName[LRC_LENGTH];
    char artist[128];
    char title[128];
    char album[128];
};

#endif // LYRICSHANDLE_H

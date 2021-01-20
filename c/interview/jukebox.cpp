/* musical jukebox design */

/* steps:
    1. understanding the requairments.
    2. defining the core objects.
    3. relations between objects.
    4. methods.

    a digital jukebox:

    objects:
        - song
        - artist
        - album (CD)
        - music player (jukebox)
        - collection (playlist)

יחסים בין הקלאסים:
בהתחלה מייצרים jukeboxריק 
וטוענים באלבומים

ניתן ליצור פלייליסט מתוך רשימת האלבומים הקיימים
כל אלבום מכיל  רשימה של כל השירים שבתוכו ואת שם האומן

כל שיר מכיל את אורכו ואת האומן.

פעולות על הJOKEBOX

-ניגון
-הכנסת אלבום
-יצירת פלייליסט
-הסרת אלבום
-הפסקת ניגון
-השהייה
-מעבר שיר
 */

#include <vector>

class CD;
class Song;
class Artist;
class Playlist;



class Jukebox
{
public:
    explicit Jukebox();
    void AddCD(CD album);
    void CreatePL();
    void Play();
    void Pause();
    void RemoveCD(CD album);
    void PlaySong(Song song);
    void SortPL();
    void ShufflePL();

private:
    std::vector<CD> cds;
    Playlist playlist;
};

class CD
{
private:
    std::vector<Song> songs;
    Artist artist;
public:
    CD(/* args */) {}
    ~CD() {}
};

class Song
{
private:
    size_t length;
    Artist artist;
public:
    Song(/* args */) {}
    ~Song() {}
};

class Playlist
{
private:
    std::vector<Song> m_pl;
public:
    Playlist(/* args */) {}
    ~Playlist() {}
    void Play();
};

class Artist;
{
private:
    char *name;
public:
    Artist;(/* args */) {}
    ~Artist;() {}
};
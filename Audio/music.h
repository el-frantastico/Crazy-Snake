#include "Speaker.h"
#include "PinDetect.h"

class Music
{
public:
    void playMainMusic(Speaker &speaker, int &note);
    void playChew(Speaker &speaker);
    void playDeath(Speaker &speaker);
    void playGameOver(Speaker &speaker, int &note);
    void playLoser(Speaker &speaker, int &note);
};
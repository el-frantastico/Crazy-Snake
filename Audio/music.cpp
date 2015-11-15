#include "music.h"

void Music::playMainMusic(Speaker &speaker, int &note)
{
       switch (note)
    {
        case 1:
        {
            speaker.PlayNote(146.83, 0.2, 0.1); //d3
            break;
        }
        case 2:
        {
            speaker.PlayNote(155.56, 0.2, 0.1); //d3#
            break;
        }
        case 3:
        {
            speaker.PlayNote(146.83, 0.2, 0.1); //d3
            break;
        }
        case 4:
        {
            speaker.PlayNote(392.00, 0.4, 0.1); //g4
            break;
        }
        case 5:
        {
            speaker.PlayNote(392.00, 0.4, 0.1); //g4
            break;
        }
        case 6:
        {
            speaker.PlayNote(440.00, 0.4, 0.1); //a4
            break;
        }
        case 7:
        {
            speaker.PlayNote(440.00, 0.4, 0.1); //a4
            break;
        }
        case 8:
        {
            speaker.PlayNote(587.33, 0.4, 0.1); //d4
            break;
        }
        case 9:
        {
            speaker.PlayNote(493.88, 0.2, 0.1); //b4
            break;
        }
        case 10:
        {
            speaker.PlayNote(392.00, 0.2, 0.1); //g4
            break;
        }
    }
}

void Music::playChew(Speaker &speaker)
{
    speaker.PlayNote(400.0,0.01,0.1);
}

void Music::playDeath(Speaker &speaker)
{
    speaker.PlayNote(600.0,0.1,0.1);
    speaker.PlayNote(400.0,0.1,0.1);
    speaker.PlayNote(200.0,0.1,0.1);
}

void Music::playGameOver(Speaker &speaker, int &note)
{
    switch (note)
    {
        case 1:
        {
            speaker.PlayNote(440.00, 0.8, 0.1); //A4
            break;
        }
        case 2:
        {
            speaker.PlayNote(261.63, 0.1, 0.1); //C4
            break;
        }
        case 3:
        {
            speaker.PlayNote(329.63, 0.1, 0.1); //E4
            break;
        }
        case 4:
        {
            speaker.PlayNote(440.00, 0.1, 0.1); //A4
            break;
        }
        case 5:
        {
            speaker.PlayNote(493.88, 0.8, 0.1); //B4
            break;
        }
        case 6:
        {
            speaker.PlayNote(293.66, 0.1, 0.1); //D4
            break;
        }
        case 7:
        {
            speaker.PlayNote(392.00, 0.1, 0.1); //G4
            break;
        }
        case 8:
        {
            speaker.PlayNote(493.88, 0.1, 0.1); //B4
            break;
        }
        case 9:
        {
            speaker.PlayNote(523.25, 0.8, 0.1); //C5
            break;
        }
    }
}

void Music::playLoser(Speaker &speaker, int &note)
{
    switch (note)
    {
        case 1:
        {
            speaker.PlayNote(293.66, 0.4, 0.1); //d4
            break;
        }
        case 2:
        {
            speaker.PlayNote(277.18, 0.4, 0.1); //d4b
            break;
        }
        case 3:
        {
            speaker.PlayNote(261.63, 0.4, 0.1); //c4
            break;
        }
        case 4:
        {
            speaker.PlayNote(246.94, 0.8, 0.1); //b3
            break;
        }
    }
}
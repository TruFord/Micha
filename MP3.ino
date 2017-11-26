//https://learn.sparkfun.com/tutorials/mp3-trigger-hookup-guide-v24?_ga=2.268910072.841687636.1511654866-1487735170.1506791444


#BAUD 38400
#RAND 2
#TRIG 01, 0, 0
#TRIG 02, 0, 0
#TRIG 03, 0, 0
#TRIG 04, 0, 0
#TRIG 05, 0, 0
#TRIG 06, 0, 0
#TRIG 07, 0, 0
#TRIG 08, 0, 0
#TRIG 09, 0, 0
#TRIG 10, 0, 0
#TRIG 11, 0, 0
#TRIG 12, 0, 0
#TRIG 13, 0, 0
#TRIG 14, 0, 0
#TRIG 15, 0, 0
#TRIG 16, 0, 0
#TRIG 17, 0, 0
#TRIG 18, 0, 0
******************** ALL INIT COMMANDS ABOVE THIS LINE *********************
This is a sample init file for the MP3 Trigger v2, firmware version 2.40.

The init file is optional. If not present, the default parameters will be
in effect: 38.4Kbaud, and all triggers will start their corresponding
tracks with restart lockout disabled. If it is present, it must be named
MP3TRIGR.INI and be located in the root directory.

Only the first 512 bytes of the file are examined for commands, and the first
occurrence of the '*' character is treated as the end of file by the parser.
Comments are not allowed in the command section, but there is no restriction
on the length of the comments that follow the first '*'.

All commands must begin with the '#' character and be followed by a space,
then the command parameters separated by commas. White space is ignored. All
parameters are decimal numbers. Leading zeros are acceptable. See the above
examples - which are redundant since they are all default values.

The following commands are supported in firmware version 2.40:

#BAUD N

    where N is one of the following: 2400, 9600, 19200, 31250 or 38400

#RAND N

    where N is from 1 to 255

    The default behavior of the random trigger function is to play a random 
    track from all the MP3 files on the flash card. The #RAND function will
    exclude the first N tracks (in the directory) from the random trigger
    function. So if there are 18 MP3 files on the card and N=4, then the
    first 4 MP3 files will be excluded from the random trigger function.

#TRIG N, F, L

    where: N is the trigger number (1-18)
    F is the trigger function type (see below)
    L is the restart lockout enable

    The defined trigger function types (F) are as follows:

    F = 0: Normal operation
    F = 1: Next (same as the forward Nav switch)
    F = 2: Random
    F = 3: Previous (same as the back Nav switch)
    F = 4: Start (restarts the current track)
    F = 5: Stop
    F = 6: Volume Up
    F = 7: Volume Down

    The restart lockout feature, if enabled, will prevent that trigger
    from working if audio is currently playing. Use this if you want
    to prevent restarts before the track has reached the end. This
    feature does not apply to function types 5-7.

    L = 0: Restart lockout disabled (default)
    L = 1: Restart lockout enabled

You only need to include entries for triggers that are to be non-default.
As an example, I use the following single-line init file to make trigger
18 be a "Next" function, then hard-wire the trigger so that my MP3 Trigger
powers up and loops continuously through all the tracks on the card.

#TRIG 18, 1, 0


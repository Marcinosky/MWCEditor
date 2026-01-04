## MWCEditor

> MWCeditor - a save editor by durkhaz 		updated by Marcinoski

> For the (cool) game "My Winter Car"			by Amistech Games


# Disclaimer - WIP
The project is still under development, i released it with most of functionalities restored, but some things can still be broken, texts are outdated and some important warnings are probably missing, use on your own risk.

on my radar:
- valve lash value and some new part conditions are missing from the report, can be changed manually
- wiring is not handled at all, will do this later as i dont want to spoil the build for myself, sorry
- old texts that need updating, some additional warnings
- time values from weather and time combo are off, weather doesn't work
- spawning items not tested, item tables in the ini not updated for the new game and i would appreciate if anyone took a crack at them


## FAQ

**Q: What does it do?**

Its a fork of [MSCeditor](https://github.com/durkhaz/MSCEditor), updated to work with the new game



**Q: Does everything work?**

Most of the things work, but i can't guarantee what the results will be. The application is stable but not all functionalities are updated to fit the new data.



**Q: What works?**

- Most things, save files can be opened and their contents inspected. 
- Satsuma report was changed to Rivett report and shows appropriate parts. 
- An aliasing system was implemented to translate insave part names (VINXXX) into actual in game names
- Teleport waypoint table was updated to be more useful for the new game.
- Timetable was updated to represent the new game
- Keys can be changed throught the key manager, or through their entries directly



**Q: Whats missing?**

- The map is disabled entirely untill i get my hands on a high quality picture of the new map, or at least get the old one from the author
- Some item properties are still not defined for the new game, behavior of automatic item teleport may vary
- Maintenance tab recommended values may not actually be the best, we need people to come up with meta values
- Valve lash and some other values are missing from the report, they're my priority
- Aliases for all the parts are needed, they aren't saved untill bought in-game



**Q: Can i help?**

If you understand what some values mean or have a good value for a recommended setting then please let me know



**Q: Where do I find my saves?**

AppData\\LocalLow\\Amistech\\My Winter Car. The tool should open the correct folder on first launch though.



## Tested

* `savefile.txt` file contains the majority of world and player data
* `player` entries can be modified to change cash, bank account and stats (PlayerThirst=Problem in game)
* `worldtime` entry can be changed to any hour (0-23)
* weather modification is broken currently
* teleportation works, updated waypoints
* existing key management works, but not all keys are stored in the save file
* gifu key is not visible in the save, but gifuavailable exists
* map doesn't work, disabled untill i get in contact with the original dev
* updated the timetable, old entries im not sure about tagged with (?)
* `carparts.txt` file contains majority of car data
* Rivett report works, bolt tightness can be inspected
* Fixing bolts, parts, mesh, all works, stuck item validation not verified
* maintenance tab lacks some entries like valve lash, new parts that can wear down
* wiring not updated at all

# MWCEditor

> MWCeditor - a save editor by durkhaz 		updated by Marcinoski

> For the (cool) game "My Winter Car"			by Amistech Games



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
- Maintenance tab in the report is empty, need to update part names and get updated sweetspot documentation
- Aliases for all the parts are needed, they aren't saved untill bought in-game



**Q: Can i help?**

Yes please, if you're progressed further into the game and have the rivett all built and various items in different states then i would love to get my hands on a dump extracted by the [Dev cconsole](https://www.nexusmods.com/mywintercar/mods/57)



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
* Damaged, Bolted statuses from old game are not present here but logic leftover for now
* Fixing bolts/stuck parts and their detection not tested, report issues if found
* maintenance tab needs definitions updated to new parts
* not all part names are aliased currently (show up as vinXXX instead of a part name)
* aliases, definitions will be updated once i progress further in the game
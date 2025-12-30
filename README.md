# MWCEditor

MWCeditor - a save editor by durkhaz 		updated by Marcinoski
For the (cool) game "My Winter Car"			by Amistech Games



**Q: What does it do?**

Its a fork of [MSCeditor](https://github.com/durkhaz/MSCEditor), updated to work with the new game



**Q: Does everything work?**

No, while the original editor works natively with MWC save files, some features are broken while others crash outright



**Q: So what is this?**

Im currently focused on refactoring the app to fit the new game and hiding all the broken features.



**Q: Are you planning to fix them?**

I want to recreate all original functionality for the new game, first focus is player, time and weather management



**Q: Where do I find my saves?**

AppData\\LocalLow\\Amistech\\My Winter Car. The tool should open the correct folder on first launch though.



## Tested

* `savefile.txt` file contains the majority of world and player data
* `player` entries can be modified to change cash, bank account and stats (PlayerThirst=Problem in game)
* `worldtime` entry can be changed to any hour (0-23)
* `worldday` works, but i don't recommend skipping time this way
* teleportation works, but only to old waypoints
* key management doesn't work, will test once i get deeper in the game
* map doesn't work, disabled untill i get my hands on an updated image
* Satsuma report works but i need to update part ids, so its empty for now
# UE4-SimpleConfig
simple config file writer/reader which can be used in Blueprints

supports bool, int, float and string values

config files are stored in the projects config directory

usage: add a loadConfig node to your BP and enter the name of the configfile which returns a config object that allows to read/write values (get sure add and execute a saveConfig node on the object after writing data to it)


### (!) Project API Name in Header File has to be changed to fit your Project

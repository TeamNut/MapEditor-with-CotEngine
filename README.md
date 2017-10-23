# MapEditor-with-CotEngine
This is a MapEditor made with CotEngine. It can make 2D roll playing games` maps and output to a file that included map information with .xml exterior. 
***
## Caution
### When do you wanna change resolution
Open **HeadValue.h** file and modify following values.
* RESOLUTION_X
* RESOLUTION_Y

### When do you wanna place more blocks
Modify following values in above file.
* MAX_OBJECT

Also you can change gap of grid to grid placing delicacy. But you have to remember: It tool's object batch method uses *object pooling*. So the MAX_OBJECT grow bigger, become load grow bigger.

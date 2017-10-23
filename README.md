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

## How to use
### About place
You can place block to **drag from bottom item view**. If you mistake placing, you can remove to **press mouse rbutton**. And also you can place more faster to **press E button**. It can place block that you used last time.

Items(tiles) in item view can look around to press button: **comma, period**.

### About camera move
Press button: W, A, S, D to move camera position. You can make map more bigger.

### About data save and data load
**Press F5 button** to save. If you press it button, you can see a comment about save in console window. Save data will create on MapEditor folder.

**Press F7 button** to load. You can also see a comment about load in console window. MapEditor can find data file in MapEditor folder.
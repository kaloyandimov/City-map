# City Map :round_pushpin:
Write a program that represents a city map. 
## Basic Functionality
The map information is contained in a text file. In the first place on each line stands the name of an intersection, followed by pairs of names of other intersections and the length of the street from the first intersection to the second. 

For example:  
**`Македония`** `5Кьошета 600` `Руски 450`  
**`5Кьошета`** `Македония 600` `Руски 400`  
**`Руски`** `Македония 450` `5Кьошета 400`  

For this program write a function that:
- Checks if there is a road between two intersections. :vertical_traffic_light:
- Checks if it is possible to get from one intersection to all the others.  :ok_hand:
- Checks if we can do a full tour of all streets without visting any street twice. :100:
- Checks if it is possible to go around some part of the city from an intersection and return to it. :arrows_counterclockwise:
- Finds all culs-de-sac. :warning: 
- Finds the three shortest paths between two intersections. :hourglass_flowing_sand:
- Finds the three alternative shortest paths between two intersections if some are closed. :construction:

Note: It is possible to have one-way streets or that the street from *A* to *B* has a different length than the street from *B* to *A*. However, it is not possible to have two different streets from *A* to *B*.

## Bonus Functionality
Write an interactive mode of the program. 

This specific mode gives access to the following commands:
| Name | Params | Usage |
|-|-|-|
| location | --- | display current position (intersection) |
| neighbours | --- | display all adjacent intersections |
| change | @ | change current position to @ |
| move | @ | change current position to @ and output the path |
| close | @ | add @ to the list of closed intersections |
| open | @ | remove @ from the list of closed intersections |
| closed | --- | display all closed intersections |
| tour | --- | display a city tour |

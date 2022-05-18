# City Map :round_pushpin:
A computer program that represents a city map as a weighted directed graph where the nodes are intersections and the edges are streets.

## Table of Contents
- [Map Data](#map-data)
- [Implemented Functions](#implemented-functions)
- [Interactive Mode](#interactive-mode)

## Map Data
The map data is contained in a text file. In the first place on each line is written the name of an intersection, followed by pairs of the distance to an adjacent intersection and its name.

For example:  
**`A`** `3 B` `2 F`  
**`B`** `2 C` `4 E`  
**`C`** `3 D`  
**`D`** `6 A` `5 B`  
**`E`** `3 D`  
**`F`** `2 E`  

## Implemented Functions
Function that checks whether it is possible to:
- get from one intersection to another; :walking:
- get from one intersection to all the others; :vertical_traffic_light:
- do a full tour of all streets without visiting any street twice; :100:
- go around some part of the city from an intersection and return to it. :arrows_counterclockwise:  

Function that finds:
- all deadends; :warning: 
- the three shortest paths between two intersections; :hourglass_flowing_sand:
- the three alternative shortest paths between two intersections if some are closed. :construction:

Note: *It is possible to have one-way streets or that the street from **A** to **B** has a different length than the street from **B** to **A**. However, it is not possible to have two different streets from **A** to **B**.*

## Interactive Mode
The interactive mode gives access to the following commands:
| Name | Params | Usage |
|-|-|-|
| location | --- | print current position |
| neighbours | --- | print all adjacent intersections |
| change | @ | change current position to @ |
| move | @ | change current position to @ and print the path |
| close | @ | add @ to the list of closed intersections |
| open | @ | remove @ from the list of closed intersections |
| closed | --- | print all closed intersections |
| tour | --- | print a city tour |
| help | --- | print this list |
| exit | --- | exit the program |

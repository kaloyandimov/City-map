# City Map :round_pushpin:

This application allows users to create and interact with a city map. It represents a city's map as a weighted directed graph, with intersections as nodes and streets as edges. The app offers a range of functionalities to help you navigate, analyze, and uncover various aspects of the city.

## Table of Contents

- [Key Features](#key-features)
- [Map Data Format](#map-data-format)
- [Supported Commands](#supported-commands)
- [Contributing](#contributing)
- [License](#license)

## Key Features

The application provides the following main functions to analyze and explore the city map:

### Checking Connectivity

- Check if it is possible to travel from one intersection to another.
- Check if it is possible to reach all intersections from a given starting intersection.

### Traversal and Shortest Paths

- Find all deadends in the city map.
- Find the shortest path between two intersections.
- Find the three shortest paths between two intersections.
- Find the three alternative shortest paths between two intersections if some intersections are closed.
- Find the Eulerian tour, which represents the path that traverses all streets exactly once.

## Map Data Format

The map data is contained in a text file. Each line represents an intersection and its adjacent streets. The format is
as follows:

```
<intersection> <distance> <adjacent_intersection> <distance> <adjacent_intersection> ...
```

### For Example:

**`A`** `3 B` `2 F`  
**`B`** `2 C` `4 E`  
**`C`** `3 D`  
**`D`** `6 A` `5 B`  
**`E`** `3 D`  
**`F`** `2 E`

## Supported Commands

The interactive mode gives access to the following commands:

| Name       | Params | Usage                                                                        |
|------------|--------|------------------------------------------------------------------------------|
| location   | —      | Print the current position                                                   |
| neighbours | —      | Print all adjacent intersections                                             |
| change     | @      | Change the current position to the specified intersection                    |
| move       | @      | Change the current position and print the path to the specified intersection |
| close      | @      | Add an intersection to the list of closed intersections                      |
| open       | @      | Remove an intersection from the list of closed intersections                 |
| closed     | —      | Print all closed intersections                                               |
| tour       | —      | Plan a city tour using an Eulerian trail                                     |
| help       | —      | Print the list of available commands                                         |
| exit       | —      | Exit the program                                                             |

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, feel free to submit a pull
request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

# FdF – 3D Wireframe Landscape Renderer

**FdF** (short for *Fil de Fer*, French for "wireframe") is a graphics project developed as part of the 42 School curriculum. It reads a `.fdf` file containing elevation data and renders a 3D wireframe model of the landscape using ![isometric projection](https://en.wikipedia.org/wiki/Isometric_projection).

## 🖼️ Project Overview

The program parses a grid of height values from a `.fdf` file and visualizes it as a 3D wireframe model. Each point's elevation influences its position in the 3D space, creating a relief map.

## 🚀 Features

- Isometric projection rendering  
- perspective projection rendering  
- Dynamic zoom and pan controls  
- Elevation scaling  
- Color gradients based on elevation  
- Keyboard controls for interaction  

## 🛠️ Installation

### Prerequisites

- A Unix-like operating system (Linux or macOS)
- `gcc` compiler
- `make` utility (if you are welling to compile using the Makefile)
- MiniLibX library

### Building the Project

```bash
git clone https://github.com/ErabaReta/fdf.git
cd fdf
make
```
## 📈 Usage

Run the program with a .fdf file as an argument:
```bash
./fdf path/to/map.fdf
```
Sample maps are available in the test_maps/ directory.

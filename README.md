# Barcode Generator

> **INFO0030 — Projet de Programmation · University of Liège**
> Second individual project — C language

---

## Overview

A C application that **generates barcodes** and exports them as PNM images (PBM/PGM/PPM).
The project builds on the PNM library from the first project and introduces **unit testing** with the Seatest framework, as well as full **Doxygen** documentation.

---

## Project Structure

```
info0030_secondProject_BarCode_Gen/
├── codebarre.c        # Barcode encoding & generation logic
├── codebarre.h        # Barcode API declarations
├── pnm.c              # PNM image library (reused from project 1)
├── pnm.h              # PNM API
├── main.c             # Main entry point
├── main-codebarre.c   # Barcode demo/testing
├── main-pnm.c         # PNM format demo/testing
├── codebarre_test.c   # Unit tests — barcode module
├── pnm_test.c         # Unit tests — PNM module
├── seatest.c / .h     # Lightweight C unit testing framework
├── Doxyfile           # Doxygen configuration
└── Makefile           # Build system
```

---

## Features

- **Barcode encoding** — converts input data into a visual barcode representation
- **PNM export** — renders the generated barcode as a `.pbm` / `.pgm` / `.ppm` image
- **Unit tested** — both the barcode and PNM modules are covered by automated tests
- **Documented** — full API documentation generated with Doxygen

---

## Build & Run

```bash
# Compile the main program
make

# Run barcode generator
./main <input> <output.pbm>

# Run unit tests
make test
./pnm_test
./test
```

---

## Tools Used

| Tool | Purpose |
|------|---------|
| `gcc` | C compiler |
| `Makefile` | Build automation |
| `Seatest` | Unit testing framework |
| `valgrind` | Memory leak detection |
| `gdb` | Debugging |
| `Doxygen` | API documentation generation |
| `git` | Version control |

---

## Key Concepts Practiced

- **Module reuse** — PNM library integrated from the previous project
- **Unit testing in C** with Seatest (`assert_*` macros, test suites)
- **Opaque types** and clean API design
- Barcode encoding algorithms and binary image rendering
- Automated build with separate test targets in `Makefile`

---

## Author

**Jamaa Jair** — [LinkedIn](https://linkedin.com/in/jamaa-jair-286656137/)
University of Liège · B.Sc. Computer Science · 2022–2025

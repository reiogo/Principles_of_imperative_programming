# Principles of Imperative Programming (CS15122 at CMU)
![proofs](https://img.shields.io/badge/proofs-verified-blue)
![language](https://img.shields.io/badge/language-C0%2FCC0-lightgrey)

inspired by [CMU CS15122](https://www.cs.cmu.edu/~15122/) — a foundational computer science course at Carnegie Mellon University.
This repository contains exercises, implementations, and proofs inspired by the CS15122.

**Note:** This is a personal study repository.


---

## 📌 Overview

This repository contains my personal work implementing and verifying classic algorithms using **C0/CC0**, with a strong emphasis on:
- ✅ **Formal contracts** — preconditions, postconditions, and loop invariants.
- 🧮 **Proofs of correctness and complexity**.
- 🧰 **Imperative programming discipline** — reasoning through mutation and state change.
- 🧭 **Algorithmic thinking under rigor** — not just working code, but **mathematically justified code**.

This is not a fork or copy of course materials — implementations, reasoning steps, and annotations are written from scratch while following the same problem structure and goals as CMU's CS15122 course.

---

## 🧰 What’s Inside

- **Core algorithms**: sorting algorithms, binary search, AVL trees, spanning trees and more.
- **Verified properties**: loop invariants, sortedness proofs, and complexity bounds.
- **Contract-driven development**: proving correctness *before* or *alongside* implementation.

---


## 🌟 Highlights

Some of the challenging and rewarding exercises:
- [Proof-driven Insertion Sort](./highlights/insertion_sort.c0) implemented and verified with full loop invariants and correctness proofs.
- [Binary Search with Proof](./highlights/binary_search.c0) implemented and verified with full proof.


---

## 🐳 Getting Started (with Docker)

This repo includes a Dockerfile so you can run the code in a clean Unix-based C0/CC0 environment.

```bash
# Build the image
docker build --platform=linux/amd64 -t cs15122  .

# Run interactively
docker run -it --rm -v "$PWD":/work --platform=linux/amd64 cs15122

# Inside container: compile & run
cd /work/test
cc0 test.c0
./a.out

# Or use interpreter
coin -d test.c0
```



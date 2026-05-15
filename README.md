# Unreal Gameplay Ability System Prototype

## Overview

This project is a focused Unreal Engine C++ prototype built to demonstrate the integration and extension of Unreal’s Gameplay Ability System (GAS) within a clean, modular gameplay architecture.

Rather than recreating GAS, the project leverages it as a foundation and introduces a lightweight framework layer on top, focusing on data-driven configuration, input abstraction, and runtime debugging.

The goal is to showcase practical systems design, maintainability, and the ability to extend complex engine systems in a controlled and scalable way.

---

## Key Features

* Integration with Unreal Gameplay Ability System (GAS)
* Data-driven ability configuration using custom DataAssets
* Decoupled input-to-ability mapping via Gameplay Tags
* Modular ability granting system
* Basic gameplay abilities (Dash, Heal, Damage)
* Lightweight gameplay state handling using Gameplay Tags (e.g. stun/block)
* Runtime debug tools for abilities, cooldowns, and active tags

---

## Technical Highlights

* Clear separation between:

  * Input handling
  * Ability activation
  * Data configuration
* Extension layer built on top of GAS (not a replacement)
* Data-driven workflow enabling easy ability scaling without code changes
* Tag-based architecture aligned with GAS best practices
* Debug-friendly systems for fast iteration and validation

---

## Architecture

The project is structured into the following layers:

### Ability System (GAS)

Handles:

* Ability execution
* Gameplay Effects
* Cooldowns
* Replication and core logic

### Ability Framework (Custom Layer)

Adds:

* Ability configuration via DataAssets
* Input abstraction using Gameplay Tags
* Ability granting and mapping logic
* Lightweight gameplay state control
* Debug and visualization tools

### Gameplay Layer

* Character setup
* Ability initialization
* Input binding

---

## Purpose

This project is a technical showcase of:

* Unreal Engine C++ gameplay programming
* Working with large and complex systems (GAS)
* Designing extensible and maintainable gameplay architecture
* Applying data-driven design patterns in real-time systems

---

## Notes

* This is not a full game, but a systems-focused prototype
* Visual assets are minimal and used only for demonstration
* Some assets may come from Epic Games sample content (e.g. Paragon)

---

## Author

Samuel Cazetta
Gameplay / Programmer

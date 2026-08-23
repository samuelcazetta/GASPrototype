# Unreal Gameplay Ability System - Technical Gameplay Prototype

## Overview

A C++ Unreal Engine gameplay programming prototype built around the **Gameplay Ability System (GAS)**, focused on network-aware architecture, reusable character abilities, AI-driven combat, replicated gameplay systems, Steam session flow, and Blueprint-extendable gameplay content.

The project was designed from the start as a GAS-focused, multiplayer-aware gameplay study, and evolved into a small playable prototype combining player abilities, AI combat, replicated interactions, and Steam session flow.

---

## Quick Highlights

* Two playable characters sharing a reusable GAS-based ability framework
* Multiplayer-aware ability execution using Local Predicted, Server Initiated, and Server Only policies
* AI enemies using Behavior Trees to drive Gameplay Abilities
* Replicated attributes, projectiles, pickups, treasure state, death, and respawn
* Animation-driven melee combat with event-based damage and hit reactions
* Steam Host / Find / Join session flow for multiplayer testing
* C++ gameplay infrastructure with Blueprint-extensible content workflows

---

## Demo

Demo video/GIF coming soon.

---

## Tech Stack

Unreal Engine C++ | Gameplay Ability System | Gameplay Tags | Gameplay Effects | Gameplay Events | Gameplay Cues | Enhanced Input | Behavior Trees | Replication | Steam Online Subsystem | Advanced Sessions | Blueprint

---

## In-Depth Description

Rather than forcing every mechanic into GAS, the project separates responsibilities between **Gameplay Abilities, Gameplay Effects, Gameplay Tags, Gameplay Events, Gameplay Cues, animation-driven systems, AI, and custom gameplay code**.

The goal is to demonstrate practical Unreal Engine C++ gameplay programming, maintainable system design, multiplayer awareness, and the ability to extend engine-native systems in a reusable way.

### Key Features

* Unreal Engine Gameplay Ability System integration
* Network-aware gameplay architecture with server authority and GAS prediction
* Gameplay Ability activation through native Gameplay Tags
* Replicated Health, Max Health, Power, and Max Power attributes
* Gameplay Effect-based damage, regeneration, cooldown, and ability cost flows
* Event-driven Hit React and Death abilities
* Animation-driven melee hit detection using reusable trace notifies
* Multi-stage melee combo system with animation-defined combo windows
* Character-specific Dash and Special abilities
* Replicated ranged projectile combat
* Shared gameplay architecture across multiple playable characters
* AI combat driven through Behavior Trees and Gameplay Abilities
* Enemy regeneration, death, respawn, and combat state handling
* Replicated treasure and pickup interaction flow
* Gameplay Cue-based combat feedback using VFX, SFX, voice, and camera shake
* Character selection and Steam Host / Find / Join session flow
* Blueprint-extensible gameplay classes backed by reusable C++ systems

### Playable Characters

The prototype currently includes two playable characters built on the same gameplay framework.

#### Wukong

Melee-focused character featuring:

* Multi-stage melee combo
* Animation-driven melee traces
* Dash
* Area special attack
* Distance-based knockback
* Character-specific impact and activation feedback

#### Phase

Ranged-focused character featuring:

* Projectile-based attacks
* Replicated projectile movement and collision
* Forward target selection
* Dash
* Character-specific special attack
* Projectile audio and visual feedback

The two characters intentionally reuse shared ability and character infrastructure while keeping character-specific behavior configurable through derived Blueprint assets.

### Gameplay Ability System

GAS is responsible for the systems it is designed to solve:

* Gameplay Abilities
* Gameplay Effects
* Gameplay Tags
* Gameplay Events
* Attribute management
* Ability costs
* Cooldowns
* Gameplay state representation
* Prediction-aware ability execution
* Replicated gameplay state
* Gameplay Cues

Custom gameplay systems handle mechanics that benefit from remaining outside GAS, such as:

* Melee collision traces
* Animation-defined combat windows
* Target queries
* Projectile actors
* Character-specific presentation
* World interaction logic

This keeps GAS as the gameplay framework rather than attempting to replace or recreate it.

### Combat Architecture

A typical melee attack follows an event-driven pipeline:

```text
Player Input
    ->
Gameplay Ability
    ->
Animation Montage
    ->
Anim Notify / Notify State
    ->
Combat Trace
    ->
Gameplay Event
    ->
Confirmed Hit
    ->
Gameplay Effect / Hit React Event
    ->
Target Gameplay Ability
    ->
Gameplay Cue
```

Core gameplay consequences remain separated from cosmetic presentation.

For example, Hit React behavior is handled by a **Server Initiated Gameplay Ability**, while its particles, sounds, and camera feedback remain inside a **Gameplay Cue**.

### Attributes and Resources

Characters use replicated GAS attributes including:

* Health
* Max Health
* Power
* Max Power

Power acts as the resource used by special abilities.

Successful attacks can accelerate Power generation through source-side Gameplay Effects, while special abilities consume the resource using GAS's native cost flow.

Attribute widgets react to Ability System Component delegates rather than continuously polling gameplay state.

### AI Integration

Enemies use the same gameplay systems as player-controlled characters whenever possible.

Behavior Trees decide **what the AI wants to do**, while GAS executes the gameplay action.

```text
Behavior Tree
    ->
BT Task
    ->
Gameplay Ability
    ->
Gameplay Effects / Gameplay Events / Gameplay Cues
```

The AI flow includes:

* Target acquisition
* Target focus
* Chase behavior
* Melee attack execution through GAS
* Leash / return behavior
* Out-of-combat regeneration
* Hit reactions
* Death
* Respawn

This avoids maintaining separate combat implementations for players and AI.

### World Interaction

The project also includes a small replicated gameplay loop built around guarded treasures.

```text
Enemy guards Treasure
    ->
Enemy dies
    ->
Treasure unlocks
    ->
Pickup is spawned on authority
    ->
Player receives Gameplay Effect
    ->
Enemy respawns
    ->
Treasure resets
```

Enemy death and respawn delegates allow world objects to react to gameplay state without coupling the treasure directly to the enemy's internal GAS implementation.

### Multiplayer and Steam Sessions

Multiplayer has been considered throughout the project rather than added as a final layer.

The gameplay architecture includes:

* Server-authoritative gameplay consequences
* Local Predicted player abilities where appropriate
* Server Initiated reaction abilities
* Server Only NPC abilities
* Replicated attributes and gameplay state
* Replicated projectiles
* Multiplayer-safe death and respawn handling
* Local-only presentation where appropriate

The project also includes a simple Steam session flow using the Steam Online Subsystem with Advanced Sessions support.

```text
Session Menu
    ->
Select Character
    ->
Host / Find Session
    ->
Join
    ->
Gameplay Map
```

Character selection is persisted through the session transition and used by the gameplay GameMode when choosing the player's pawn.

The online implementation intentionally remains small: its purpose is to make the multiplayer gameplay systems easy to demonstrate rather than build a complete matchmaking or lobby framework.

### C++ and Blueprint Responsibilities

The project uses C++ for reusable gameplay infrastructure and Blueprint for content configuration and presentation.

#### C++

Used primarily for:

* Ability framework code
* Ability System initialization
* Attribute handling
* Combat validation
* Melee traces
* Target queries
* Projectile behavior
* Shared ability logic
* AI tasks and services
* Replication-sensitive gameplay
* World interaction infrastructure

#### Blueprint

Used primarily for:

* Character variants
* Gameplay Ability configuration
* Animation Montages
* Gameplay Effects
* Gameplay Cues
* VFX / SFX assignment
* Character-specific presentation
* Behavior Tree configuration
* Gameplay tuning

The intention is to keep gameplay logic reusable in C++ while allowing content to remain easily configurable and extendable through Unreal's editor workflow.

### Project Structure

The project separates first-party gameplay content from imported sample assets.

```text
Source/
    AbilitySystem/
    Character/
    AI/
    GameObjects/
    Player/
    Utility/
    GameplayTags/

Content/
    GASPrototype/
        AbilitySystem/
        Characters/
        AI/
        GameObjects/
        UI/
        Maps/

    ThirdParty/
        Paragon/
        Prototype Assets/
        External Content/
```

Third-party and Epic Games sample assets are kept isolated from project-specific gameplay content.

### Technical Focus

This project demonstrates practical experience with:

* Unreal Engine C++
* Gameplay Ability System
* Gameplay Tags
* Gameplay Events
* Gameplay Effects
* Gameplay Cues
* Ability Tasks
* Enhanced Input
* Character / PlayerState GAS ownership patterns
* Server authority and client prediction
* Replication
* Animation-driven gameplay
* Behavior Trees
* AI / GAS integration
* Runtime delegates
* Reusable gameplay architecture
* Blueprint / C++ interoperability
* Steam multiplayer sessions

### Purpose

This is **not intended to be a full game or feature-complete hack and slash project**.

It is a systems-focused portfolio project created to demonstrate how I approach gameplay programming in Unreal Engine:

* designing reusable gameplay systems;
* working with engine-native frameworks rather than recreating them;
* separating gameplay logic from presentation;
* sharing systems between players and AI;
* considering networking during implementation;
* refactoring systems as their responsibilities become clearer;
* keeping C++ infrastructure extensible through Blueprint content.

### Assets

Visual and audio assets are used for demonstration purposes.

Some content comes from Epic Games sample and Marketplace assets, including Paragon character content and Unreal Engine prototyping assets.

All imported external content is kept separate from project-specific gameplay assets under the `ThirdParty` content structure.

---

## Author

**Samuel Cazetta**  
Systems / Gameplay Programmer

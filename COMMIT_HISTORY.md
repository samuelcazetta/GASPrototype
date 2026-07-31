# Historico completo de commits

Gerado a partir de `git log --reverse` em 2026-07-30.

## 1. **Initial commit**

- Data: 15/05/2026
- Description: Sem descricao.

## 2. **git lfs**

- Data: 15/05/2026
- Description: Sem descricao.

## 3. **Add initial README for Gameplay Ability System Prototype**

- Data: 15/05/2026
- Description: This README provides an overview of the Unreal Gameplay Ability System Prototype, detailing its features, architecture, and purpose.

## 4. **chore: ignore IDE files and add project note**

- Data: 15/05/2026
- Description: Sem descricao.

## 5. **ThirdParty Asset**

- Data: 15/05/2026
- Description: Character Wukong

## 6. **feat: add player character and enhanced input setup**

- Data: 15/05/2026
- Description:
  - Adds base and player character classes with third-person camera setup
  - Implements player controller input bindings for movement, look, and jump
  - Adds Enhanced Input assets, player blueprints, game mode, and test map
  - Updates module dependencies for UMG and Gameplay Ability System support

## 7. **feat: add initial GAS ability system setup**

- Data: 17/05/2026
- Description:
  - Adds base gameplay ability configuration flags
  - Adds Ability System Component to the player state with mixed replication
  - Initializes GAS actor info on player possession and player state replication
  - Adds startup ability granting support to the base character
  - Adds skill input bindings for attack, dash, and special actions
  - Updates player/controller blueprints, input mapping assets, test map, and Wukong-related assets

## 8. **feat: wire skill inputs to native gameplay tags**

- Data: 18/05/2026
- Description:
  Adds native gameplay tags for attack, dash, and special abilities

  Routes skill input actions through the base character ability activation flow

  Updates movement input to use the cached base character reference

  Updates player ability/blueprint assets for the attack ability setup

  Adds experimental movement tuning notes for the player character

## 9. **feat: add GAS combo attack flow**

- Data: 20/05/2026
- Description:
  - Adds Wukong attack ability assets for start, chain and finisher attack
  - Adds gameplay tags for attack continuation, combo window events, combo-ready states, and movement input blocking
  - Updates ability activation to support primary and fallback ability tags for combo chaining
  - Blocks movement input while the character has the movement input blocked state tag
  - Adds attack-specific gameplay effects, gameplay cue, notify, and audio assets
  - Updates Wukong attack montages, player blueprint, and test map for the combo attack setup

## 10. **feat: add melee attack trace event pipeline**

- Data: 22/05/2026
- Description:
  - Adds a melee attack notify state with socket-based sphere tracing
  - Routes melee hit detection through the GAS gameplay event pipeline
  - Adds attack hit gameplay tag for melee combat events
  - Adds blueprint utility helper to dispatch gameplay events with hit result payload data
  - Adds custom attack collision channel and character overlap collision setup
  - Updates attack ability flow to react to melee hit events
  - Updates Wukong attack montages, gameplay cue, player blueprint, and skeleton assets
  - Routes controller alive validation through base character state

## 11. **feat: add GAS attributes and hit reaction flow**

- Data: 28/05/2026
- Description:
  - Adds custom ability system component with ActivateOnGiven support
  - Adds replicated attribute set for health and mana initialization
  - Initializes character attributes through a startup gameplay effect
  - Adds hit reaction gameplay ability with cached hit direction vectors
  - Adds hit react container for montage, sound, and particle response data
  - Adds utility helpers for hit direction and gameplay event dispatch
  - Adds gameplay tags for hit react and auto-activated abilities
  - Reorganizes ability classes under the AbilitySystem/Abilities folder
  - Updates Wukong attack, damage, combo, gameplay cue, and hit react assets
  - Moves Wukong player and melee montage assets into the project content structure

## 12. **feat: add GAS attribute widget binding flow**

- Data: 28/05/2026
- Description:
  - Adds attribute widget base class for displaying current and max attribute values
  - Adds widget component that binds child widgets to GAS attribute change delegates
  - Defers widget binding until the ASC and AttributeSet are initialized
  - Broadcasts ASC and AttributeSet initialization from the player character
  - Exposes AttributeSet access through base/player character and player state
  - Broadcasts attribute initialization events for UI synchronization
  - Pushes initial attribute values to widgets before future change events

## 13. **feat: add player stats UI widgets**

- Data: 01/06/2026
- Description:
  - Adds player stats widget and reusable health bar widget assets
  - Adds blueprint widget component for GAS attribute UI
  - Updates Wukong player blueprint to use the new UI widget setup

## 14. **feat: add dash ability flow**

- Data: 04/06/2026
- Description:
  - Adds player dash ability, dash cooldown effect, dash notify, and dash movement curve
  - Adds dash gameplay cue, Niagara dash trail FX, and GameplayCue.Dash config entry
  - Adds Wukong dash/flip animations and updates player, input mapping, test map, and animation assets
  - Adds gameplay tags for dash cooldown, air-dashed movement state, and intangible state
  - Clears the air-dashed state when the character lands
  - Adds tangibility checks so melee hit events ignore intangible targets
  - Adds a gameplay ability helper for removing matching loose gameplay tags
  - Renames/moves Wukong attack and hit react montages into the project animation set

## 15. **feat: add death flow and combat audio cues**

- Data: 16/06/2026
- Description:
  - Adds death ability/event/state tags and death gameplay effect
  - Triggers death gameplay event when health reaches zero
  - Updates IsAlive to use the Dead gameplay tag instead of always returning true
  - Adds Wukong death ability and death montage assets
  - Adds attribute reset helper for respawn/retry flows
  - Adds GameMode helper to pick a random PlayerStart spawn point
  - Updates Wukong player Blueprint with death, hit react, dash, UI, and audio references
  - Replaces/renames dash gameplay cue and adds combat sound cues for dash, hit impact, and Wukong attacks
  - Enables WaveformEditor plugin for audio asset work
  - Updates attack, hit react, dash, map, and game mode assets to match the new flow

## 16. **feat: add Wukong special attack flow**

- Data: 22/06/2026
- Description:
  - Adds Wukong special attack ability, cooldown effect, damage effect, montages, notifies, and audio cues
  - Adds GameplayCue.Special and special attack quote gameplay cues
  - Adds special attack cooldown gameplay tag
  - Adds shared attack helper to send hit react events and apply damage once per target
  - Updates melee attack notify trace settings for special attack hit detection
  - Adds player post-process component and custom depth setup for special attack visual highlighting
  - Adds post-process material assets for the special attack effect
  - Updates Wukong player Blueprint to include the special attack startup ability and fade-in post-process timeline
  - Updates attack/dash/map assets and removes older basic attack/attack sound cue assets
  - Adjusts render settings for custom depth and exposure behavior

## 17. **feat: add Paragon Phase character assets**

- Data: 22/06/2026
- Description:
  - Adds the Paragon Phase content pack with meshes, materials, animations, FX, audio, and maps
  - Adds the Phase player character Blueprint under GASPrototype characters
  - Updates the game mode Blueprint to reference the new Phase character setup

## 18. **chore: relocate Paragon Phase assets to ThirdParty**

- Data: 22/06/2026
- Description:
  - Moves imported Paragon Phase content into the ThirdParty content folder
  - Keeps external/vendor assets separated from project-specific GASPrototype assets

## 19. **feat: split player abilities into base and character variants**

- Data: 23/06/2026
- Description:
  - Moves shared player ability Blueprints into a Base ability folder
  - Adds Wukong-specific dash and special attack ability variants
  - Adds Phase-specific dash ability setup using a retargeted dash montage
  - Retargets a Wukong dash animation for Phase to cover the missing native dash animation
  - Adds Phase animation assets for dash, hit react, flip, and retargeting
  - Renames the Wukong player Blueprint to make room for character-specific player setups
  - Updates Phase player, dash cooldown, and Phase animation Blueprint Mask references

## 20. **feat: add Phase ranged attack flow**

- Data: 29/06/2026
- Description:
  - Adds a ranged attack ability base with target lookup for forward-aligned enemies
  - Adds cpp bp utility helpers to find nearby GAS characters by overlap radius and validate facing direction with dot product checks
  - Adds a replicated base projectile actor that applies damage and triggers hit react on overlap
  - Adds Phase projectile attack ability, projectile notify, attack montage, projectile Blueprint, and emissive projectile material
  - Wires the Phase player and animation Blueprint for the projectile attack setup

## 21. **feat: add pushback to Wukong special attack**

- Data: 01/07/2026
- Description:
  - Adds a Blueprint-callable pushback helper for launching hit actors away from the avatar
  - Scales launch force by distance using inner and outer radius falloff
  - Supports angled launch arcs and optional debug visualization for pushback direction/force
  - Updates Wukong special attack to apply pushback

## 22. **feat: add player character switch flow**

- Data: 02/07/2026
- Description:
  - Adds GameMode-driven character cycling that skips the currently possessed character

  - Clears persisted PlayerState ASC abilities and active effects before possession changes

  - Cleans up attribute widget delegates so repeated character switches do not call destroyed widgets

## 23. **feat: add Phase special attack flow**

- Data: 06/07/2026
- Description:
  - Adds a shared special attack ability class under the GAS ability hierarchy
  - Adds Phase special attack flow with montage, logic and gameplay effect/cue activation
  - Adds a BlueprintNativeEvent fade hook on the player character for special attack presentation
  - Adds Phase special attack VFX using the Phase ult charge particle
  - Reuses the shared special attack ability path across Phase and Wukong instead of duplicating character logic
  - Adds character gameplay tags to keep character-specific VFX/cue routing data-driven
  - Preserves gameplay event hit context through damage application for cleaner hit react/VFX integration
  - Switches range targeting to sphere trace hit results so abilities can reuse impact/location context
  - Updates Wukong special attack with knockback and its own gameplay cue as validation of the shared flow

## 24. **feat: add enemy character GAS foundation**

- Data: 06/07/2026
- Description:
  - Adds an enemy character class with its own replicated ASC and AttributeSet
  - Initializes enemy GAS actor info, startup abilities, attributes, and health change handling on BeginPlay
  - Adds a base AI controller and Blueprint controller for future enemy behavior
  - Adds AIModule dependency for AI controller support
  - Adds an enemy character Blueprint wired to the new C++ enemy/AI setup
  - Reorganizes playable character assets under Characters/Player for clearer player/enemy separation

## 25. **feat: add Paragon minion assets and basic enemy setup**

- Data: 07/07/2026
- Description:
  - Adds Paragon Minions third-party content for enemy character prototyping
  - Creates the enemy character Blueprint for the minion-based enemy setup
  - Gives startup abilities, attributes and UI do enemy BP
  - Creates the enemy basic Animation Blueprint with threadsafe animation update
  - Renames shared ability Blueprints with a `_Base` suffix for clearer inheritance

## 26. **feat: add enemy BT combat flow**

- Data: 15/07/2026
- Description:
  - Adds enemy behavior tree and blackboard flow for combat, return, and idle states
  - Starts the behavior tree from `AGASP_AIController` and stores the enemy spawn location for return behavior
  - Adds BT services for AI perception, alive state synchronization, target acquisition, and focus management
  - Adds BT tasks that drive enemy combat through the Gameplay Ability System, including melee attacks, health regeneration, and regeneration cancellation
  - Adds combat flow that combines Behavior Trees with GAS abilities for enemy attack execution
  - Adds return and idle flow that restores the enemy to its guarded position and starts out-of-combat regeneration
  - Adds gameplay tags for enemy abilities and regeneration effects
  - Adds enemy melee, hit react, death, and health recovery GAS ability/effect assets

## 27. **chore: gameplay polish**

- Data: 15/07/2026
- Description:
  - Improves gameplay and AI robustness
  - Standardizes asset naming
  - Removes obsolete files

## 28. **feat: add guarded treasure pickup flow**

- Data: 16/07/2026
- Description:
  - Adds replicated pickup actor support that applies a configured GameplayEffect to overlapping player characters
  - Adds replicated treasure actor support with a guarded unlock flow and Blueprint event for unlock presentation
  - Broadcasts an enemy death delegate so world objects can react to defeated guards outside the GAS ability flow
  - Hides and disables treasure pickup collision until the assigned guard dies
  - Adds treasure, pickup, and renamed projectile Blueprints using the `BP_GASP_*` naming pattern
  - Adds Asure chest and Paragon buff FX assets for treasure and pickup presentation
  - Updates TestMap with guarded treasure/pickup setup and removes generated placeholder geometry

## 29. **feat: add power resource and special cost flow**

- Data: 20/07/2026
- Description:
  - Adds replicated Power/MaxPower attributes
  - Adds Power initialization, clamping, replication notifies, and a dedicated player power bar widget
  - Adds `GE_PowerCharge` as a startup regen effect that slowly fills the Power bar over time
  - Adds `GE_PowerCharge_OnHit` to reward successful hits by charging the attacker’s Power faster
  - Adds `GE_SpecialCost` so special abilities consume Power on activation
  - Updates attack damage helper to optionally apply on-hit Power charge effects to the attacker
  - Updates projectile hit logic to grant on-hit Power charge to the projectile owner after successful damage/hit react
  - Updates player/enemy attack and special ability assets to use Power charge and special cost effects
  - Supports multiple initial attribute effects on base characters for cleaner startup effect composition
  - Updates UI widget bindings to include the new Power display

## 30. **chore: clean up gameplay cue and special attack assets**

- Data: 21/07/2026
- Description:
  - Updates hit react references to keep the cue name character-agnostic
  - Cleans up Phase and Wukong special attack ability/cue assets after the Power cost changes
  - Adjusts projectile overlap handling while preserving damage, hit react, and Power charge flow

## 31. **feat: move hit reactions and death to event-driven GAS abilities**

- Data: 24/07/2026
- Description:
  - Adds a Server Initiated hit reaction ability activated by Event.HitReact, moving montage/cancel/block state handling into the Gameplay Ability flow
  - Keeps GC_HitReact focused on cosmetic feedback such as VFX and SFX instead of driving core reaction logic
  - Refactors attack hit handling into HandleConfirmedHit to validate targets, prevent duplicate hits, apply damage, send Event.HitReact to the target, and apply source on-hit effects
  - Preserves multiplayer authority by having the server dispatch the hit reaction event on the target ASC instead of the source directly driving the victim reaction
  - Updates melee and special attack assets to use the new confirmed-hit consequence flow
  - Updates player and enemy startup abilities to include the event-driven hit react and death abilities
  - Keeps death routed through the health change flow into Event.Death, letting GA_GASP_Death own terminal state, cancellation, and blocking behavior
  - Simplifies initial attribute initialization by validating the Ability System Component once before applying startup effects

## 32. **fix: use instigator hit react effects in gameplay cue**

- Data: 27/07/2026
- Description:
  - Updates the hit react cue flow to read particles and sound from the instigator's HitReactContainer instead of the reacting target
  - Preserves the target as the actor receiving the hit reaction while letting the attack source define the impact feedback
  - Adjusts GA_GASP_HitReactByEvent and GC_HitReact assets around the corrected cue parameter flow
  - Cleans up minor base character death comments and range helper formatting

## 33. **feat: expand gameplay cue and impact feedback**

- Data: 30/07/2026
- Description:
  - Adds character-specific attack and hit impact cues for Phase, Wukong, and enemies
  - Adds Phase voice/audio feedback for special attack and projectile attack, including a dedicated projectile looping sound
  - Adds native special attack activation audio through UGASP_SpecialAttack
  - Adds native projectile audio support with an AudioComponent and configurable AudioEffect on AGASP_BaseProjectile
  - Adds Phase special attack VFX/voice cue tags and redirects the old Phase special sound cue tag to the new voice tag
  - Adds camera shake feedback to hit react and introduces a death gameplay cue burst with Blueprint-configured camera shake
  - Updates Phase, Wukong, enemy, projectile, and hit react assets to use the new sound cue and particle feedback setup
  - Reorganizes third-party miscellaneous assets and replaces older shared cue assets with more specific per-character cues


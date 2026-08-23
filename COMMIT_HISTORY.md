# GASPrototype Development Log

Generated from `git log --reverse` on 2026-08-05.

This document summarizes the technical evolution of **GASPrototype**, an Unreal Engine C++ gameplay prototype focused on the Gameplay Ability System, modular combat systems, AI behavior, replicated gameplay interactions, Steam sessions, and data-driven content workflows.

## Technical Overview

Across the project history, the prototype was built from the start as a GAS-focused, multiplayer-aware Unreal Engine gameplay sandbox, then expanded into a playable combat prototype with player and NPC interactions:

- Unreal Engine C++ gameplay framework integration
- Gameplay Ability System setup with replicated ASC/AttributeSet flows
- Gameplay Tags, Gameplay Effects, Gameplay Events, and Gameplay Cues
- melee, ranged, dash, special attack, hit reaction, death, and respawn flows
- character-specific abilities for Wukong and Phase
- AI enemies driven by Behavior Trees and GAS abilities
- replicated projectiles, pickups, guarded treasure, and character selection
- Steam session menu flow using OnlineSubsystemSteam and Advanced Sessions
- Blueprint/Data Asset content extension over C++ gameplay foundations

## Development Timeline

## 1. Initial Commit

- Date: 2026-05-15
- Summary: Created the initial Unreal Engine project baseline.

## 2. Git LFS Setup

- Date: 2026-05-15
- Summary: Added Git LFS support for Unreal Engine binary assets.

## 3. Add Initial README For Gameplay Ability System Prototype

- Date: 2026-05-15
- Summary:
  - Added the first project README.
  - Documented the initial purpose, architecture direction, and planned Gameplay Ability System focus.

## 4. Ignore IDE Files And Add Project Note

- Date: 2026-05-15
- Summary:
  - Added repository hygiene rules for IDE/generated files.
  - Added early project notes.

## 5. Add Third-Party Wukong Character Asset

- Date: 2026-05-15
- Summary:
  - Imported the Wukong character content used as the first playable character prototype.

## 6. Add Player Character And Enhanced Input Setup

- Date: 2026-05-15
- Summary:
  - Added base and player character C++ classes with third-person camera setup.
  - Implemented player controller input bindings for movement, look, and jump.
  - Added Enhanced Input assets, player Blueprints, GameMode, and test map.
  - Updated module dependencies for UMG and Gameplay Ability System support.

## 7. Add Initial GAS Ability System Setup

- Date: 2026-05-17
- Summary:
  - Added base gameplay ability configuration flags.
  - Added the Ability System Component to PlayerState using Mixed Replication.
  - Initialized GAS actor info on player possession and PlayerState replication.
  - Added startup ability granting support to the base character.
  - Added skill input bindings for attack, dash, and special actions.
  - Updated player/controller Blueprints, input mapping assets, test map, and Wukong-related assets.

## 8. Wire Skill Inputs To Native Gameplay Tags

- Date: 2026-05-18
- Summary:
  - Added native gameplay tags for attack, dash, and special abilities.
  - Routed skill input actions through the base character ability activation flow.
  - Updated movement input to use the cached base character reference.
  - Updated player ability and Blueprint assets for the first attack ability setup.
  - Added experimental movement tuning notes for the player character.

## 9. Add GAS Combo Attack Flow

- Date: 2026-05-20
- Summary:
  - Added Wukong attack ability assets for start, chain, and finisher attacks.
  - Added gameplay tags for attack continuation, combo window events, combo-ready states, and movement input blocking.
  - Updated ability activation to support primary and fallback ability tags for combo chaining.
  - Blocked movement input while the character has the movement input blocked state tag.
  - Added attack-specific gameplay effects, gameplay cue, notify, and audio assets.
  - Updated Wukong attack montages, gameplay cue, player Blueprint, and test map for combo combat.

## 10. Add Melee Attack Trace Event Pipeline

- Date: 2026-05-22
- Summary:
  - Added a melee attack notify state with socket-based sphere tracing.
  - Routed melee hit detection through the GAS gameplay event pipeline.
  - Added attack hit gameplay tag for melee combat events.
  - Added Blueprint utility support for dispatching gameplay events with hit result payload data.
  - Added a custom attack collision channel and character overlap collision setup.
  - Updated attack ability flow to react to melee hit events.
  - Updated Wukong attack montages, gameplay cue, player Blueprint, and skeleton assets.
  - Routed controller alive validation through base character state.

## 11. Add GAS Attributes And Hit Reaction Flow

- Date: 2026-05-28
- Summary:
  - Added a custom Ability System Component with ActivateOnGiven support.
  - Added replicated AttributeSet support for health and mana initialization.
  - Initialized character attributes through startup Gameplay Effects.
  - Added hit reaction gameplay ability with cached hit direction vectors.
  - Added hit react containers for montage, sound, and particle response data.
  - Added utility helpers for hit direction and gameplay event dispatching.
  - Added gameplay tags for hit react and auto-activated abilities.
  - Reorganized ability classes under the AbilitySystem/Abilities folder.
  - Updated Wukong attack, damage, combo, gameplay cue, and hit react assets.

## 12. Add GAS Attribute Widget Binding Flow

- Date: 2026-05-28
- Summary:
  - Added an attribute widget base class for displaying current and max attribute values.
  - Added widget component support for binding child widgets to GAS attribute change delegates.
  - Deferred widget binding until the ASC and AttributeSet are initialized.
  - Broadcasted ASC and AttributeSet initialization from the player character.
  - Exposed AttributeSet access through base/player character and PlayerState.
  - Broadcasted attribute initialization events for UI synchronization.
  - Pushed initial attribute values to widgets before future change events.

## 13. Add Player Stats UI Widgets

- Date: 2026-06-01
- Summary:
  - Added player stats widget and reusable health bar widget assets.
  - Added Blueprint widget component support for GAS attribute UI.
  - Updated Wukong player Blueprint to use the new UI widget setup.

## 14. Add Dash Ability Flow

- Date: 2026-06-04
- Summary:
  - Added player dash ability, dash cooldown effect, dash notify, and dash movement curve.
  - Added dash gameplay cue, Niagara dash trail FX, and GameplayCue.Dash configuration.
  - Added Wukong dash/flip animations and updated player, input mapping, test map, and animation assets.
  - Added gameplay tags for dash cooldown, air-dashed movement state, and intangible state.
  - Cleared the air-dashed state when the character lands.
  - Added tangibility checks so melee hit events ignore intangible targets.
  - Added a gameplay ability helper for removing matching loose gameplay tags.
  - Renamed and moved Wukong attack and hit react montages into the project animation set.

## 15. Add Death Flow And Combat Audio Cues

- Date: 2026-06-16
- Summary:
  - Added death ability/event/state tags and death Gameplay Effect.
  - Triggered death gameplay events when health reaches zero.
  - Updated `IsAlive` to use the Dead gameplay tag.
  - Added Wukong death ability and death montage assets.
  - Added an attribute reset helper for respawn/retry flows.
  - Added GameMode support for selecting random PlayerStart spawn points.
  - Updated Wukong player Blueprint with death, hit react, dash, UI, and audio references.
  - Added combat sound cues for dash, hit impact, and Wukong attacks.
  - Enabled the WaveformEditor plugin for audio asset work.

## 16. Add Wukong Special Attack Flow

- Date: 2026-06-22
- Summary:
  - Added Wukong special attack ability, cooldown effect, damage effect, montages, notifies, and audio cues.
  - Added GameplayCue.Special and special attack quote gameplay cues.
  - Added special attack cooldown gameplay tag.
  - Added shared attack helper logic to send hit react events and apply damage once per target.
  - Updated melee attack notify trace settings for special attack hit detection.
  - Added player post-process component and custom depth setup for special attack visual highlighting.
  - Added post-process material assets for the special attack effect.
  - Updated Wukong player Blueprint with special attack startup ability and fade-in post-process presentation.
  - Adjusted render settings for custom depth and exposure behavior.

## 17. Add Paragon Phase Character Assets

- Date: 2026-06-22
- Summary:
  - Added the Paragon Phase content pack with meshes, materials, animations, FX, audio, and maps.
  - Added the Phase player character Blueprint under GASPrototype characters.
  - Updated the GameMode Blueprint to reference the new Phase character setup.

## 18. Relocate Paragon Phase Assets To ThirdParty

- Date: 2026-06-22
- Summary:
  - Moved imported Paragon Phase content into the ThirdParty content folder.
  - Kept external/vendor assets separated from project-specific GASPrototype assets.

## 19. Split Player Abilities Into Base And Character Variants

- Date: 2026-06-23
- Summary:
  - Moved shared player ability Blueprints into a Base ability folder.
  - Added Wukong-specific dash and special attack ability variants.
  - Added Phase-specific dash ability setup using a retargeted dash montage.
  - Retargeted a Wukong dash animation for Phase to cover the missing native dash animation.
  - Added Phase animation assets for dash, hit react, flip, and retargeting.
  - Renamed the Wukong player Blueprint to support character-specific player setups.
  - Updated Phase player, dash cooldown, and Phase animation Blueprint mask references.

## 20. Add Phase Ranged Attack Flow

- Date: 2026-06-29
- Summary:
  - Added a ranged attack ability base with target lookup for forward-aligned enemies.
  - Added C++ Blueprint utility helpers to find nearby GAS characters by overlap radius.
  - Used dot product checks to validate forward-facing ranged attack targets.
  - Added a replicated base projectile actor that applies damage and triggers hit react on overlap.
  - Added Phase projectile attack ability, projectile notify, attack montage, projectile Blueprint, and emissive projectile material.
  - Wired the Phase player and Animation Blueprint for the projectile attack setup.

## 21. Add Pushback To Wukong Special Attack

- Date: 2026-07-01
- Summary:
  - Added a Blueprint-callable pushback helper for launching hit actors away from the avatar.
  - Scaled launch force by distance using inner and outer radius falloff.
  - Supported angled launch arcs and optional debug visualization for pushback direction and force.
  - Updated Wukong special attack to apply pushback.

## 22. Add Player Character Switch Flow

- Date: 2026-07-02
- Summary:
  - Added GameMode-driven character cycling that skips the currently possessed character.
  - Cleared persisted PlayerState ASC abilities and active effects before possession changes.
  - Cleaned up attribute widget delegates so repeated character switches do not call destroyed widgets.

## 23. Add Phase Special Attack Flow

- Date: 2026-07-06
- Summary:
  - Added a shared special attack ability class under the GAS ability hierarchy.
  - Added Phase special attack flow with montage, logic, and Gameplay Effect/Cue activation.
  - Added a BlueprintNativeEvent fade hook on the player character for special attack presentation.
  - Added Phase special attack VFX using the Phase ult charge particle.
  - Reused the shared special attack ability path across Phase and Wukong instead of duplicating character logic.
  - Added character gameplay tags to keep character-specific VFX/Cue routing data-driven.
  - Preserved gameplay event hit context through damage application for cleaner hit react and VFX integration.
  - Switched range targeting to sphere trace hit results so abilities can reuse impact/location context.
  - Updated Wukong special attack with knockback and its own gameplay cue as validation of the shared flow.

## 24. Add Enemy Character GAS Foundation

- Date: 2026-07-06
- Summary:
  - Added an enemy character class with its own replicated ASC and AttributeSet.
  - Initialized enemy GAS actor info, startup abilities, attributes, and health change handling on BeginPlay.
  - Added a base AI controller and Blueprint controller for future enemy behavior.
  - Added AIModule dependency for AI controller support.
  - Added an enemy character Blueprint wired to the new C++ enemy/AI setup.
  - Reorganized playable character assets under Characters/Player for clearer player/enemy separation.

## 25. Add Paragon Minion Assets And Basic Enemy Setup

- Date: 2026-07-07
- Summary:
  - Added Paragon Minions third-party content for enemy prototyping.
  - Created the enemy character Blueprint for the minion-based enemy setup.
  - Gave startup abilities, attributes, and UI to the enemy Blueprint.
  - Created the enemy basic Animation Blueprint with thread-safe animation update.
  - Renamed shared ability Blueprints with a `_Base` suffix for clearer inheritance.

## 26. Add Enemy Behavior Tree Combat Flow

- Date: 2026-07-15
- Summary:
  - Added enemy Behavior Tree and Blackboard flow for combat, return, and idle states.
  - Started the Behavior Tree from `AGASP_AIController`.
  - Stored enemy spawn location for return behavior.
  - Added BT services for AI perception, alive state synchronization, target acquisition, and focus management.
  - Added BT tasks that drive enemy combat through GAS, including melee attacks, health regeneration, and regeneration cancellation.
  - Combined Behavior Trees with GAS abilities for enemy attack execution.
  - Added return and idle flow that restores the enemy to its guarded position and starts out-of-combat regeneration.
  - Added gameplay tags for enemy abilities and regeneration effects.
  - Added enemy melee, hit react, death, and health recovery GAS ability/effect assets.

## 27. Gameplay Polish

- Date: 2026-07-15
- Summary:
  - Improved gameplay and AI robustness.
  - Standardized asset naming.
  - Removed obsolete files.

## 28. Add Guarded Treasure Pickup Flow

- Date: 2026-07-16
- Summary:
  - Added replicated pickup actor support that applies a configured Gameplay Effect to overlapping player characters.
  - Added replicated treasure actor support with a guarded unlock flow and Blueprint event for unlock presentation.
  - Broadcasted an enemy death delegate so world objects can react to defeated guards outside the GAS ability flow.
  - Hid and disabled treasure pickup collision until the assigned guard dies.
  - Added treasure, pickup, and renamed projectile Blueprints using the `BP_GASP_*` naming pattern.
  - Added Asure chest and Paragon buff FX assets for treasure and pickup presentation.
  - Updated TestMap with guarded treasure/pickup setup and removed generated placeholder geometry.

## 29. Add Power Resource And Special Cost Flow

- Date: 2026-07-20
- Summary:
  - Added replicated Power and MaxPower attributes.
  - Added Power initialization, clamping, replication notifies, and a dedicated player power bar widget.
  - Added `GE_PowerCharge` as a startup regeneration effect that slowly fills the Power bar over time.
  - Added `GE_PowerCharge_OnHit` to reward successful hits by charging the attacker's Power faster.
  - Added `GE_SpecialCost` so special abilities consume Power on activation.
  - Updated attack damage helper logic to optionally apply on-hit Power charge effects to the attacker.
  - Updated projectile hit logic to grant on-hit Power charge to the projectile owner after successful damage/hit react.
  - Updated player/enemy attack and special ability assets to use Power charge and special cost effects.
  - Supported multiple initial attribute effects on base characters for cleaner startup effect composition.
  - Updated UI widget bindings to include the new Power display.

## 30. Clean Up Gameplay Cue And Special Attack Assets

- Date: 2026-07-21
- Summary:
  - Updated hit react references to keep the cue name character-agnostic.
  - Cleaned up Phase and Wukong special attack ability/cue assets after the Power cost changes.
  - Adjusted projectile overlap handling while preserving damage, hit react, and Power charge flow.

## 31. Move Hit Reactions And Death To Event-Driven GAS Abilities

- Date: 2026-07-24
- Summary:
  - Added a server-initiated hit reaction ability activated by `Event.HitReact`.
  - Moved hit reaction montage, cancellation, and blocking state handling into the Gameplay Ability flow.
  - Kept `GC_HitReact` focused on cosmetic feedback such as VFX and SFX.
  - Refactored attack hit handling into `HandleConfirmedHit`.
  - Centralized target validation, duplicate-hit prevention, damage application, hit reaction dispatching, and source on-hit effects.
  - Preserved multiplayer authority by having the server dispatch the hit reaction event on the target ASC.
  - Updated melee and special attack assets to use the new confirmed-hit consequence flow.
  - Updated player and enemy startup abilities to include event-driven hit react and death abilities.
  - Kept death routed through the health change flow into `Event.Death`, letting `GA_GASP_Death` own terminal state, cancellation, and blocking behavior.
  - Simplified initial attribute initialization by validating the Ability System Component once before applying startup effects.

## 32. Fix Instigator Hit React Effects In Gameplay Cue

- Date: 2026-07-27
- Summary:
  - Updated the hit react cue flow to read particles and sound from the instigator's HitReactContainer instead of the reacting target.
  - Preserved the target as the actor receiving the hit reaction while letting the attack source define the impact feedback.
  - Adjusted `GA_GASP_HitReactByEvent` and `GC_HitReact` assets around the corrected cue parameter flow.
  - Cleaned up minor base character death comments and range helper formatting.

## 33. Expand Gameplay Cue And Impact Feedback

- Date: 2026-07-30
- Summary:
  - Added character-specific attack and hit impact cues for Phase, Wukong, and enemies.
  - Added Phase voice/audio feedback for special attack and projectile attack, including a dedicated projectile looping sound.
  - Added native special attack activation audio through `UGASP_SpecialAttack`.
  - Added native projectile audio support with an AudioComponent and configurable AudioEffect on `AGASP_BaseProjectile`.
  - Added Phase special attack VFX/voice cue tags.
  - Redirected the old Phase special sound cue tag to the new voice tag.
  - Added camera shake feedback to hit react.
  - Added a death gameplay cue burst with Blueprint-configured camera shake.
  - Updated Phase, Wukong, enemy, projectile, and hit react assets to use the new sound cue and particle feedback setup.
  - Reorganized third-party miscellaneous assets and replaced older shared cue assets with more specific per-character cues.

## 34. Add Third-Person Assets To Test Map

- Date: 2026-07-31
- Summary:
  - Imported default Third Person level prototyping assets under ThirdParty for test map iteration.
  - Added prototype meshes, grid materials, colorway instances, and supporting external actor/object data.
  - Updated TestMap with third-person blockout content to improve traversal and gameplay testing.

## 35. Refine Special Attack Feedback And Enemy Treasure Reset Flow

- Date: 2026-08-04
- Summary:
  - Split special attack local feedback into Blueprint-callable helpers for activation sound, fade-in, and fade-out effects.
  - Updated Phase and Wukong special attack assets to drive the new local activation/end feedback flow.
  - Added enemy respawn handling that hides the actor during the respawn delay, resets attributes, returns it to the start location, and restores visibility.
  - Broadcasted enemy respawn events so dependent gameplay actors can react when the guard returns.
  - Reworked treasure unlock handling to spawn its pickup on authority instead of keeping a hidden child actor.
  - Added treasure relock support when the guarding enemy respawns, including replicated open/close animation hooks.
  - Updated treasure, pickup, chest animation, player Blueprints, death ability, and TestMap assets around the refined interaction loop.

## 36. Add Steam Session Menu And Character Selection Flow

- Date: 2026-08-05
- Summary:
  - Enabled Steam online subsystem support with AdvancedSessions and AdvancedSteamSessions plugins.
  - Added Steam net driver config, AppId 480 setup, and default game map routing through SessionMenu.
  - Added a GASP AdvancedFriendsGameInstance to persist the selected character gameplay tag between menu and gameplay.
  - Added SessionMenu map and `WBP_SessionMenu` flow for creating, finding, joining sessions, and toggling Phase/Wukong selection.
  - Routed character selection through the player controller and stored the tag on PlayerState.
  - Updated `GASP_GameMode` to choose the default pawn class from the selected character tag.
  - Reset ASC state before respawning after character selection changes.
  - Replaced the old `BP_GameMode` setup with separate gameplay/menu GameMode assets.
  - Updated player controller and map assets around the session flow.

# *Apollo Justice: Ace Attorney: Retrial* Design Document (WIP)
---
![Retrial project logo](./Added%20assets/Images/titleLogo.png)
---
## Introduction
*Apollo Justice: Ace Attorney: Retrial*, abbreviated as *Apollo Justice: Retrial* or simply as *Retrial*, will be a romhack of the US ROM of *Apollo Justice: Ace Attorney* for the Nintendo DS. A romhack is a mod — or modification — of a game created by editing the source code. As a result, a romhack is typically a variation of an existing game with unique elements, rather than a wholly unique game[^1].

In addition to all the content from the original 2007 DS release, *Retrial* will contain original quality-of-life changes, scenes, chapters, and assets in order to greater capitalize on the original's ideas. Put a different way, *Retrial* will try to be a "definitive edition" of the DS version of *Apollo Justice: Ace Attorney*, made with the spirit and professionalism expected of the *Ace Attorney* franchise.

**In one sentence: *Retrial* will be an official-style improvement and expansion romhack of the DS version of *Apollo Justice: Ace Attorney*.**

As a romhack of an existing *Ace Attorney* entry, the premise will be the same as the rest of the *Ace Attorney* series: in a visual novel format, players control the protagonist, a lawyer, as they explore crime scenes and collect evidence, which they use to solve the murder mystery in court, exonerate the innocent defendant, and identify the real killer. Like usual, the setting is an alternate version of modern Los Angeles with heavier Japanese cultural influence.


## Goals
The goals of the *Retrial* project are as follows:

1. *Apollo Justice: Ace Attorney* is and has historically been a divisive game in popular opinion. We will emphasize the aspects that we consider the game's strong suits (atmosphere, well-defined identity, character dynamics, visuals, soundtrack, etc.); at the same time, we will work to understand both the game's flaws and what it was trying to accomplish in its weaker areas (character balance, mystery logic, excessively subtle writing, etc.). In doing so, **we hope that we can create a mod that *Apollo Justice* fans will enjoy and that those who don't like the original may be able to appreciate more.**
2. We hope to remind people why they love *Ace Attorney* by delivering memorable stories and characters.
3. As a non-profit, volunteer project worked on in our free time, **we hope to have fun, provide an opportunity for each other to practice and grow our respective skills (organization, programming, narrative, dialogue, and mystery writing, art, music, etc.), and become more familiar with the game development process.**


## Mechanics
As a romhack of *Apollo Justice: Ace Attorney*, *Retrial* will follow the standard *Ace Attorney* gameplay loop: players will follow the protagonist, defense attorney Apollo, as he proceeds through an "investigation phase" and a "trial phase." In the investigation phase, players will advance dialogue, make dialogue choices, examine objects from 2D and 3D perspectives, and present evidence to other characters in order to collect evidence and open new areas where they will repeat the loop to collect more evidence and open more areas. In the trial phase, players will defend their client by advancing text until they reach one of:

- a cross-examination, where the player must press the witness to find a statement to which they can present a contradicting piece of evidence
- a multiple-choice question, where the player must answer correctly to demonstrate their understanding of the case's logic and push the mystery solving forward
- a Perceive section, where the screen zooms in on the witness and the player must move the view around to identify where and when the witness has a "subconscious twitch" in reaction to a lie they're telling


## Additions
### Features
- [ ] Add title screen music, where there was previously silence
- [ ] Make investigation cursor change color based on whether an object has already been examined
- [ ] Add option to skip the Serenade video playback
- [ ] Add *Trials and Tribulations* music toggle for the flashback sections
- [ ] Add text backlog, activated with the Select button 


### Characters
- [ ] Clay, as retroactively described in *Phoenix Wright: Dual Destinies*, is an astronaut who will serve as Apollo's best friend


### Story and Dialogue
- [ ] A fifth case, titled **Truth and Justice**
- [ ] A comedic "Asinine Attorney" case, in which Phoenix is accused of murdering Charley the houseplant (worked on: Midnight)
  
As listed below, there will also be:
- About fifteen mini-episodes, called Secret Files, that focus on character dynamics and are accessed from the main menu
- Additional new scenes that are similar to the Secret Files but that are integrated directly into the main cases

**Turnabout Trump:**
- [x] Phoenix and Kristoph’s dinner conversation before 4-1
- [x] Apollo visiting Kristoph in prison right after 4-1, where as a retcon he sees Klavier for the first time

**Turnabout Corner:**
- [x] Ema and Phoenix’s first conversation in a long time
- [ ] Apollo, Trucy, Ema, and Wocky hanging out (worked on: @OnYourRight)
- [x] Edgeworth and Gumshoe visiting Wright and Co. Law Offices

**Turnabout Serenade:**
- [ ] Apollo, Trucy, and Lamiroir visiting Machi after 4-3 (worked on: AWD)
- [ ] Klavier inviting Apollo to his office after 4-3 to talk (worked on: Kringle)
- [ ] Apollo, Trucy, and Phoenix at the agency cooking (needs to be put into a scene)

**Turnabout Succession:**
- [ ] Klavier and Kristoph talking after Gramarye trial (worked on: piyo)
- [x] Valant before turning himself in
- [ ] Maya meeting Trucy (needs to be put into a scene)

**Truth and Justice:**
- [ ] *to be filled in later*

**Scenes inserted directly into the main game:**
- [ ] Apollo having a phone call with Clay right after 4-1 (needs to be put into a scene)
- [ ] The off-camera scene where Phoenix finally tells Apollo what happened (worked on: Matt)
- [ ] Apollo and Trucy talking in the hospital after the final 4-4 trial (needs to be put into a scene)
- [ ] Klavier apologizing to Phoenix (part of 4-5)

With the exception of Clay's inclusion, *Retrial* will be written from the perspective of 2007, as if *Apollo Justice: Ace Attorney*'s sequels, *Phoenix Wright: Dual Destinies* and *Phoenix Wright: Spirit of Justice*, had not yet released. *Retrial* is intended to address *Apollo Justice* as a game, not the *Apollo Justice* trilogy of games.


### Sprites


### Models


### Audio


## Changes
- [ ] Change Trucy's skin color to a darker shade to correct the planning error from the original game
- [ ] Fix typos
- [ ] Correct logical errors to the extent that is feasible
- [ ] Edit particularly out-of-character lines


## Tools
Since no known romhacking work has been done before on the DS version of *Apollo Justice*, some tools need to be developed to facilitate the development process. These include:

- [ ] plain text to *Apollo Justice*'s text encoding converter
- [ ] *Apollo Justice*'s raw image format to .png converter
- [ ] .gif to animation file converter


## Documentation
Documentation will be a core part of the *Retrial* project. It will take two forms:
- Documentation of our own methods for all relevant tasks
- Documentation of the game's internal workings, function of important addresses in RAM, etc.


---
[^1]: *Ace Attorney*, *Apollo Justice: Ace Attorney*, and all of its associated characters and assets, and all other rights belong to Capcom. 
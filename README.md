# ENGINE-VN
No LLMs were used in this project. Bullet points in markdown documents have existed before, during (and maybe after) the mass adoption of LLMs. I highlight this if for no other reason than to instill some confidence that all horrible decision are courtesy of me, and not some giant autocomplete machine.
## Abstract

This project is my attempt at a 2D game-engine, mostly built to enable:
- Point and click adventure games
- Visual novels

and with further work:
- 2D or 2.5D strategy games
- General applications

This project is my very first of something even remotely approaching this size, so you can imagine how slow, non-linear and sometimes downright stupid the development timeline will be.

## Architecture

At the core of this project is the idea that a programs running can be modified at runtime. This concept is by no means original, and in fact many modern game engines run this way.

The idea borrows a little from real life cities. Cities are organized as sprawls of roads that connect buildings together. To roads, the only thing that matters is the size of buildings, they have no knowledge of their inner workings. They understand that the buildings accept different cargo (some accept trucks, others take people, some both), and that's all they care about.

That's why the workings of a city do not significantly change if one of the buildings close down, remodel or change purpose. The roads and cars trudge on just the same.

This is, in esssence, what this framework is trying to achieve.

Its built of 2 main components:
### Core

This is the largely inflexible part of the architecture. It's entire job is:
- Tracking the state of the entire program
- Making sure appopriate CoreModules exist and have appropriate memory access
- Accepts CoreEvents and routes them according to certain rules to CoreQueues

In essence, it is the road system. It takes parcels, people (and everything else, the point is the payload is irrelevant), and routes it to the appropriate "street".

These "streets" are the CoreQueues. I'm tinkering with the idea of these being in the project at all, but they seem like a good idea given that it provides maximum flexibility (and even improved performance in cases where many different CoreModules accept the same type of payload).

CoreQueues contain the second main component:
### CoreModules

These are the flexible parts of the program, and the idea is that they, and only they, represent the functional units of the final program. Anything that happens in the final program, such as:
- Serialization
- UI/Graphics
- Sound (middleware and playback)
- Verification
- Version control

and in the case of something like a visual novel:

- User input
- Story graph
- Managing sprites (VRAM, RAM and compressed archives of sprites)
- countless other events...

will take place inside a module. Technically, the entire program could be one big module, or every single function could be a separate module. This generalizes the concept of work in a program, and could theoretically allow for runtime expansion of functionality.

An example might be modules that are dynamically linked, or something like plugins. They could just slot into a running program, registering their events and corresponding with appropriate payload immediately.

A few other key components of the project architecture are:
### CoreState

This concept allows for the Core to know which state the program is in. For example, you may want a different state for a main-menu of a video game, and it's main running loop. This means you have a minimal memory footprint and minimal overhead when the game is just stuck in the main menu, waiting for player input. In this case, the only modules present would be:
- An input module (it can be a different module for keyboards and for touchscreens, for example)
- A plethora of UI modules (buttons, text displays, video frames)

In such a case, something like the settings button would simply fire off a CoreEvent that lets the Core (and therefore, the CoreStateManager) know that we need to bring up the Settings state of the program.

This would then change which modules exist, refitting the program to accomodate a settings panel.

This would repeat for any change in functionality.

A CoreState simply holds a blueprint of the kinds of modules that exist in it, the amount of CoreQueues and what events they accept, along with a possible serialization bundle that saves some previous state (a MainGame state may serialize information about the player in a save).

A drawback of this is, of course, performance. It's probably cheaper to just let the UI module handle its own changes, instead of invoking a separate module for each separate element on the screen.

This is, hopefully, the clever bit of this architectural nightmare: you can simply program how you see fit. If you want to have the entire UI system be one big module that can more efficiently manage memory when changing states, you can do so. In fact, as stated before, you can just have one state, and then have a giant module that does everything a CoreStateManager would manage.

In essence, the only overhead this project should ever introduce is routing and the initial registration of a module. A CoreModule will have to let you know what events it can take in, and since all event declarations have to live on the heap (theyre dynamic), this means there will be a minor performance concern there. Also, routing an event to a relevant queue after the module is done with its work is another concern.

One possibility is having a packaging stage at the end of a build, much how modern game engines do it. When the developer is done with their game or program, they can package the program into asset files and a new executable that contains very barebones runtime utilities to just allow the modules to interoperate. In that case, much of the flexibility goes away, but so does the routing overhead (we can simply convert all the routing functionailty of a Core into simply the codeflow of how modules call other module functions and so on).

Some inbetween may be possible. There are many future architectural plans, and I may write another .md file (or a plethora of them) to lay out my ideas for possible future expansion on this concept.

## Summary

To summarize, this is an attempt at an extremely flexible (sickeningly overengineered) general program framework/game engine that will, for now, be geared towards very simple games (as stated above in the Abstract).
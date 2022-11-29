# TODO.md

Not every TODO comment can fit in just one line - or even several. Some TODOs
are too overarching and general to the project to fit in one file or scope.
Thus, this file exists to extract some bigger TODOs out of the source files.

## Resource Streaming

Addons may include dozens of megabytes of resources. It would be wasteful to
keep all of these resources in memory. As resources are loading, these streams
of data could be used to create fake low-detail representations of textures, or
audio could cut off until it is ready to play. This would allow lower-end
devices to lift the burden of loading resources during start-up, and allow
seamless integration with servers, making mods download resources from the
server while the game is running.


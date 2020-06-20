# Torque 3D contribution guidelines

So you want to help Torque out by contributing to the repo? That's awesome!
We just ask that you'd give this document a quick read to get yourself familiar with the process.
Do you want to [request a feature](#request-a-feature)?
Create a [pull-request](#create-a-pull-request) to contribute your own code to the engine?
[Report an issue](#report-an-issue) you've discovered?

## Report an issue

Before you report an issue with the engine, please [search](https://github.com/TorqueGameEngines/Torque3D/issues) and quickly make sure someone else hasn't obviously reported it.
If you're not sure if it's the same issue, go ahead and comment on it!
Once you're certain you've found a new issue, hit the [big green button](https://github.com/TorqueGameEngines/Torque3D/issues/new) and please include the following information:

 * Your platform and compiler, if you're not using a precompiled binary
 * A description of what currently happens, and what *should* or *should not* happen
 * Steps to reproduce the issue, if _at all_ possible
 * If it's related to graphics, your GFX card and driver details.

## Create a pull-request

We ask that potential contributors read our [pull-request guidelines](#pull-request-guidelines) before opening a PR.
We also have some [code style guidelines](https://github.com/GarageGames/Torque3D/wiki/Code-Style-Guidelines).
Here's a quick guide to the branches in this repo that you might think of targeting a PR at:

#### The master branch

The repository's `master` branch is where we make releases.
It's supposed to be stable at all times - or as stable as we can make it - and only gets updated when a new version comes out.
Any pull-requests to the master branch will have to be rejected - sorry :(.

#### The development branch

The `development` branch is where most development happens.
It is the target for the next 'middle' version of the engine (the 6 in 3.6.1, for example).
This means we will add new features, and refactor code if it doesn't break existing games made with the engine _too_ much*.
Most pull requests to `development` can be accepted if we like your code - unless they would potentially break users' games.

*How much is _too_ much is for the Steering Committee to decide.

#### The development-3.6 branch

The `development-3.6` branch is where we will make bugfixes and small patches to the previous stable 'middle' version.
This branch is where the 'small' versions will be created - 3.6.2, 3.6.3, etcetera.
So if you have a bugfix or tiny enhancement that doesn't require anyone to change their game, it'd be best appreciated in this branch.

#### TLDR

Don't make any PRs to `master`.
PR new features and large fixes/refactorings to `development`.
PR bugfixes to `development-3.6`.

### Pull-request Rules

Pull requests not adhering to these rules cannot be accepted, so pay attention!

* Obviously, your contribution cannot contain any code that is not legally compatible with Torque 3D's MIT license.
* Contributions must adhere to our [code style guidelines](http://wiki.torque3d.org/coder:code-style-guidelines).
* Pull-requests against the master branch cannot be accepted. All requests must go to development, or an appropriate topic or maintenance branch.

In many cases, if any of these rules are breached, we will first ask the contributor to resubmit their pull request, or add commits to it that resolve our issues. In exceptional cases (i.e., we really really like your work), a committee member may perform that work themselves.

### Pull-request Guidelines

Here are some of the things we look for in a great pull request. These aren't hard-and-fast rules, but following these guidelines will increase the chances that your request is pulled!

* Our favourite requests are ones that work directly towards the goals laid out in our roadmap. We are more likely to help out and fix slightly broken pull requests if they align with our goals, and chances are your request will move faster through our process.
* Each pull request should be focused and concise. If it has a very clear intent and a small set of changes towards a specific goal, it's easy for us to decide whether we want it, and to then test it and make sure it works as advertised and doesn't break things.
* If you're fixing a bug, we need you to provide steps to reproduce it so we can verify that exists and that your patch actually does fix it. We'd also appreciate platform and compiler information.
* We like each pull request to have a reasonable revision history - not too many small commits with typo fixes, for example. Sometimes, we may ask contributors to rebase large numbers of commits into a single commit before the request is pulled.

### Version Policy

We maintain an **X.Y.z** version scheme similar to that of [Semantic Versioning](http://semver.org/). However, since our API is less well-defined, the table below describes what we mean by the three version number components.

*Note that this new versioning policy is different to the one adopted by the first and second Steering Committees, and applies only to engine versions 3.5.2 and above.*

| Version | Description |
| --- | --- |
| **X** Major version number | The major version number denotes a single version of our client-facing API, which refers to the script and editor capabilities exposed to binary-only users of the engine, as well as major parts of the internal C++ API, such as the class hierarchy. |
| **Y** Minor version number | The minor version number refers to the set of features in a given API. Across a minor version number change, we may refactor code, fix bugs, or introduce new features, but we will not make breaking changes to existing ones. |
| **z** Patch number | Patches denote minor updates to stability or correctness that do not change the engine API in a significant way. |


## Request a feature

We ask that all feature requests be discussed in the [Torque3D forums](https://forums.torque3d.org/) or our [Discord](https://discord.gg/wz2ZrRH)
If your idea is popular, we'll hear of it and probably make an issue ourselves, if we agree.

Even better - don't request a feature, start working on it!
This engine isn't going to improve itself ;).

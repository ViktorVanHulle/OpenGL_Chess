# PROG2002 Assignment Autumn 2022 

## Introduction

This assignment is an extension of the labs where some of the concepts studied
will be used. The assignment will be graded as _pass/fail_, and passing is
compulsory for attending the exam in December 2022 and the re-sit exam in
August 2023. In addition, the assignment needs to be carried out *individually*.

The teaching team won't answer any technical question related to the
assignment, however, questions related to the clarification of the  
assignment's requirements can be taken during the comig labs sessions, or
directly by e-mail to rafael.palomar@ntnu.no.

Keep your own backups, the teaching team won't take any responsibility for
anything happening to the repositories infrastructure. In the unlikely event
that something happens, the teaching team will indicate how to proceed with the
repositories.

The description of the assignment and the issues are subject to change if, for
instance, an errata is detected or any point need to be clarified. In such
event, the teaching team will communicate the change by e-mail and the students
will do the change in the repository accordingly.

Make sure you read an understand the following points as your assignment needs
to comply with them in order to pass the assignment.

## Keep clean repositories

The repositories shall not contain any file that can be generated from your
source code or your CMake project definitions. This includes generated binary
files (libraries, executables, object files, etc.), and files generated for your
develoment environment (e.g., Visual Studio files). An exception to this rule
are the resource files (e.g., texture images) needed to run the application. In
addition, the repository shall not contain any file that it is not needed in the
project. 

Commit messages need to relate to the content of the commit and be
self-explanatory. In addition, commits shall be written using professional
language; use of non-professional language (irony, jokes, disrespectful
language, etc.) will lead to fail the assignment. The same holds for all the
content of your repository. 

## The delivered software must configure, compile and run flawlessly in a neutral platform 

For your project to get a pass, the project must configure, compile and run
flawlessly in a multi-platform way (e.g., not using code specific to either
Windows, Linux or MacOS, keeping capitalization consitency). "It works on my
machine" won't be enough to consider the assignment as passed. Keep in mind the
following points to help you on this:

  - Your project should have a root-level `CMakeLists.txt`.
  - Make sure you don't include platform-specific code. `__debugbreak()` or
    `#pragma once` are examples of Windows-specific code that won't be allowed.
  - Before the delivery, make sure you clone your own repository afresh, and try
    to do the configuration, building and running tests needed for verification.
  - Make sure you respect the capitalization of file names. Windows will not
    distinguish between lower/upper-case letters, but other platforms will.
  - Make sure any file resources yout project may need will be deployed by the
    build process in the right location so they can be found by your application.
  - Make sure you don't hard-code paths, most likely your code will only work on
    your machine.
  - The evaluated code must be integrated in the `main` branch of the repository
    assigned to you. No other branch and no other repository willb e considered
    for the evaluation.
    
### Using the continuous integration pipeline in your repository

In order to facilitate checking the compilation of your project, your repository
comes with an integrated CI/CD pipeline that will test your changes in a Ubuntu
container and let you know if the building process succeeds. The use of this is
optional and it should be considered as an extra help, not as a required
infrastructure to complete the assignment.

The repositories are configured so you cannot change directly the main branch.
The recommended approach is that (1) you create a new branch for development
(this can be e.g., a single `development` branch or an ephimeral topic branch
e.g., `feature/create_main_application`), (2) you push the changes on that
branch to your repository, and (3) you create a merge request. As long as you
keep changing your branch (even force-pushing changes) your merge request wilbe
tested. Finally, when you are done, you can merge the branch to `main`.

## External libraries needed to build the software must be includes as git-submodules

As w e have been doing for the assignments, the external libraries needed to
build the software must be included in the project by means of git submodules.
Don't include external libraries directly into the assignment repository. The
external libraries to use are the same we have used in the labs.

## Allowed material and plagiarism

To carry out with the assignment you can make use of the material you have
developed during the assignments, as well as the referenced material in the
issues detailed in the labs. No other material is allowed to be used.

## Organization and delivery of assignment

The assignment is organized around a set of issues that must all be completed
successfully to pass. Upon completion of every individual issue, the issue must
be closed as confirmation that a particular issue has been completed. Issues not
closed won't be considered completed even if the code is completed: Be aware!
The issues don't need to be completed in order. 

# Assignment description

The task of the assignment is the creation of a simple chees-like appliction
that will display a board with two sets of cubes (one per player) that will be
initially arrangedi n a board (8x8 by default) having different types of tiles;
unlike chess, we only have one type of unit. The pieces can be moved anywhere in
the board, provided that there is not any other unit occupying the same tile.
The application must allow to move the camera around the board, in a circular
fashion (looking to the center) and display a selector (always visible) that
will highlight units as it moves though them. The application will provide
visual help to move a unit to another place; in this case the unit will be
highlighted in a different color until it moves, then the unit will take its
original color or the selector color if it applies.

![TaskDemo](TaskDemo.gif)

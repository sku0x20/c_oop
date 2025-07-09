# C OOP

this sample demonstrates

- programming in object-oriented fashion
- doing london style tdd

its opinionated approach to do

- polymorphism
- oop
- tdd

## definitions

> polymorphism

- interface based
- should follow LSP
- i.e., don't do type switching
- type enum(mimicking sealed classes) or int can be added per-case basis but should be avoided; consumers should code
  against interface.

> oop

- non imperative style
- organizing code into objects
- calling functions/methods on objects
- control flow follows creating objects and calling their methods to do the job.

> tdd

- london style tdd
- test against interface
- test the behavior
- mocks are just DRYied fakes \*

## conventions

- headers are not interfaces
- struct defines types
- struct defines interfaces
- types have data as well as methods
- methods are function pointers that take a struct pointer of the type itself as the first argument usually named 'this'
- if a function operates on struct, it has to be defined as a method
- all the data is assumed to me hidden/private
- clients should use getter methods
- struct defines interface
- interfaces have only methods
- interfaces cannot be initiated
- types have minimum one constructor that initializes and returns the object
- objects should be initialized by the constructor
- initialization should take care of method mapping
- each type has a free method
-

## resources

- https://youtu.be/bZO0A1tj2MI

## limitations

- cannot initiate objects on the stack

# C OOP

an opinionated approach to do

- polymorphism
- oop
- tdd

in c

## definitions

> polymorphism
- interface based
- should follow LSP
- ie. don't do type switching 
- type enum(mimicking sealed classes) or int can be added on case basis but should be avoided; consumers should code against interface.

> oop
- non imperative style
- build on idea of message passing style
- organizing code into objects
- calling functions/methods on objects
- control flow follows creating objects and calling their methods to do the job.

> tdd
- london style tdd
- test against interface
- test the behavior
- mocks are just DRYied fakes *

## conventions
- header are not interfaces
- struct defines types
- struct defines interfaces
- types have data as well as methods
- methods are function pointers which take struct pointer of type itself as first argument usually named 'this' 
- if a function operates on struct it has to be defined as method
- all the data is assumed to me hidden/private
- clients should use getter methods
- struct defines interface
- interface have only methods
- interfaces cannot be initiated
- a types is said to implement an interface when it embed interface as first member
- each type has a constructor which takes care of mapping methods and initializing the object instance

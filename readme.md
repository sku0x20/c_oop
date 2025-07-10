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

> types

- struct defines types
- types have data as well as methods
- methods are function pointers that take a struct pointer of the type itself as the first argument usually named 'this'
- if a function operates on struct, it has to be defined as a method
- all the data is assumed to me hidden/private
- clients should use getter methods
- types have minimum one constructor that initializes and returns the object on heap
- objects should be initialized by the constructor
- each type has a free method
  - it frees the resources as well as itself
- methods' implementations should make 'this' as a const pointer
  - better to take every pointer parameter as a const pointer

> interfaces

- headers are not interfaces
- struct defines interfaces
- typical vtable implementation

```c
struct interface {
  void* impl; // opaque pointer to impl. struct instance
  vtable* vtable; // vtable pointer to impl.
}

struct impl{
  interface interface(impl* this)
}
```

- vtable is a pointer for memory optimization reasons
  - all implementation instances can share the same vtable struct instance
  - though one additional lookup
- interface struct is always returned by value, never pointer
- interface have methods which delegate to methods in vtable passing the impl pointer

## limitations

- cannot initiate objects on the stack
  - else free won't work

## resources

- zig allocator interface & implementations
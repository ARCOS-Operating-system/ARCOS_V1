# ARCOS Schema Definition Language (SDL)

The Schema Definition Language (SDL) provides a concise, strongly-typed, declarative format to define ARCOS object interfaces. These schema files drive interface enforcement, code generation, and introspection support across the OS.

## Purpose

* Define object types and their callable methods
* Enforce type-safety and versioning
* Enable interface discovery and tooling

## Basic Syntax

```sdl
object fs.File {
    version 1.0

    method read(offset: UInt64, size: UInt32) -> Bytes
    method write(offset: UInt64, data: Bytes) -> UInt32
    method close() -> Void
}
```

## Language Elements

### Object Declaration

```sdl
object <module.Name> {
    version <semver>
    ...
}
```

* Full name must include namespace/module prefix.
* Versioning is optional but recommended.

### Method Signature

```sdl
method <name>(<args>) -> <ReturnType>
```

* Arguments and return values must use supported types.

### Types

* Primitive: `Bool`, `Int32`, `UInt64`, `String`, `Bytes`, `Void`
* Composite: `List<T>`, `Map<K, V>`, `Optional<T>`
* User-defined with `type` blocks

### Custom Type Definitions

```sdl
type fs.Entry = {
    name: String
    inode: UInt64
    is_dir: Bool
}
```

## Features

* Inline documentation (planned)
* Optional/deprecated fields (planned)
* Compile-time linting and validation
* Auto-generation of IPC bindings

## Toolchain Support

* `arcos-sdlc` — compiler and validator
* `arcos-introspect` — service to query available object types and versions
* IDE plugins (future)

## Future Extensions (V2)

* Interface capabilities
* Annotations (`@doc`, `@capability`) for metadata
* Contracts for runtime validation
* SDL package registry and schema discovery

---

SDL is the foundation for structured, extensible, and introspectable system APIs in ARCOS. Interfaces are not ad hoc, they are schema-first and tooling-friendly.

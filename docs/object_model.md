# ARCOS Object Type System

ARCOS replaces traditional file-based I/O and syscalls with a **typed object model**. Every kernel-visible entity is a structured object with well-defined interfaces, message endpoints, and capability gates.

## Core Principles

* All system entities are objects.
* Objects are **typed** — the interface is declared and enforced.
* Capabilities grant access to methods on objects.
* No unstructured byte streams or generic `read()`/`write()` calls.

## Object Type Declaration

Each object type declares:

* A **type name** (e.g., `net.Interface`, `fs.Dir`, `crypto.Key`)
* A set of **message handlers** (typed IPC endpoints)
* Its **capability classes**

```text
object net.Interface {
    method up() -> Result
    method down() -> Result
    method get_status() -> InterfaceStatus
}
```

## Object Lifecycle

* Objects are created by system services (e.g. `netd`, `fsd`).
* When created, the caller receives a capability reference.
* Objects live in per-process **object trees** (private namespaces).
* Objects may be cloned, revoked, or passed to other services (if allowed).

## Object References

* Object references are opaque handles bound to capabilities.
* No global namespace or path lookup.
* Introspection or discovery requires dedicated system services.

## Example Object Types

### `fs.Dir`

```text
method list() -> [fs.Entry]
method open(name: String) -> fs.File
```

### `crypto.Key`

```text
method sign(data: Bytes) -> Signature
method verify(data: Bytes, sig: Signature) -> Bool
```

### `display.Window`

```text
method draw(cmd: DrawCommand)
method close()
```

## Capability Binding

Each method on an object requires the appropriate capability.
Objects may expose subsets of their interface to different holders.

## Object Tree & Ownership

* Every process has a private object tree.
* Parent-child relationships are tracked.
* Objects are automatically cleaned up on process exit.

## Future Extensions (V2)

* **Interface versioning** and negotiation
* **Dynamic interface reflection**
* **Structured errors** and method contracts
* **Schema definition language (SDL)** for objects

---

The ARCOS Object Model is foundational to security, clarity, and modularity. No files, no syscalls only typed, inspectable, and composable system objects.

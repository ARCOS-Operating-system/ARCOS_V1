# ARCOS Capability System

## 1. What is a Capability?

A capability is an unforgeable, secure reference to a system object. It represents both access and authority. Unlike traditional access models (e.g., UID/GID), capabilities are explicitly granted and enforced at the kernel level.

### Structure Example

```sdl
type sys.Capability = {
    object: ObjectRef
    rights: List<String>
    sealed: Bool
}
```

* `object`: the reference to the object (file, service, process, etc.)
* `rights`: explicit permissions (e.g., read, write, invoke)
* `sealed`: indicates non-transferability

---

## 2. Capability Operations

### Grant

* Provide a capability to another process
* Requires a valid capability with delegation rights

### Revoke

* Remove access by marking the capability or invalidating it system-wide

### Seal

* Mark as non-transferable to prevent delegation

### Inspect

* Allows introspection of a capability's metadata, rights, or status

---

## 3. Capability Creation

* Only core kernel or system-trusted services can create new capabilities.
* Capabilities are obtained via:

  * Process inheritance (from parent)
  * Init-time manifest
  * Explicit request from system service

---

## 4. Enforcement

* All method calls on objects must present a valid capability.
* No fallback to user/group-based permissions.
* No global object table or namespace: access is by reference only.

---

## 5. Revocation Models

### Epoch-based Revocation

* Each object has a version or epoch. Revoking it increments the epoch, invalidating all capabilities.

### Handle Tracking

* Objects maintain internal reference maps for capability owners. Revoking removes specific handles.

### Capability Groups

* Capabilities can belong to a group ID. Revoking the group invalidates all related caps.

---

## 6. Serialization & Transfer

* Capabilities are not serializable as plain data.
* Must be transferred via secure message-passing channels.
* Transfer tables are managed by the kernel per process.

---


ARCOS capabilities replace ambient authority with precise, object-bound access. They provide secure, fine-grained, revocable, and inspectable permissions across the OS, forming the foundation for isolation, service composition, and security.

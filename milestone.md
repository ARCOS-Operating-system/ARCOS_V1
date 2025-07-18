# ARCOS\_v1 Milestone Plan

ARCOS\_V1 is the first working snapshot of the ARCOS operating system. It demonstrates its core philosophy: capability-based access control, service-oriented architecture, and object-based interfaces.

---

## Goals

Build a minimal, bootable OS with:

* Core capability model
* Basic process spawning and management
* In-memory file service
* Init system based on service manifests

---

## Core Components

### 1. Microkernel Core

* Lightweight message-passing kernel
* Basic scheduling (round-robin or FIFO)
* Capability dispatch enforcement

### 2. Init System

* Parses and loads service manifests
* Spawns first services
* Grants sealed capabilities

### 3. Filesystem Service

* In-memory FS
* Exposes `fs.Directory`, `fs.File` via SDL
* Access only through granted capabilities

### 4. Process Manager

* Manages PIDs and running processes
* Implements `sys.ProcessManager`
* Supports spawn/kill/list

### 5. Capability System

* Kernel enforcement of rights
* Transferable and sealed caps
* Secure IPC with cap delivery

---

## SDL Interfaces Required

* `sys.ProcessManager`
* `fs.Directory`, `fs.File`
* `sys.CapabilityManager` (internal only)
* `log.Logger` (optional)

---

## Demo Scenario

1. ARCOS boots kernel
2. Init loads manifest:

   * `filed` (file service)
   * `logd` (logging)
   * `testproc` (a user service)
3. Init grants capabilities:

   * `filed` gets raw FS access
   * `testproc` gets sealed `fs.Directory` cap
4. `testproc` performs reads on its granted files

---

## Directory Layout

```
/kernel/
  boot/
  scheduler/
  cap/
  ipc/
  init/
  process/
  vfs/

/user/
  services/
    logd/
    filed/
    testproc/

/manifests/
  filed.manifest
  testproc.manifest

/docs/
  capabilities.md
  init.md
  service_manifest.md
  sdl.md
```

---

## Excluded From v1

* Networking
* GUI/display
* Persistent storage
* Distributed object support
* Package manager

---

ARCOS\_v1 forms the reference implementation and testbed for ARCOS' unique capability-first object model. Later milestones will expand horizontally into distributed services, GUI layers, and real-world application environments.

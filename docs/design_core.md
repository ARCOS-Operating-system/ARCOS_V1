# ARCOS

**ARCOS** — Asynchronous, Reactive, Capability OS

> Fast. Composable. Typed. Designed for a post-POSIX world.

## Index

* [1. Philosophy](#1-philosophy)
* [2. Architecture Overview](#2-architecture-overview)
* [3. Object Model](#3-object-model)
* [4. Capability System](#4-capability-system)
* [5. Messaging & IPC](#5-messaging--ipc)
* [6. Init & Service Model](#6-init--service-model)
* [7. Reactive Core Runtime](#7-reactive-core-runtime)
* [8. Filesystem & Storage](#8-filesystem--storage)
* [9. Distributed Design](#9-distributed-design)
* [10. User Interface Architecture](#10-user-interface-architecture)
* [11. Deployment & Immutability](#11-deployment--immutability)
* [12. Glossary](#12-glossary)

---

## 1. Philosophy

ARCOS is not a UNIX clone.
It is built from first principles, embracing:

* Explicit typed object models (not files)
* Pure capability-based security (not UIDs)
* Message-passing (not syscalls)
* Reactive, event-oriented core
* Immutable, declarative system state

The system is understandable, modular, secure by construction, and designed for distributed environments.

We reject POSIX, systemd, and "everything is a file".
We accept clarity, composition, and contract-driven design.

---

## 2. Architecture Overview

Core Components:

* **Microkernel** — Minimal privileged core; message-passing only.
* **Init (PID 1)** — Declarative, manifest-based service tree spawner.
* **Object Runtime** — Typed object model, reference and interface-based.
* **Capability Engine** — Security and object access control.
* **Reactive Scheduler** — Event-loop based runtime for async behavior.
* **Filesystem Layer** — Immutable, versioned, and content-addressed.
* **Network Core** — Namespaces and services are distributed by default.

---

## 3. Object Model

* All system entities (files, sockets, GUIs, processes) are typed objects.
* Interfaces are explicit; objects define capability-accessible methods.
* Inspired by: EROS, CapROS, seL4 object models.
* Objects are managed in per-process object trees.

---

## 4. Capability System

* No global UIDs, GIDs, or ACLs.
* Every access is via an unforgeable capability token.
* Capabilities are reference-like, non-transferable unless explicitly allowed.
* Services may mint, grant, or restrict capabilities.

---

## 5. Messaging & IPC

* No syscalls.
* All system interaction via async message-passing.
* Messages are typed and versioned.
* IPC channels are object-bound; only holders of the right capability can message an object.

---

## 6. Init & Service Model

* Init is PID 1. It:

  * Loads a static manifest
  * Spawns services in dependency order
  * Supervises and restarts as configured
* Services define:

  * Name
  * Executable path
  * Dependencies
  * Restart policy

---

## 7. Reactive Core Runtime

* The OS core is event-driven.
* No traditional threads or blocking I/O.
* Each process runs inside an event loop.
* Kernel delivers messages, events, and timers to each object.

---

## 8. Filesystem & Storage

* Immutable by default.
* Every file, config, binary is content-addressed.
* Versioned system images and per-user data layers.
* Inspired by: NixOS, Git, Btrfs.

---

## 9. Distributed Design

* Objects can be remote.
* Namespaces are network-transparent.
* All services may live locally or across the net.
* Locality-aware resource dispatch is handled by the runtime.

---

## 10. User Interface Architecture

* GUI is sandboxed, first-class, but completely decoupled.
* UI runs as a message-driven service.
* No core assumptions about display or input.

---

## 11. Deployment & Immutability

* System is deployed as an immutable graph.
* Services and objects are updated atomically.
* Rollbacks are first-class operations.
* No mutable /etc, /var by default.

---

## 12. Glossary

* **Capability** – A reference token that grants access to a system object.
* **Manifest** – A static declaration of services and dependencies for init.
* **Object** – A typed entity with defined message-handling interfaces.
* **Service** – A managed process with lifecycle controlled by init.
* **Reactive** – Event-driven, non-blocking behavior.
* **Content-addressed** – Identified by hash, not path.

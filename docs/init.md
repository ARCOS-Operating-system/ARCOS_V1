# ⚙️ ARCOS Init System (PID 1)

ARCOS Init is the first userland process, PID 1. It is responsible for reading the boot manifest, resolving dependencies, launching system services, and supervising them throughout runtime.

## Boot Flow

```text
[Kernel Starts]
       ↓
[Init (PID 1) runs]
       ↓
[Reads /system/init/boot.service]
       ↓
[Parses services into dependency graph]
       ↓
[Topological sort → launch order]
       ↓
[Spawns services, monitors state]
       ↓
[Event loop: watch + restart + supervise]
```

## 📋 Responsibilities

| Phase                  | Description                                                                                                   |
| ---------------------- | ------------------------------------------------------------------------------------------------------------- |
| **Parse DSL**          | Load and validate manifest. Errors include duplicate service names, undefined dependencies, or syntax issues. |
| **Dependency Graph**   | Build a DAG from `depends_on`. Detect and reject cycles.                                                      |
| **Capability Minting** | Each capability token is issued at launch and scoped per object type and optional path.                       |
| **Service Launch**     | Fork and execute each service with defined `path`, `args`, and capability handles.                            |
| **Supervision Loop**   | Init tracks each service. Handles exits, crashes, and restarts based on `restart` policy.                     |
| **State Object**       | Init publishes internal status object (e.g., `Init::status`) accessible via capability.                       |

## Failure Modes

* Manifest parse failure: **boot aborts** with diagnostics.
* Undefined or missing binary: **service is skipped** and logged.
* Dependency cycles: **boot aborts**.
* Service crash: handled based on restart policy. Loops are rate-limited.

## Security Model

* **No ambient capabilities**: all access must be explicitly granted.
* **Per-service namespace isolation**: services do not share filesystem or object graph roots unless configured.
* **Init owns and passes capabilities** securely at startup.

## Restart Policies

* `always`: restart unconditionally
* `on_failure`: restart if exit code ≠ 0
* `manual`: do not restart automatically
* `never`: do not restart

## Future Directions (V2)

* `healthcheck` IPCs for readiness probes
* Dynamic manifest reload (`Init::reload()`)
* Hooks for audit logging and sandbox policy
* Support for lazy/deferred services

---

Init is minimal by design, declarative, and completely predictable, a stable foundation for the ARCOS object system.

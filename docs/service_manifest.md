# ARCOS Service Manifest DSL

ARCOS defines its system services through a custom, minimal DSL that reflects its object-capability philosophy, allowing precise declaration of process behavior, dependencies, and access rights.

## Overview

Service manifests are parsed by the Init system (PID 1) at boot. They define:

* What services to launch
* In what order
* With what arguments
* With what capability-based permissions
* Under which restart policies

## Example Manifest

```ARCOS
service netd {
    path "/system/bin/netd"
    args ["--config", "/config/net.yaml"]
    capabilities {
        network.interface.configure
        fs.read "/config"
    }
    restart always
}

service authd {
    path "/system/bin/authd"
    depends_on [netd]
    capabilities {
        crypto.sign
    }
    restart on_failure
}

service gui {
    path "/system/bin/gui"
    depends_on [authd]
    capabilities {
        display.draw
        input.read
    }
    restart manual
}
```

---

## 🔤 Grammar & Syntax

| Field          | Description                                         |
| -------------- | --------------------------------------------------- |
| `service NAME` | Declares a uniquely named service                   |
| `path`         | Path to the immutable service binary                |
| `args`         | Optional list of CLI args (strings)                 |
| `capabilities` | List of granted capabilities (optionally scoped)    |
| `depends_on`   | Optional list of service names to wait for          |
| `restart`      | One of `always`, `on_failure`, `manual`, or `never` |

### Notes

* Services are launched in topological dependency order.
* Capabilities are passed as secure references, not strings.
* Init logs service spawn success/failure, exit code, and restart attempts.
* Errors in parsing or cyclic dependencies abort boot with diagnostics.

## Capability Spec

Capabilities follow the pattern:

```
namespace.action [optional_scope]
```

Examples:

* `network.interface.configure`
* `fs.read "/config"`
* `crypto.sign`

The capability runtime enforces these at object-boundaries. There is no fallback or escalation path.

---

## Manifest Location & Loading

Manifests are stored in the immutable system image:

```
/system/init/boot.service
```

A future version may support layered manifests for user services or overrides.

---

## Future Features (TBD) (V2)

* `timeout` declarations for startup grace periods
* `healthcheck` command or message interface
* `env` support for static key-values
* `mount` and `namespace` declarations

---

This DSL is designed to be minimal, verifiable, and secure by construction — in line with ARCOS’s post-POSIX model.

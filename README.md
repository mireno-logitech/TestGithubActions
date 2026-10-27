# Click Counter – GitHub Actions sample

A tiny native Win32 C++ app: a window with a **Click me** button and a `Count: N` label that increments on every click. The point of the repo is to demonstrate GitHub Actions.

## Layout

| Path | Purpose |
|------|---------|
| `src/main.cpp` | Win32 window, button and label |
| `src/counter.h` | GUI-independent counter logic |
| `tests/` | Console unit tests for `Counter` |
| `CounterApp.sln` | Visual Studio solution (x64, Debug/Release) |

## Build locally

Requires Visual Studio (or Build Tools) with the C++ desktop workload.

```powershell
msbuild CounterApp.sln /p:Configuration=Release /p:Platform=x64
.\bin\x64\Release\CounterTests.exe
.\bin\x64\Release\CounterApp.exe
```

## Workflows (`.github/workflows/`)

| Workflow | Trigger | What it does |
|----------|---------|--------------|
| `ci.yml` | push / PR to `main` | Builds Debug + Release (matrix), runs unit tests, uploads the exe as an artifact |
| `codeql.yml` | push / PR to `main`, weekly | CodeQL C/C++ security analysis (results under Security → Code scanning) |
| `release.yml` | tag `v*` or manual dispatch | Builds, tests, zips the exe and publishes a GitHub Release |

To cut a release:

```powershell
git tag v1.0.0
git push origin v1.0.0
```

<!-- CI trigger test -->

# Design Pattern Overview

[![CI](https://github.com/errowdrigorena/DesignPatternOverview/actions/workflows/ci.yml/badge.svg?branch=master&event=push)](https://github.com/errowdrigorena/DesignPatternOverview/actions/workflows/ci.yml?query=branch%3Amaster+event%3Apush)
[![Coverage](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/errowdrigorena/DesignPatternOverview/master/coverage-badge.json)](https://github.com/errowdrigorena/DesignPatternOverview/actions/workflows/ci.yml)

> **Este repositorio es el material de código de un curso.**
> Su valor real está en el curso que lo acompaña, no en explorarlo de forma aislada.

## ¿Qué hay aquí?

Implementaciones en C++ de los 23 patrones de diseño clásicos del Gang of Four, más el pseudo-patrón Simple Factory.
Cada patrón incluye:

- Una versión **clásica** fiel al GoF original (herencia, polimorfismo virtual).
- Una o varias versiones **modernas** que aprovechan C++20/23 (concepts, ranges, `std::function`, CRTP, *deducing this*...).
- Algunos patrones incluyen además una versión con **Boost**.
- Tests automatizados con Google Test para cada variante.

### Patrones incluidos

| Creacionales | Estructurales | De comportamiento |
|---|---|---|
| Simple Factory | Adapter | Chain of Responsibility |
| Factory Method | Bridge | Command |
| Abstract Factory | Decorator | Interpreter |
| Builder | Facade | Iterator |
| Prototype | Flyweight | Mediator |
| Singleton | Proxy | Memento |
| | | Observer |
| | | Strategy |
| | | Template Method |
| | | Visitor |

### Tecnología

- **C++23** — el estándar más moderno disponible en el momento de creación.
- **CMake** con presets para configurar el proyecto.
- **Conan** para gestión de dependencias (Boost, Google Test).
- **GitHub Actions** para integración continua y reporte de cobertura.

## Estructura del proyecto

```
<Patron>Pattern/
  include/
    <Patron>Pattern_classic/   — versión GoF
    <Patron>Pattern_modern/    — versión C++ moderno
    <Patron>Pattern_common/    — tipos compartidos
  src/                         — implementaciones y demos
tests/<Patron>Pattern/         — tests de todas las variantes
Patrones_curso/                — fichas del curso
```

## Cómo compilar

Requiere CMake ≥ 3.25, un compilador C++23 y Conan 2.x.

```bash
conan install . --output-folder=build --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
```

Para ejecutar los tests:

```bash
ctest --preset conan-release
```

---

*Si has llegado aquí sin el curso, gran parte del contexto y la explicación detrás de cada decisión de diseño se perderá. Las fichas del curso en `Patrones_curso/` complementan el código con teoría, diagramas UML y razonamiento.*

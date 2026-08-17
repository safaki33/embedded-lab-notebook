# Power tree — BOARD NAME

- **Date:**
- **Source of truth:** (schematic revision, datasheet versions)

## Input

- **Source:** (USB 5 V, barrel jack, battery — and its tolerance range)
- **Protection:** (reverse polarity, TVS, fuse, inrush limiting)
- **Worst case input voltage seen by the first regulator:**

## Rails

| Rail | Regulator | Type | Vin | Vout | Max current (datasheet) | Measured idle | Loads |
| --- | --- | --- | --- | --- | --- | --- | --- |
| | | LDO / buck / boost | | | | | |

## Sequencing

Which rail must come up first, and what enforces that? Enable chains, power-good signals, or
nothing at all.

## Worst case thermal

For each linear regulator: `P = (Vin − Vout) × Iout`. With the package thermal resistance
(θJA) and ambient temperature, does the junction stay inside the rated limit at maximum load?

| Regulator | P (W) | θJA (°C/W) | Rise (°C) | Tj at 25 °C ambient | Rated max | Margin |
| --- | --- | --- | --- | --- | --- | --- |

## Efficiency

Measured with bench supply and multimeter: `η = (Vout × Iout) / (Vin × Iin)`.

| Load current | Vin | Iin | Vout | Iout | Efficiency |
| --- | --- | --- | --- | --- | --- |

## Sleep current budget

| Mode | Expected | Measured | Difference explained by |
| --- | --- | --- | --- |

## Questions raised


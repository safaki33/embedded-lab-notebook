# Embedded Lab Notebook

A running record of embedded systems measurements, experiments and design calculations —
power electronics, RF and RTOS internals.

Reading about a subject and being able to measure it are different skills. This repository is
the measured half. Every claim here is backed by a number I produced myself, or it is explicitly
marked as an open question.

## How entries work

Every experiment is one file in `measurements/`, named `YYYY-MM-DD-NNN-short-slug.md`, and follows
the template in [`templates/measurement-entry.md`](templates/measurement-entry.md).

The rule that makes the notebook useful: **the hypothesis is written before the measurement**.
Predicting a result and being wrong teaches more than recording a result you never predicted.

## Structure

| Path | Contents |
| --- | --- |
| `measurements/` | One file per experiment, chronological |
| `templates/` | Fixed entry formats |
| `PLAN.md` | The 30-day study program this notebook follows |

## Index

| Date | Entry | Topic | Status |
| --- | --- | --- | --- |
| 2026-08-17 | [001 — Probe compensation and the 1x/10x tradeoff](measurements/2026-08-17-001-probe-compensation.md) | Measurement technique | In progress |

## Bench

Instruments used in these entries, with the settings that matter recorded per entry:

- Oscilloscope and probes
- Adjustable bench power supply
- Digital multimeter
- Soldering station
- Development board

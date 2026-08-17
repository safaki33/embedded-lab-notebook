# 001 — Probe compensation and the 1x/10x tradeoff

- **Date:** 2026-08-17
- **Topic:** measurement-technique
- **Status:** in progress

## Question

Two questions, both answerable with numbers:

1. What does an under-compensated and an over-compensated probe do to a square wave edge, and how
   large is the amplitude error at the top of the pulse?
2. On the same signal, how do the 1x and 10x settings differ in measured rise time and in noise
   floor?

## Hypothesis

Written before touching the instrument:

- Compensation is a capacitance match between the probe and the scope input. A mismatch should not
  shift the flat part of a low frequency square wave much, but should visibly tilt or overshoot the
  first microseconds after the edge. Expected amplitude error at the top: ____ %.
- The 1x setting removes the 9:1 attenuator, so it should show ____ times more signal amplitude but
  also far lower bandwidth, since the probe capacitance now sits directly across the input.
  Expected measured rise time in 1x: ____ ns, in 10x: ____ ns.

The point of writing these blanks in advance is that being wrong here is the actual lesson.

## Setup

- **Device under test:** oscilloscope's own calibration output (square wave, ____ kHz, ____ Vpp)
- **Instruments and settings:**
  - Scope model: ____
  - Vertical: ____ V/div, coupling: DC
  - Timebase: ____ , and a second capture at ____ for the edge detail
  - Bandwidth limit: off for this entry
  - Probe: ____ , rated bandwidth ____ MHz
- **Probing points:** calibration terminal, probe ground clip on the adjacent ground tab
- **Known sources of error:** probe rated bandwidth limits the measurable rise time; the scope's own
  rise time adds in quadrature and must be subtracted before quoting a signal rise time

## Procedure

1. Set the probe to 10x and connect to the calibration output.
2. Deliberately mis-adjust the compensation trimmer to the under-compensated extreme. Capture.
3. Adjust to the over-compensated extreme. Capture.
4. Adjust to a flat top. Capture. This is the reference.
5. Measure rise time (10 % to 90 %) on the flat-compensated capture.
6. Switch the probe and the scope channel setting to 1x. Repeat the rise time measurement.
7. With no signal connected, record the peak-to-peak noise on both 1x and 10x at the same V/div.

## Raw data

Screenshots in `img/`. Fill in as measured:

| Condition | Top of pulse | Amplitude error | Rise time (10-90 %) | Noise (Vpp, no signal) |
| --- | --- | --- | --- | --- |
| 10x, under-compensated | | | | |
| 10x, over-compensated | | | | |
| 10x, compensated | | | | |
| 1x, compensated | | | | |

Measured system rise time and the correction applied:

`t_signal = sqrt(t_measured² − t_scope² − t_probe²)` → ____

## Observations

## Interpretation

Did the compensation error behave the way the RC model predicts? Was the 1x bandwidth penalty as
large as expected? If the numbers came out different from the hypothesis, the model or the setup was
wrong — say which.

## Uncertainty

Scope's own rise time, probe tolerance, the ground clip inductance (small at this frequency but
record it as a known factor for entry 002), trimmer repeatability.

## Open questions

## Next step

Entry 002: measure the same 3.3 V rail ripple twice, once with the long ground lead and once with a
ground spring, and quantify how much of the observed ringing is real and how much is the probing.

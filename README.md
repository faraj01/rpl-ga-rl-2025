# Repository for "Optimizing RPL with a Hybrid GA-RL Approach: Field-Validated Performance for IoT WSNs"

## Overview
This repository contains data and code supporting the paper "Optimizing RPL with a Hybrid GA-RL Approach: Field-Validated Performance for IoT WSNs" by Hamzah Faraj, submitted to the IEEE Internet of Things Journal on March 13, 2025.

## Data Structure
- `taif_deployment_data.csv`: Raw measurements from a 30-day field test in Taif, Saudi Arabia, conducted from February 10 to March 11, 2025. Includes APC (mW), latency (ms), PDR (%), and interference (%). Columns are Date, APC(mW), Latency(ms), PDR(%), Interference(%).
- `rpl_ga_rl_simulation.c`: Contiki OS script simulating RPL optimization with a hybrid GA-RL approach across five topologies (random, linear, elliptical, tree, mobile).

## Simulation Setup
- **Platform**: Contiki OS with Cooja simulator.
- **Topologies**: Random, linear, elliptical, tree, mobile (10–30 nodes).
- **Parameters**: UDGM Distance Loss model, 1-hour simulation with 5-minute warm-up, 8 Hz channel check rate.
- **Metrics**: APC, latency, PDR, calculated as per Equation (1) in the manuscript (APC = (Energest_total * I * V) / (Rtimer_second * Runtime) mW).

## Deployment Details
- **Location**: Taif, Saudi Arabia (21.2703°N, 40.4155°E).
- **Duration**: 30 days (February 10–March 11, 2025).
- **Nodes**: 15 TmoteSky nodes in a 500 m × 500 m 5×3 grid, 2 mobile nodes (1 m/s).
- **Interference**: 10–30% (Wi-Fi, cellular), mitigated by CSMA and frequency hopping.

## Notes
This repository now contains the actual simulation code and Taif deployment data as described in the manuscript. For further details, contact Hamzah Faraj (f.hamzah@tu.edu.sa).

## About
Repository for the paper "Optimizing RPL with a Hybrid GA-RL Approach: Field-Validated Performance for IoT WSNs" by Hamzah Faraj, containing simulation code, Taif deployment data, and documentation.

# Digital simulation

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)

## General info

The application is a digital simulation of a wireless network based on the CSMA 1-persistent protocol. Simulation is developed according to the event scheduling method.

Simulation results:

* maximum error rate for each transmitter;
* average package error rate (BER) for the entire wireless network;
* number of generated packages;
* number of sent packages;
* number of lost packages;
* number of retransmissions;
* average number of retransmission;
* system bit rate (packages per second);
* average of package delay (ms);
* average of wainting time.

## Technologies
* C++.

## Setup

**Program calling parameters**
* simulation number 1-10 (diffrent seeds for generators);
* simulation time;
* lambda parameter (less than or equal to 0.1);
* end of time initial phase.

# 🚀 CDN Simulator

A distributed Content Delivery Network (CDN) simulator that models how modern CDNs route client requests, cache content at geographically distributed edge servers, handle server failures, and collect performance analytics.

The project combines a **C++ distributed-systems simulation engine** with a **TypeScript/Express backend** and a planned **React monitoring dashboard**.

---

## 📌 Overview

A Content Delivery Network improves application performance by serving content from edge servers located closer to users instead of repeatedly requesting data from a centralized origin server.

This project simulates that architecture by modeling:

- An Origin Server responsible for storing files
- Multiple geographically distributed Edge Servers
- LRU-based caching at edge servers
- Geo-based request routing
- Round-robin routing
- Least-loaded routing
- Edge-server health checks
- Automatic request failover
- Request logging
- Cache and request analytics
- Random client request generation
- Machine-readable JSON state export
- TypeScript/Express API integration

The simulator can be executed independently from the command line or accessed through a REST API.

---

# 🏗️ System Architecture

```text
                         Client Requests
                               │
                               ▼
                    ┌─────────────────────┐
                    │    Load Balancer    │
                    │                     │
                    │  • Geo Routing      │
                    │  • Round Robin      │
                    │  • Least Loaded     │
                    │  • Failover         │
                    └──────────┬──────────┘
                               │
              ┌────────────────┼────────────────┐
              │                │                │
              ▼                ▼                ▼
       ┌────────────┐   ┌────────────┐   ┌────────────┐
       │ Delhi Edge │   │Chennai Edge│   │Kolkata Edge│
       │            │   │            │   │            │
       │ LRU Cache  │   │ LRU Cache  │   │ LRU Cache  │
       │ Health     │   │ Health     │   │ Health     │
       │ Statistics │   │ Statistics │   │ Statistics │
       └──────┬─────┘   └──────┬─────┘   └──────┬─────┘
              │                │                │
              └────────────────┼────────────────┘
                               │
                         Cache Miss
                               │
                               ▼
                     ┌──────────────────┐
                     │  Origin Server   │
                     │                  │
                     │ A  B  C  D  E    │
                     └──────────────────┘


                    C++ Simulation Engine
                               │
                               ▼
                     Simulation Exporter
                               │
                               ▼
                       Structured JSON
                               │
                               ▼
                    Node.js / Express API
                               │
                               ▼
                       React Dashboard
